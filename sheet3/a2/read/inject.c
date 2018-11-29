
#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#include <errno.h>

#define PATH_MAX 1024


/*==========================================TYPES==========================================*/

typedef ssize_t (*readlink_t)(const char *, char *, size_t);
typedef char *(*getcwdOriginal_t)(char *, size_t);

typedef ssize_t (*readOriginal_t)(int, void *, size_t);
typedef ssize_t (*writeOriginal_t)(int, const void *, size_t);
typedef int (*openOriginal_t)(const char *, int);

typedef FILE *(*fopenOriginal_t)(const char *, const char *);
typedef size_t (*fwriteOriginal_t)(const void *, size_t, size_t, FILE *);
typedef size_t (*freadOriginal_t)(void *, size_t, size_t, FILE *);

/*==========================================PREDEFINE==========================================*/

/*we need to open the "whitelist" file. To maintain a certain degree of order on this code,
the hooked functions are the last ones, so we need to predefine the "open" and "read".*/
FILE *fopenOriginal(const char *filename, const char *mode);
size_t freadOriginal(void *ptr, size_t size, size_t nmemb, FILE *stream);


/*==========================================FIND OUT IF FILE IS ALLOWED==========================================*/

//we can't include unistd.h, so we'll have to do it like this to use "readlink" and "getcwd".
ssize_t readlinkOriginal(const char *path, char *buf, size_t bufsiz)
{
  return ((readlink_t)dlsym(RTLD_NEXT, "readlink"))(path, buf, bufsiz);
}
char *getcwdOriginal(char *buf, size_t size)
{
  return ((getcwdOriginal_t)dlsym(RTLD_NEXT, "getcwd"))(buf, size);
}


void findFileName(int fd, char* name)
{
  //stdin and stdout are enable for default
  //fd = 0 -> stdin
  //fd = 1 -> stdout
  if (fd == 0)
  {
    strcpy(name, "stdin");
    return;
  }
  if (fd == 1)
  {
    strcpy(name, "stdout");
    return;
  }
  //finds out file name using "readlink"
  char path[PATH_MAX];
  char str[PATH_MAX];
  strcpy(path,"/proc/self/fd/");
  sprintf(str, "%d", fd);
  strcat(path, str);
  char buf[PATH_MAX];
  int len;
  readlinkOriginal(path, buf, sizeof(buf));
  name[sizeof(buf)]='\n';
  strcpy (name, buf);
}



void findAbsolutePath(char *path)
{
  if (path[0]=='/')
    //already is absolute path
    return;
  //finds out current path and concatenates the name of the file with it
   char cwd[PATH_MAX];
   if (getcwdOriginal(cwd, sizeof(cwd)) != NULL) 
   {
      strcat(cwd,"/");
      strcat(cwd,path);
   }
   strcpy (path, cwd);
}


int isAllowed (char * buf)
{

  if( (strcmp("stdin", buf)==0) || (strcmp("stdout", buf)==0) )
    return 1;


  //open the whilelist file
  FILE *fp;
  char corda[PATH_MAX];
  fp = fopenOriginal("whitelist", "r");
  int over = 0;
  //finds out if the file that they're trying to open is in the whitelist
  while ( !(feof(fp)) && (!over))
  {
    fgets(corda, sizeof(corda)-1, fp);
    if (strncmp (corda, buf, strlen(buf)-1)==0)
      over = 1;
  }
  return over;
}


/*
About the hooked functions:
All of them are pretty much the same.
we have a functionOriginal(), that is simply calling the original function,
and we have function(), which is the hooked version. On this, we first find 
out if the file is on the white list. If it is, we can simply execute functionOriginal().
If not, we set errno to Permission denied, and return either -1 or NULL 
(depending on what the function should return).
"function" is to be replaced by the name of the function (e.g. read).

*/

/*==========================================READ==========================================*/


ssize_t readOriginal(int fd, void *data, size_t size) 
{

  //the original read function
  return ((readOriginal_t)dlsym(RTLD_NEXT, "read"))(fd, data, size);
}

ssize_t read(int fd, void *data, size_t size) 
{
  char str[PATH_MAX];
  findFileName(fd, str);
  if ( isAllowed(str) )
  {
    ssize_t amount_read;
    amount_read = readOriginal(fd, data, size);

    return amount_read;
  }
  errno=EACCES;
  return -1;
}

/*==========================================WRITE==========================================*/


ssize_t writeOriginal(int fd,  const void *data, size_t size)
{
  //the original write function
  return ((writeOriginal_t)dlsym(RTLD_NEXT, "write"))(fd, data, size);
}


ssize_t write(int fd, void *data, size_t size) 
{
  char str[PATH_MAX];
  findFileName(fd, str);
  if ( isAllowed(str) )
  {
    ssize_t amount_write;
    amount_write = writeOriginal(fd, data, size);

    return amount_write;
  }
  errno=EACCES;
  return -1;
}

/*==========================================OPEN==========================================*/


int openOriginal(const char *path, int oflags)
{
  //the original open function
  return ((openOriginal_t)dlsym(RTLD_NEXT, "open"))(path, oflags);
}

int open(const char *path, int oflags)
{
  char filename[PATH_MAX];
  strcpy(filename, path);
  findAbsolutePath((char*)filename);
    if (isAllowed ((char*)filename))
    {
      int open_file;
      open_file = openOriginal(filename, oflags);

      return open_file;
    }
  errno=EACCES;
  return -1;
}

/*==========================================FOPEN==========================================*/

FILE *fopenOriginal(const char *filename, const char *mode) 
{
  //the original open function
  return ((fopenOriginal_t)dlsym(RTLD_NEXT, "fopen"))(filename, mode);
}

FILE *fopen(const char *filename, const char *mode) 
{
  char path[PATH_MAX];
  strcpy(path, filename);
  findAbsolutePath(path);
  if(isAllowed(path))
  {
    FILE * open_file;
    open_file = fopenOriginal(filename, mode);

    return open_file;
  }
  errno=EACCES;
  return NULL;  

}


/*==========================================FWRITE==========================================*/


size_t fwriteOriginal(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  //the original open function
  return ((fwriteOriginal_t)dlsym(RTLD_NEXT, "fwrite"))(ptr, size, nmemb, stream);
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  char path[PATH_MAX];
  findFileName(fileno(stream),path);
  if(isAllowed(path))
  {
    size_t amount_write;
    amount_write = fwriteOriginal(ptr, size, nmemb, stream);

    return amount_write;
  }
  errno=EACCES;
  return -1; 
}


/*==========================================FREAD==========================================*/


size_t freadOriginal(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  //the original open function
  return ((freadOriginal_t)dlsym(RTLD_NEXT, "fwrite"))(ptr, size, nmemb, stream);
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  char path[PATH_MAX];
  findFileName(fileno(stream),path);
  if(isAllowed(path))
  {
    size_t amount_read;
    amount_read = freadOriginal(ptr, size, nmemb, stream);
    
    return amount_read;
  }
  errno=EACCES;
  return -1; 
}

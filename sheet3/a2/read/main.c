#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char *argv[]) {
  char buffer[1000];
  int amount_read;
  int fd;

  fd = fileno(stdin);
  if ((amount_read = read(fd, buffer, sizeof buffer)) == -1) {
    perror("error reading");
    return EXIT_FAILURE;
  }

  if (fwrite(buffer, sizeof(char), amount_read, stdout) == -1) {
    perror("error writing");
    return EXIT_FAILURE;
  }

  fd = open("file2.txt", O_WRONLY | O_APPEND);
  if (fd != -1)
  {
    buffer[0]='l';
    buffer[1]='\0';
    if (write(fd,buffer,1)== -1)
      perror("error writing");
    close(fd);
  }
  else
    perror("error opening");

  FILE *fp;
   int c;
   fp = fopen("file2.txt","r");
   if (fp != NULL)
   {
      while(1) {
        c = fgetc(fp);
        if( feof(fp) ) { 
           break ;
        }
        printf("%c", c);
     }
     fclose(fp);
   }
   else
    perror ("error opening");
   


  return EXIT_SUCCESS;
}
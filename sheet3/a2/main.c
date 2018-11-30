#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

const char *byte_to_binary(int x)
{
    static char b[12];
    b[0] = '\0';

    int z;
    for (z = 2048; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

int main(int argc, const char *argv[]) {

    /*
    printf("%6d, %s\n",O_RDONLY,byte_to_binary(O_RDONLY) );
    printf("%6d, %s\n",O_WRONLY,byte_to_binary(O_WRONLY) );
    printf("%6d, %s\n",O_RDWR,byte_to_binary(O_RDWR) );
    printf("%6d, %s\n",O_APPEND,byte_to_binary(O_APPEND) );
    printf("%6d, %s\n",O_TRUNC,byte_to_binary(O_TRUNC) );
    printf("%6d, %s\n",O_CREAT,byte_to_binary(O_CREAT) );
    printf("%6d, %s\n",O_EXCL,byte_to_binary(O_EXCL ) );

    printf("%6d, %s access mode\n",O_ACCMODE,byte_to_binary(O_ACCMODE ) );
    */

    /*char buffer[1000];
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
    int ch;
    fp = fopen("file2.txt","r");
    if (fp != NULL)
    {
        while(1) {
            ch = fgetc(fp);
            if( feof(fp) ) { 
                break ;
            }
            printf("%c", ch);
        }
        fclose(fp);
    }
    else
        perror ("error opening");*/

    char c[] = "This is tutorialspoint.com";
    char conteudo[100];
    FILE* file = fopen("file.txt", "w+");

    if (file != NULL)
    {

        if (fwrite(c, sizeof(char) , strlen(c), file) != -1)
        {
            fseek(file, 0, SEEK_SET);
            if (fread(conteudo,  sizeof(char) , strlen(c), file) != -1)
                printf("%s\n",conteudo );
            else
                perror ("error reading");
        }
        else
            perror ("error writing");

        fclose(file);
    }
    else
        perror ("error opening");


    char c2[] = "Random Text\n";
    char conteudo2[100];
    int file2;
    file2 = open("file2.txt", O_RDWR);
    if (file2 != -1)
    {
        if (write(file2, c2, strlen(c2)) != -1)
            lseek(file2, 0, SEEK_SET);
        else
            perror ("error writing 2");

        int sz = read(file2, conteudo2, strlen(c2));
        if (sz != -1)
        {
            for (int i = 0; i < sz; ++i)
                printf("%c",conteudo2[i] );
        }
        else
            perror ("error reading 2");
        close(file2);
    }
    else
        perror ("error opening 2");




    return EXIT_SUCCESS;
}
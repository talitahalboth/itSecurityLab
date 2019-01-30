#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int isInInterval(int x)
{
    if (x <=47 || x > 57)
        if (x <=64 || x > 90)
            return 0;
        else
            return 1;
    return 1;
}

//neded it before being sure of what i was doing, left it _just to be sure_ although i only generate valid keys
int checkKey(char key[29])
{
    if ((key[0] & 0xff ^ key[1] & 0xff ^ key[2] & 0xff ^ key[3] & 0xff ^ key[4] & 0xff) != 0x41/*0b1000001*/) return(1);
    if ((key[6] & 0xff ^ key[7] & 0xff ^ key[8] & 0xff) != (key[0xa] & 0xff)) return(1);
    if ((key[0xc] & 0xff & key[0xd] & 0xff & key[0xe] & 0xff & key[0xf] & 0xff) != (key[0x10] & 0xff)) return(1);
    if (((key[0x12] & 0xff | key[0x16] & 0xff | key[0x14] & 0xff) & 0xf) != (key[0x15] & 0xff ^ key[0x13] & 0xff)) return(1);
    if (((key[0x18] & 0xff) != (key[0x19] & 0xff) - 0x1) || (((key[0x1a] & 0xff) != (key[0x1b] & 0xff) + 0x1) || ((key[0x1c] & 0xff) != 0x58))) return(1);    
    for (int i = 0; i < 26; ++i)
        if ((((i != 0x5) && (i != 0xb)) && (i != 0x11)) && (i != 0x17))
            if (!isInInterval(key[i]))
                return (1);
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./keygen <number of key>\n" );
        exit (1);
    }
    srand(time(NULL));
    int r, x;
    char key[29];
    x = strtol(argv[1], NULL, 10);
    for (int i = 0; i < x; ++i)
    {
        //valores fixos primeiro:
        key[5]= 0x2d;
        key[11]= 0x2d;
        key[17]= 0x2d;
        key[23]= 0x2d;
        key[28]= 0x58;
        //(47,57] ou (2f,39]
        //(64,90] ou (40,5a]
        //monta lista com todos os valores possíveis
        int permittedValues[36];
        for (int i = 0; i < 36; ++i)
        {
            if (i < 10)
            {
                permittedValues[i] = 48+i;
            }
            else
            {
                permittedValues[i] = 65 + i-10;
            }
        }
        for (int i = 0; i < 4; ++i)
        {
            r = rand() % 36; 
            key[i]=permittedValues[r]; 
        } 
        //makes sure everything is in the interval
        while (!isInInterval(key[4] = key[0] ^ key[1] ^ key[2] ^ key[3] ^ 0x41))
        {
            r = rand() % 36; 
            key[0]=permittedValues[r]; 
        }


        r = rand() % 36; 
        key[6]= permittedValues[r];
        r = rand() % 36; 
        key[7]= permittedValues[r];
        r = rand() % 36; 
        key[8]= permittedValues[r];
        while (!isInInterval(key[10] =  key[6] ^ key[7] ^ key[8]))
        {
            r = rand() % 36; 
            key[8]= permittedValues[r];
        }

        r = rand() % 36; 
        key[9]= permittedValues[r];

        r = rand() % 36;
        key[16] = permittedValues[r];
        for (int i = 0; i < 4; ++i)
        {
            r = rand() % 36;
            while (!isInInterval(key[12+i] = permittedValues[r] | key[16]))
            {
                r = rand() % 36;
            }
        }
        key[16] = key[12] & key[13] & key[14] & key[15];

        r = rand() % 36; 
        key[18]= permittedValues[r];
        r = rand() % 36; 
        key[20]= permittedValues[r];
        r = rand() % 36; 
        while (!isInInterval(key[22]= permittedValues[r] | 0xf))
        {
            r = rand() % 36; 
        }
        

        r = rand() % 14; 
        key[19] = 65+r;
        key[21] = key[19] ^ 15;

        r = rand() % 35; 
        key[24] = permittedValues[r];
        while (!isInInterval (key[25] = key[24]+1))
        {
            r = rand() % 35; 
            key[24] = permittedValues[r];
        }


        r = rand() % 35; 
        key[27] = permittedValues[r];
        while (!isInInterval (key[26] = key[27]+1))
        {
            r = rand() % 35; 
            key[27] = permittedValues[r];
        }
        if (!checkKey(key))
            printf("%s\n",key );
    }
    return 0;
}
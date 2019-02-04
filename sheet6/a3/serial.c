#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    //printf("%c\n",0x41^0x0^0x0^0x0^0x0 );
    //printf("%d\n",0x0^0x0 );
    char key[29];

    // > 02f & <= 0x39
    //maior que 2f ou (menor ou igual) a 39
    //c.c., maior que 40 e menor ou igual a 5a

    //xor igual a 41

    //pode ser qualquer numero
    key[0]= 0x41;
    //pode ser qualquer numero
    key[1]= 0x50;
    //pode ser qualquer numero
    key[2]= 0x50;
    //pode ser qualquer numero
    key[3]= 0x50;
    //xor dos antiores com 41
    key[4]= 0x50;

    /*fixo*/
    key[5]= 0x2d;

    //xor igual à key[10] 0xa
    key[6]= 0x30;
    key[7]= 0x50;
    key[8]= 0x50;
    //pode ser qualquer numero
    key[9]= 0x51;

    key[10]= 0x30;


    //fixo
    key[11]= 0x2d;
    //[16] = 1000
    //       1000
    /*       1100
             1110

    */           
    //and precisa ser igual à key[16] 0x10
    key[12]= 0x30;
    key[13]= 0x30;
    key[14]= 0x30;
    key[15]= 0x30;
    //pode ser qualquer numero
    key[16]= 0x30;

    //fixo
    key[17]= 0x2d;

    //pode ser qualquer numero
    key[18]= 0x4F;
    //qualquer numero entre [65,78]
    key[19]= 0x4e;
    //pode ser qualquer numero
    key[20]= 0x4F;
    //key[19] ^ 15
    key[21]= 0x41;
    //pode ser qualquer numero OR 0xf
    key[22]= 0x4F;

    //fixo
    key[23]= 0x2d;


    //pode ser qualquer numero
    key[24]= 0x30;
    //key[24] + 1
    key[25]= 0x31;

    //pode ser qualquer numero
    key[26]= 0x31;
    //key[26] - 1
    key[27]= 0x30;

    //fixo
    key[28]= 0x58;

    if ((key[0] & 0xff ^ key[1] & 0xff ^ key[2] & 0xff ^ key[3] & 0xff ^ key[4] & 0xff) != 0x41/*0b1000001*/) {
        printf("1\n");
        exit(1);
    }

    if ((key[6] & 0xff ^ key[7] & 0xff ^ key[8] & 0xff) != (key[0xa] & 0xff)) {
        printf("2\n");
        exit(1);
    }
 
    if ((key[0xc] & 0xff & key[0xd] & 0xff & key[0xe] & 0xff & key[0xf] & 0xff) != (key[0x10] & 0xff)) {
        printf("3\n");
        exit(1);
    }

    if (((key[0x12] & 0xff | key[0x16] & 0xff | key[0x14] & 0xff) & 0xf) != (key[0x15] & 0xff ^ key[0x13] & 0xff)) {
        printf("4\n");
        exit(1);
    }

    if (((key[0x18] & 0xff) != (key[0x19] & 0xff) - 0x1) 
        || (((key[0x1a] & 0xff) != (key[0x1b] & 0xff) + 0x1) || ((key[0x1c] & 0xff) != 0x58))) {
        printf("5\n");
        exit(1);
    }
    for (int i = 0; i < 29; ++i)
    {
        printf("%c",key[i] );
    }
    return 0;
}
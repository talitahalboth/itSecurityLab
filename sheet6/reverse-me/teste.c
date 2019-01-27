#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    //int var8 = arg0; //var_8= dword ptr -8
    char varc[26] = "abcdefghijklmnopqrstuvwxyz"; //var_C= dword ptr -0Ch
    char var15[26];
    for (int i = 0 /*var_1C= dword ptr -1Ch */; i < 9; ++i)
    {
        int var20 = strlen (varc)-1;
        int var24 = i * i ^ 0x6f56df77;
        if (i < 8)
        {
            int dx = var24 % var20;
            int cl = varc[dx];
            var15[i] = cl;

        }
        else
        {
            var15[i] = 0;
        }


    }
    printf("%s\n",var15 );
    return 0;
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    FILE *outputFile,*optab,*lengthFile,*symtab;
    int op1[10],txtlen,txtlen1,i,j=0,len, start, addr, locctr, opcode;
    char temp[30],line[20],field1[20],field2[10],field3[10],symlabel[10],operation[10];

    outputFile = fopen("output.txt", "r");
    lengthFile = fopen("length.txt", "r");
    optab = fopen("optab.txt", "r");
    fscanf(outputFile,"%s%s%s", field1, field2, field3);
    if(strcmp(field2, "START") == 0)
    {
        start = (int)strtol(field3, NULL, 16);
        fscanf(lengthFile, "%X", &len);
    }
    printf("H^%6s^%06X^%06X\nT^%06X^", field1, start, len, start);
    fscanf(outputFile, "%X%s%s%s", &addr, field1, field2, field3);
    while(strcmp(field2, "END") != 0)
    {
        optab=fopen("optab.txt","r");
        while(fscanf(optab,"%s%X", operation, &opcode) > 0)
        {
            if(strcmp(field2, operation) == 0)
            {
                symtab = fopen("symtab.txt", "r");

                while(fscanf(symtab, "%X%s", &locctr, symlabel) > 0)
                {
                    if(strcmp(field3, symlabel) == 0)
                        printf("%02X%04X^", opcode, locctr);
                    else if(strcmp(field3, "-") == 0)
                        printf("%02X0000^", opcode);
                    break;
                }
                fclose(symtab);
                break;
            }
        }
        fclose(optab);
        if((strcmp(field2,"BYTE")==0)||(strcmp(field2,"WORD")==0))
        {
            if(strcmp(field2, "WORD") == 0)
                printf("%06X^",(int)strtol(field3, NULL, 10));
            else
            {
                len=strlen(field3);
                if (field3[0] == 'C') {
                    for(i=2;i<=len-2;i++)
                        printf("%06X",field3[i]);
                }
                else
                {
                    for(i=2;i<=len-2;i++)
                        printf("%C",field3[i]);
                }
                    
                printf("^");
            }
        }
        fscanf(outputFile,"%X%s%s%s", &addr, field1, field2, field3);
    }
    printf("\nE^%06X\n",start);
    fclose(outputFile);
    fclose(lengthFile);

    return 0;
}
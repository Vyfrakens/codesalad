#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *inputFile, *optab, *symtab, *outputFile, *lengthFile;
    int field3, locctr, startingAddress, opcode;
    char field1[20], field2[20], op[20], operation[20];
    
    inputFile = fopen("input.txt", "r");
    
    symtab = fopen("symtab.txt", "w");
    outputFile = fopen("output.txt", "w");
    lengthFile = fopen("length.txt", "w");
    
    
    
    
    fscanf(inputFile, "%s%s%X", field1, field2, &field3);
    if (strcmp(field2, "START") == 0)
    {
        startingAddress = field3;
        locctr = startingAddress;
        fprintf(outputFile, "\t%s\t%s\t%X\n",field1,field2,field3); // COPY START 1000
    }
    else
        locctr=0x0;
    
    
    
    
    fscanf(inputFile, "%s%s", field1, field2);
    while(!feof(inputFile))
    {
        fscanf(inputFile, "%s", op);
        fprintf(outputFile, "\n%X\t%s\t%s\t%s\n", locctr, field1, field2, op);
        
        
        if(strcmp(field1, "-") != 0)
            fprintf(symtab, "\n%X\t%s\n", locctr, field1);
        
        optab = fopen("optab.txt", "r");
        fscanf(optab, "%s%X", operation, &opcode);
        while(!feof(optab))
        {
            if(strcmp(field2, operation) == 0)
            {
                locctr = locctr + 3;
                break;
            }
            fscanf(optab,"%s%X", operation, &opcode);
        }
        if(strcmp(field2, operation) == 0 && feof(optab))
            locctr = locctr + 3;
        fclose(optab);
        
        
        
        
        if(strcmp(field2,"WORD") == 0)
            locctr = locctr + 3;
        else if(strcmp(field2,"RESW") == 0)
        {
            field3 = atoi(op);
            locctr = locctr + (3 * field3);
        }
        else if(strcmp(field2,"BYTE")==0)
        {
            if(op[0] == 'X')
                locctr = locctr + 1;
            else
                locctr=locctr + strlen(op) - 3;
        }
        else if(strcmp(field2,"RESB") == 0)
        {
            field3 = atoi(op);
            locctr = locctr + field3;
        }
        fscanf(inputFile,"%s%s",field1,field2);
    }
    
    
    
    
    
    
    if(strcmp(field2, "END") == 0)
        fprintf(lengthFile, "%X\n", locctr - startingAddress);
    
    
    fclose(inputFile);
    fclose(symtab);
    
    return 0;
}










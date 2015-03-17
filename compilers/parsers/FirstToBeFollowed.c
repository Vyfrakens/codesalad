//
//  FirstToBeFollowed.c
//  MyLaboratory
//
//  Created by Francis Johny on 14/03/15.
//  Copyright (c) 2015 Vyfrankens. All rights reserved.
//

//TODO : FOLLOW()

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int m1, n, i, j = 2, z, flag = 0, old;
char a[10][10], g[10];
void first(char);
int check(char);

int cmp(const void *a, const void *b)
{
    return ( *(char*)a - *(char*)b );
}

int unique(char *a, int len)
{
    int i, j;
    qsort(a, len, sizeof(char), cmp);
    for (i = j = 0; i < len; i++) {
        if (a[i] != a[j]) {
            a[++j] = a[i];
        }
    }
    return j + 1;
}


int main()
{
    char ch;
    int i, len;
    printf("-----------------------------\n");
    printf("\t\tFIRST\n");
    printf("-----------------------------\n");
    printf("Enter the number of productions : ");
    scanf("%d",&n);
    printf("Enter the productions : \n");
    for (i = 0; i < n; i++) {
        scanf("%s%c", a[i], &ch);
    }
    printf("----------------------------");
    printf("\nPRODUCTIONS\tFIRST\n");
    printf("----------------------------\n");
    for (z = 0; z < n; z++) {
        m1 = 0;
        flag = 0;
        printf("%7s\t\t",a[z]);
        first(a[z][0]);
        len = unique(g, m1);
        for (j = 0; j < len; j++) {
            if (g[j] != '!') {
                printf("%c ", g[j]);
            }
        }
        printf(" \n");
    }
    printf("----------------------------\n");
}



void first(char c)
{
    int k;
    if (!isupper(c)) {
        g[m1++] = c;
    }
    
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (a[k][2] == '$') {
                g[m1++] = a[k][2];
            } else if (islower(a[k][2])) {
                g[m1++] = a[k][2];
            } else {
                first(a[k][2]);
                for (j = 2; a[k][j+1] != '\0';) {
                    j++;
                    if(check('$') && g[0] != '$') {
                        first(a[k][j]);
                    }
                }
            }
        }
    }
}

int check(char ch)
{
    int i;
    for (i = 0; g[i] != '\0'; i++) {
        if (g[i] == ch) {
            g[i] = '!';
            return 1;
        }
    }
    return 0;
}






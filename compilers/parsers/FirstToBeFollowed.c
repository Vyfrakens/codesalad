//
//  FirstToBeFollowed.c
//  MyLaboratory
//
//  Created by Francis Johny on 14/03/15.
//  Copyright (c) 2015 Vyfrankens. All rights reserved.
//

//TODO : FOLLOW()

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int m1, n, i, j = 3, z, flag = 0, old;
char a[10][10], g[10];
void first(char);

int main()
{
    char ch;
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
        for (j = 0; j < m1; j++) {
            printf("%c ", g[j]);
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
        flag = 0;
    }
    
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (a[k][2] == '$') {
                if (!flag) {
                    g[m1++] = a[k][2];
                } else {
                    first(a[old][j++]);
                }
            } else if (islower(a[k][2])) {
                g[m1++] = a[k][2];
            } else {
                flag = 1;
                old = k;
                first(a[k][2]);
            }
        }
    }
}
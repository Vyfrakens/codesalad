//
//  FirstToBeFollowed.c
//  MyLaboratory
//
//  Created by Francis Johny on 14/03/15.
//  Copyright (c) 2015 Vyfrankens. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int m, m1, n, z, i, j, flag = 0;
char a[10][10], f[1500], g[150];
void follow(char);
void firstof(char);
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
    int i, len, j;
    printf("--------------------------------------------------------\n");
    printf("\t\tFIRST AND FOLLOW\n");
    printf("--------------------------------------------------------\n");
    printf("Enter the number of productions : ");
    scanf("%d",&n);
    printf("Enter the productions : \n");
    for (i = 0; i < n; i++) {
        scanf("%s%c", a[i], &ch);
    }
    printf("------------------------------------------------");
    printf("\nPRODUCTIONS\t\tFIRST\t\tFOLLOW\n");
    printf("----------------------------------------------\n");
    for (z = 0; z < n; z++) {
        m = 0;
        m1 = 0;
        flag = 0;
        printf("%11s\t\t",a[z]);
        first(a[z][0]);
        len = unique(g, m1);
        for (j = 0; j < len; j++) {
            if (g[j] != '!') {
                printf("%c ", g[j]);
            }
        }
        printf("\t\t");
        follow(a[z][0]);
        len = unique(f, m);
        for (j = 0; j < len; j++) {
            printf("%c ", f[j]);
        }
        printf(" \n");
        memset(&f[0], 0, sizeof(f));
        memset(&g[0], 0, sizeof(g));
    }
    printf("---------------------------------------------\n");
}

void follow(char c)
{
    int i,j;
    if (a[0][0] == c) {
        f[m++] = '$';
    }
    
    for (i = 0; i < n; i++) {
        for (j = 2; a[i][j] != '\0'; j++) {
            if (a[i][j] == c) {
                if (a[i][j+1] != '\0') {
                    firstof(a[i][++j]);
                    if (flag) {
                        if (a[i][j+1] != '\0')
                            firstof(a[i][++j]);
                        if (a[i][j+1] == '\0')
                            follow(a[i][0]);
                    }
                }
                else if (a[i][j+1] == '\0' && c != a[i][0]) {
                    follow(a[i][0]);
                }
            }
        }
    }
}

void firstof(char c)
{
    int k;
    if (!isupper(c)) {
        f[m++] = c;
    }
    
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (a[k][2] == '$') {
                flag = 1;
            } else if (islower(a[k][2])) {
                f[m++] = a[k][2];
            } else {
                firstof(a[k][2]);
            }
        }
    }
}


void first(char c)
{
    int k, j;
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
                    if(check('$')) {
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


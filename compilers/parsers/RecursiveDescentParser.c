//  MyLaboratory
//  RecursiveDescentParser
//  Created by Francis Johny on 17/04/15.
//  Copyright (c) 2015 Vyfrankens. All rights reserved.
//

 //Grammar :
 //E -> T | T + E
 //T -> a | a * T | (E)

 //Input : (a)

#include <stdio.h>

char *next;

int E(); int E1(); int E2(); int T(); int T1(); int T2(); int T3();

int terminal(char token){ return (*next++ == token); }
int E1(){ return T(); }
int E2(){ return T() && terminal('+') && E(); }
int E(){ char *temp = next; return (next = temp, E1()) || (next = temp, E2()); }
int T1(){ return terminal('a'); }
int T2(){ return terminal('a') && terminal('*') && T(); }
int T3(){ return terminal('(') && E() && terminal(')'); }
int T(){ char *temp = next; return (next = temp, T1()) || (next = temp, T2()) || (next = temp, T3()); }

int main(int argc, const char * argv[]) {
    char str[10];
    printf("INPUT : ");
    scanf("%s", str);
    next = &str[0];
    printf("OUTPUT : ");
    (E() == 1 && *next == '\0') ? printf("PARSED SUCCESSFULLY") : printf("PARSED UNSUCCESSFULLY");
    printf("\n");
    return 0;
}

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
int gethex(FILE*);
char *getstr(FILE*);
char *inttobin(int);
int strequals(char*, char*);
int main() {
	char *mask;
	int start, pstart, plen, rstart, rlen, addr, val, i, l;
	FILE *f = fopen("relloader.object", "r");
	if(!f) return -1;
	printf("Enter the starting address: ");
	scanf("%x", &start);
	if(strequals(getstr(f), "H")) {
		printf("%s\n", getstr(f));
		pstart = gethex(f);
		plen = gethex(f);
	}
	else
		return -1;
	addr = start;
	while(strequals(getstr(f), "T")) {
		rstart = gethex(f) + start;
		rlen = gethex(f);
		mask = inttobin(gethex(f));
		i = 0;
		while(addr<rstart) printf("%06X\tXX\n", addr++);
		while(addr<(rstart+rlen)) {
			l = ftell(f);
			val = gethex(f) + mask[i++] * (start - pstart);
			l = ftell(f) - l - 1;
			switch(l/2) {
				case 3: printf("%06X\t%02X\n", addr++, val/0x10000);
				case 2: printf("%06X\t%02X\n", addr++, (val/0x100)%0x100);
				case 1: printf("%06X\t%02X\n", addr++, val%0x100);
			}
		}
	}
	while (addr<(start+plen)) printf("%06X\tXX\n", addr++);
	return 0;
}
int gethex(FILE *f) {
	int x;
	fscanf(f, "%x", &x);
	return x;
}
char *getstr(FILE *f) {
	char *str = malloc(7);
	fscanf(f, "%s", str);
	return str;
}
char *inttobin(int n) {
	char *bin = malloc(12);
	int i;
	for(i=12; i>0; n/=2)
		bin[--i] = n%2;
	return bin;
}
int strequals(char *a, char *b) {
	return strcmp(a, b)==0;
}
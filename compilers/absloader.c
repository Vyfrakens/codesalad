#include "stdio.h"
#include "stdlib.h"
#include "math.h"
char *getstring(FILE*, int);
int strtohex(char*);
int main() {
	char ch, str[7];
	int pstart, plen, rstart, rlen, addr, val;
	FILE *f = fopen("absloader.obj", "r");
	if(!f) return -1;
	if(fgetc(f)=='H') {
		printf("%s\n", getstring(f, 6));
		pstart = strtohex(getstring(f, 6));
		plen = strtohex(getstring(f, 6));
		fgetc(f);
	}
	else return -1;
	addr = pstart;
	while((ch = fgetc(f))!='E') {
		rstart = strtohex(getstring(f, 6));
		rlen = strtohex(getstring(f, 2));
		while(addr<rstart) printf("%06X\tXX\n", addr++);
		while(addr<(rstart+rlen))
			printf("%06X\t%02X\n", addr++, strtohex(getstring(f, 2)));
		fgetc(f);
	}
	while(addr<(rstart+rlen)) printf("%06X\tXX\n", addr++);
	return 0;
}
char *getstring(FILE *f, int len) {
	char *str = malloc(len+1);
	fread(str, len, 1, f);
	str[len] = '\0';
	return str;
}
int strtohex(char* str) {
	char ch;
	int res = 0, i, x, len;
	for(len=0; str[len]!='\0'; ++len);
	for(i=0; i<len; ++i) {
		ch = str[i];
		x = (ch>='0'&&ch<='9')?(ch-'0'):((ch>='A'&&ch<='F')?(ch-'A'+10):(ch-'a'+10));
		res += x * pow(16, len-i-1);
	}
	return res;
}
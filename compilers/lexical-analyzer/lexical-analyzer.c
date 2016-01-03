#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char *KEYWORDS[] = {"void", "int", "float", "while"};
char *OPERATORS[] = {"=", "+", "-", "*", "/", "=="};
char *DELIMITERS[] = {"(", ")", "{", "}", ";"};

int iskeyword(char *s) {
	int i;
	for(i=0; i < sizeof(KEYWORDS) / sizeof(char*); ++i)
		if(strcmp(s, KEYWORDS[i]) == 0)
			return 1;
	return 0;
}
int isoperator(char *s) {
	int i;
	for(i=0; i < sizeof(OPERATORS) / sizeof(char*); ++i)
		if(strcmp(s, OPERATORS[i]) == 0)
			return 1;
	return 0;
}
int isdelimiter(char *s) {
	int i;
	for(i=0; i < sizeof(DELIMITERS) / sizeof(char*); ++i)
		if(strcmp(s, DELIMITERS[i]) == 0)
			return 1;
	return 0;
}
int main() {
	int i;
	char str[80];
	FILE *f = fopen("../firstfollow/stack.h", "r");
	if(f) {
		while(!feof(f)) {
			fscanf(f, "%s", str);
			printf("%s\t", str);
			if(iskeyword(str))
				printf("Keyword\t");
			if(isoperator(str))
				printf("Operator\t");
			if(isdelimiter(str))
				printf("Delimiter\t");
			printf("\n");
		}
	}
}
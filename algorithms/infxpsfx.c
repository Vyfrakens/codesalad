#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct {
	char s[50];
	int top;
} stack;
void push(stack*, char);
char pop(stack*);
void debug(stack*);
int getprec(char op);
int main() {
	stack oprnd = {"", -1}, postfix = {"", -1}, ev = {"", -1};
	int i = 0, j, eval = 1, op1, op2;
	char expn[50], ch;
	printf("Enter the expresion: ");
	while((expn[i++]=getchar())!='\n');
	expn[i-1] = ')';
	expn[i] = '\0';
	push(&oprnd, '(');
	for(i=0; expn[i]!='\0'; ++i) {
		if(isalnum(expn[i])) {
			push(&postfix, expn[i]);
			if(isalpha(expn[i]))
				eval = 0;
		}
		else if(expn[i]=='(') {
			push(&oprnd, expn[i]);
		}
		else if(expn[i]==')') {
			while((ch=pop(&oprnd))!='(')
				push(&postfix, ch);
		}
		else if(expn[i]=='+'||expn[i]=='-'||expn[i]=='*'||expn[i]=='/'||expn[i]=='^') {
			while(getprec(expn[i])<=getprec(ch=pop(&oprnd))) {
				push(&postfix, ch);
			}
			push(&oprnd, ch);
			push(&oprnd, expn[i]);
		}
		printf("Iteration %d (%c):\n", i, expn[i]);
		printf("Stack: ");
		debug(&oprnd);
		printf("Postfix: ");
		debug(&postfix);
	}
	printf("Postfix Expression is %s\n", postfix.s);
	if(eval) {
		for(i=0; i<=postfix.top; ++i) {
			if(isdigit(postfix.s[i]))
				push(&ev, (postfix.s[i]));
			if(postfix.s[i]=='+'||postfix.s[i]=='-'||postfix.s[i]=='*'||postfix.s[i]=='/'||postfix.s[i]=='^') {
				op1 = atoi(pop(&ev));
				op2 = atoi(pop(&ev));
				switch(postfix.s[i]) {
					case '+': push(&ev, op2 + op1) ; break;
					case '-': push(&ev, op2 - op1) ; break;
					case '*': push(&ev, op2 * op1) ; break;
					case '/': push(&ev, op2 / op1) ; break;
					case '^': push(&ev, op2 ^ op1) ; break;
				}
			}
		}
	}
	ev.s[ev.top+1] = '\0';
	for(i=0; ev.s[i] != '\0'; ++i) printf("%d", ev.s[i]);
	return 0;
}
int getprec(char op) {
	switch(op) {
		case '+':
		case '-': return 0;
		case '*':
		case '/': return 1;
		case '^': return 2;
		default: return -1;
	}
}
void push(stack *s, char item) {
	s->s[++s->top] = item;
}
char pop(stack *s) {
	return s->s[s->top--];
}
void debug(stack *s) {
	int i;
	for(i=0; i<=s->top; ++i)
		printf("%c", s->s[i]);
	printf("\n");
}
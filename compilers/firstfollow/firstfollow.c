#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stack.h"

typedef struct {
	char lhs;
	char rhs[10];
} production;

int n;
production *p;

production getproduction();
int isterminal(char);
stack *first(char);
stack *first_of_rhs(char*);
stack *follow(char);

int main() {
	int i;
	stack *f;
	printf("Enter the no. of productions: ");
	scanf("%d",&n);
	p = malloc(n);
	printf("Enter the productions (epsilon = #):\n");
	for(i=0; i<n; ++i)
		p[i] = getproduction();

	printf("Productions:\n");
	for(i=0; i<n; ++i)
		printf("%c -> %s\n", p[i].lhs, p[i].rhs);
	printf("\n");

	for(i=0; i<n; ++i) {
		f = first(p[i].lhs);
		clean_stack(f);
		printf("FIRST(%c) = {", p[i].lhs);
		print_stack(f, ", ");
		printf("}\n");

		while(p[i].lhs == p[i+1].lhs) ++i;
	}

	printf("\n");

	for(i=0; i<n; ++i) {
		f = follow(p[i].lhs);
		clean_stack(f);
		printf("FOLLOW(%c) = {", p[i].lhs);
		print_stack(f, ", ");
		printf("}\n");

		while(p[i].lhs == p[i+1].lhs) ++i;
	}
}

production getproduction() {
	production *p = malloc(sizeof(production));
	char *temp = malloc(2);	// For siipping over the arrow
	scanf("%1s%2s%9s", &p->lhs, temp, p->rhs);
	free(temp);
	return *p;
}

stack *first(char c) {
	int i;
	stack *f = NULL;
	// printf("first(%c) = \n", c);
	if(c == '\0')
		push(&f, '#');
	else if(isterminal(c))
		push(&f, c);

	for(i=0; i<n; ++i) {
		if(p[i].lhs == c) {
			if(isterminal(p[i].lhs))	// Terminal or epsilon
				push(&f, p[i].lhs);
			else						// Non terminal
				push_stack(&f, first_of_rhs(p[i].rhs));
		}
	}
	// printf("\n");
	return f;
}

stack *first_of_rhs(char *s) {
	stack *f = NULL;
	push_stack(&f, first(*s));
	if(f->data == '#' && *(s + 1) != '\0') {
		pop(&f);	// Remove epsilon
		push_stack(&f, first_of_rhs(s + 1));
	}
	return f;
}

stack *follow(char c) {
	int i, j;
	stack *f = NULL;
	// printf("-> follow(%c) \n", c);
	if(p[0].lhs == c) 
		push(&f, '$');
	for(i=0; i<n; ++i) {
		for(j=0; p[i].rhs[j] != '\0'; ++j) {
			if(p[i].rhs[j] == c) {
				push_stack(&f, first_of_rhs(p[i].rhs + j + 1));
				if(f->data == '#') {
					pop(&f);
					if(c != p[i].lhs)
						push_stack(&f, follow(p[i].lhs));
				}
			}
		}
	}
	// printf("\n");
	return f;
}

int isterminal(char c) {
	return !(c >= 'A'&& c <= 'Z');
}

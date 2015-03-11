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
		remove_duplicates(f);
		printf("FIRST(%c) = {", p[i].lhs);
		print_stack(f, ", ");
		printf("}\n");

		while(p[i].lhs == p[i+1].lhs) ++i;
	}

	printf("\n");

	for(i=0; i<n; ++i) {
		f = follow(p[i].lhs);
		remove_duplicates(f);
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
	int i, j;
	stack *f = NULL;
	// printf("first(%c) -> ", c);
	if(isterminal(c))
		push(&f, c);

	for(i=0; i<n; ++i) {
		j = 0;
		if(p[i].lhs == c) {
			if(isterminal(p[i].rhs[0]))	// Terminal or epsilon
				push(&f, p[i].rhs[0]);
			else {	// Non terminal
				// printf("first(%c)\n", p[i].rhs[0]);
				push_stack(&f, first(p[i].rhs[0]));
				for(j=1; p[i].rhs[j] != '\0' && f->data == '#'; ++j) {
					pop(&f);	// Remove epsilon
					push_stack(&f, first(p[i].rhs[j]));
				}
			}
		}
	}
	// printf("\n");
	return f;
}

stack *follow(char c) {
	int i, j, k;
	stack *f = NULL;
	// printf("follow(%c) -> ", c);
	if(p[0].lhs == c) 
		push(&f, '$');
	for(i=0; i<n; ++i) {
		for(j=0; p[i].rhs[j] != '\0'; ++j) {
			if(p[i].rhs[j] == c && p[i].lhs != c) {
				if(p[i].rhs[j+1] == '\0') {
					// printf("follow(%c)\n", p[i].lhs);
					push_stack(&f, follow(p[i].lhs));
				}
				else {
					// printf("first(%c)\n", p[i].rhs[j+1]);
					push_stack(&f, first(p[i].rhs[j+1]));
					for(k=j+2; p[i].rhs[k] != '\0' && f->data == '#'; ++k) {
						pop(&f);	// Remove epsilon
						// printf("first(%c)\n", p[i].rhs[k]);
						push_stack(&f, first(p[i].rhs[k]));
					}
					if(f->data == '#') {
						pop(&f);
						// printf("follow(%c)\n", p[i].lhs);
						push_stack(&f, follow(p[i].lhs));
					}
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

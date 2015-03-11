struct stack {
	char data;
	struct stack *next;
};
typedef struct stack stack;

void push(stack **s, char c) {
	stack *t = malloc(sizeof(stack));
	t->data = c;
	t->next = *s;
	(*s) = t;
}

void push_stack(stack **s, stack *c) {
	stack *p;
	if(c) {
		for(p = c; p->next; p = p->next);
		p->next = (*s);
		(*s) = c;
	}
}

char pop(stack **s) {
	if(*s) {
		char c = (*s)->data;
		stack *t = *s;
		(*s) = (*s)->next;
		free(t);
		return c;
	}
	return 0;
}

void reverse_stack(stack **s) {
	if (*s) {
		*s = (*s)->next;
		reverse_stack(s);
	}
}

void remove_duplicates(stack *start) {
	stack *ptr1, *ptr2, *dup;
	ptr1 = start;

	while(ptr1 != NULL && ptr1->next != NULL) {
		ptr2 = ptr1;
		while(ptr2->next != NULL) {
			if(ptr1->data == ptr2->next->data) {
				dup = ptr2->next;
				ptr2->next = ptr2->next->next;
				free(dup);
			}
			else {
				ptr2 = ptr2->next;
			}
		}
		ptr1 = ptr1->next;
	}
}

void print_stack(stack *s, char *delim) {
	stack *ptr;
	for(ptr = s; ptr; ptr = ptr->next)
		printf("%c%s", ptr->data, ptr->next ? delim : "");
}
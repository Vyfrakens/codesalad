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

void clean_stack(stack *s) {
	stack *i, *j;
	char temp;
	// Sorting
	for(i = s; i; i = i->next)
		for(j = i->next; j; j = j->next)
			if(i->data > j->data){
				temp = i->data;
				i->data = j->data;
				j->data = temp;
			}
	// Remove duplicates
	for(i = s; i; i = i->next) 
		while(i->next && i->data == i->next->data)
			i->next = i->next->next;
}

void print_stack(stack *s, char *delim) {
	stack *ptr;
	for(ptr = s; ptr; ptr = ptr->next)
		printf("%c%s", ptr->data, ptr->next ? delim : "");
}
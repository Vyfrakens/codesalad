#include<stdio.h>
#include<stdlib.h>
struct stack{
	int info;
	struct stack *link;
};
typedef struct stack stack;
void push(stack**, int);
int pop(stack**);
void display(stack*);
int main() {
	int ch, e;
	stack *s = NULL;
	printf("STACK:\n\t1. Push\n\t2. Pop\n\t3. Display\n\t4. Exit\n\n");
	do {
		printf("Enter your choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
			printf("Enter the element to be pushed: ");
			scanf("%d", &e);
			push(&s, e);
			display(s);
			break;
			case 2:
			printf("The element popped is %d\n", pop(&s));
			display(s);
			break;
			case 3:
			printf("The current stack is:\n");
			display(s);
			break;
			case 4:
			printf("Quiting...\n");
			break;
			default:
			printf("Wrong Choice!!!");
		}
	}while(ch!=4);
}
void push(stack **top, int item) {
	stack *temp;
	temp = (stack*) malloc(sizeof(stack));
	temp->info = item;
	temp->link = *top;
	*top = temp;
}
int pop(stack **top) {
	stack *temp = *top;
	int item;
	if(!top) printf("Stack Underflow\n");
	item = (*top)->info;
	*top = (*top)->link;
	return item;
}
void display(stack *top) {
	stack *ptr;
	if(!top) printf("Stack is Empty");
	else
		for(ptr=top; ptr; ptr=ptr->link)
			printf("%d ", ptr->info);
	printf("\n");
}
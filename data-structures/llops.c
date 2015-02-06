#include<stdio.h>
#include<stdlib.h>
struct list{
	int info;
	struct list *link;
};
typedef struct list list;
void insert_beg(list**, int);
void insert_end(list**, int);
void insert_before(list**, int, int);
void insert_after(list**, int, int);
int delete_beg(list**);
int delete_end(list**);
int delete_item(list**, int);

list *create_node(int, list*);
int delete_node(list**);

void display(list*);
int main() {
	int ch, e, t;
	list *l = NULL;
	printf("LINKED LIST OPERATIONS:\n\t1. Insert\n\t2. Delete\n\t3. Display\n\t4. Exit\n\n");
	do {
		printf("Enter your choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
			printf("Enter the element to be inserted: ");
			scanf("%d", &e);
			printf("Insert at: ");
			scanf("%d", &ch);
			switch(ch) {
				case 1:
				insert_beg(&l, e);
				break;
				case 2:
				insert_end(&l, e);
				break;
				case 3:
				printf("Enter the element before which, the element is to be inserted: ");
				scanf("%d", &t);
				insert_before(&l, e, t);
				break;
				case 4:
				printf("Enter the element after which, the element is to be inserted: ");
				scanf("%d", &t);
				insert_after(&l, e, t);
				break;
				default:
				printf("Wrong Choice!!!");
			}
			ch = 1;
			display(l);
			break;
			case 2:
			printf("Delete from: ");
			scanf("%d", &ch);
			switch(ch) {
				case 1: e = delete_beg(&l); break;
				case 2: e = delete_end(&l); break;
				case 3:
				printf("Enter the element to be deleted: ");
				scanf("%d", &t);
				e = delete_item(&l, t);
				break;
				default:
				printf("Wrong Choice!!!\n");
			}
			printf("The element deleted is %d\n",e);
			display(l);
			ch = 2;
			break;
			case 3:
			printf("The current list is:\n");
			display(l);
			break;
			case 4:
			printf("Quiting...\n");
			break;
			default:
			printf("Wrong Choice!!!\n");
		}
	}while(ch!=4);
}
void insert_beg(list**head, int e) {
	*head = create_node(e, *head);
}
void insert_end(list**head, int e) {
	list *ptr;
	if(!head) 	*head = create_node(e, *head);
	else {
		for(ptr=*head; ptr->link; ptr = ptr->link);
		ptr->link = create_node(e, NULL);
	}
}
void insert_before(list**head, int e, int r) {
	list *ptr, *prev;
	for(ptr=*head, prev = NULL; ptr && ptr->info!=r; prev = ptr, ptr = ptr->link);
	if(!ptr) printf("Element not found\n");
	else if(!prev)
		(*head) = create_node(e, ptr);
	else
		prev->link = create_node(e, ptr);
}
void insert_after(list**head, int e, int l) {
	list *ptr;
	for(ptr=*head; ptr && ptr->info!=l; ptr = ptr->link);
	if(!ptr) printf("Element not found\n");
	else
		ptr->link = create_node(e, ptr->link);
}

int delete_beg(list**head) {
	list *ptr = *head;
	if(!(*head)) printf("Underflow\n");
	else
		return delete_node(head);
	return 0;
}
int delete_end(list**head) {
	list *ptr;
	if(!(*head)) printf("Underflow\n");
	else if(!(*head)->link) return delete_node(head);
	else {
		for(ptr = *head; ptr->link->link; ptr = ptr->link);
		return delete_node(&(ptr->link));
	}
	return 0;
}
int delete_item(list**head, int d) {
	list *ptr, *prev;
	for(ptr=*head, prev = NULL; ptr && ptr->info!=d; prev = ptr, ptr = ptr->link);
	if(!ptr) printf("Underflow\n");
	else if(!prev) return delete_node(head);
	else return delete_node(&(prev->link));
	return 0;
}

list *create_node(int e, list*l) {
	list *temp = (list*) malloc(sizeof(list));
	temp->info = e;
	temp->link = l;
	return temp;
}
int delete_node(list**node) {
	list *temp = *node;
	int e = (*node)->info;
	(*node) = (*node)->link;
	free(temp);
	return e;
}

void display(list *head) {
	list *ptr;
	if(!head) printf("List is Empty");
	else
		for(ptr = head; ptr; ptr = ptr->link)
			printf("%d ", ptr->info);
	printf("\n");
}
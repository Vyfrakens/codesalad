#include <stdio.h>
#include <stdlib.h>
struct tree {
	int info;
	struct tree *lc;
	struct tree *rc;
};
typedef struct tree tree;
struct stack{
	tree *info;
	struct stack *link;
};
typedef struct stack stack;
tree *create_tree();
void create_bst(tree**);
void trav_preorder(tree*);
void trav_inorder(tree*);
void trav_postorder(tree*);
void traverse(tree*);

void push(tree*);
tree* pop();
void display();
void iterativePreorder(tree*);
void iterativeInorder(tree*);
void iterativePostorder(tree*);


void insert(tree**, int);
void delete(tree**, int);

int main (int argc, char const *argv[]) {
	tree *t;// = create_tree(t);
	create_bst(&t);
	traverse(t);
	int ch, n;
	printf("BST:\n\t1. Insert\n\t2. Delete\n\t3. Traverse\n\t4. Exit\n\n");
	do {
		printf("Enter choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
			printf("Enter the element to be inserted: ");
			scanf("%d", &n);
			insert(&t, n);
			traverse(t);
			break;
			case 2:
			printf("Enter the element to be deleted: ");
			scanf("%d", &n);
			delete(&t, n);
			traverse(t);
			break;
			case 3:
			traverse(t);
			break;
			case 4:
			printf("Quiting...\n");
			break;
			default:
			printf("Wrong Choice!!!\n");
		}
	} while(ch!=4);
	traverse(t);
	return 0;
}
tree *create_tree() {
	char ch;
	tree *node = (tree*) malloc(sizeof(tree));
	printf("Enter element: ");
	scanf("%d", &node->info);
	printf("Does %d have left child (Y/N)? ", node->info);
	scanf(" %c", &ch);
	if(ch=='y'||ch=='Y') node->lc = create_tree();
	printf("Does %d have right child (Y/N)? ", node->info);
	scanf(" %c", &ch);
	if(ch=='y'||ch=='Y') node->rc = create_tree();
	return node;
}
void create_bst(tree**t) {
	int i, n, e;
	printf("Enter no. of elements: ");
	scanf("%d", &n);
	printf("Enter Elements: ");
	for(i=0; i<n; ++i) {
		scanf("%d", &e);
		insert(t, e);
	}
}
void insert(tree **leaf, int e) {
	if(!(*leaf)) {
		(*leaf) = (tree*) malloc(sizeof(tree));
		(*leaf)->info = e;
		(*leaf)->lc = (*leaf)->rc = NULL;
	}
	else if(e>(*leaf)->info) insert(&(*leaf)->rc, e);
	else if(e<(*leaf)->info) insert(&(*leaf)->lc, e);
}
void delete(tree **leaf, int e) {
	tree *ptr;
	if(!(*leaf)) printf("Elemnent not found\n");
	else if(e>(*leaf)->info) delete(&(*leaf)->rc, e);
	else if(e<(*leaf)->info) delete(&(*leaf)->lc, e);
	else {
		if((*leaf)->lc&&(*leaf)->rc) {
			ptr = (*leaf)->rc;
			while(ptr->lc) ptr = ptr->lc;
			(*leaf)->info = ptr->info;
			delete(&(*leaf)->rc, (*leaf)->info);
		}
		else {
			ptr = *leaf;
			if(!(*leaf)->lc) (*leaf) = (*leaf)->rc;
			else if(!(*leaf)->rc) (*leaf) = (*leaf)->lc;
			free(ptr);
		}
	}
}

void trav_preorder(tree *t) {
	if(t) {
		printf("%d ", t->info);
		trav_preorder(t->lc);
		trav_preorder(t->rc);
	}
}
void trav_inorder(tree *t) {
	if(t) {
		tarv_inorder(t->lc);
		printf("%d ", t->info);
		trav_inorder(t->rc);
	}
}
void trav_postorder(tree *t) {
	if(t) {
		trav_postorder(t->lc);
		trav_postorder(t->rc);
		printf("%d ", t->info);
	}
}
void iterativePreorder(tree *t) {
    stack parentStack;
    int top=-1;
    while ( *t ) {
        printf( "%d ", t->info );
        if ( t->rc )
            push(t->rc);
        if ( t->lc ) 
            push(t->lc);
        t = pop();
    }
}
void iterativeInorder(tree *t) {
    stack parentStack;
    while (not parentStack.isEmpty() || *t) {
        if (*t) {
            push(t->info);
            *t = t->lc;
        } else {
            *t = pop();
            printf(t->info);
            *t = t->rc;
        }
    }           
}                  
                                      
void iterativePostorder(tree *t) {
    stack parentStack;
    lastnodevisited = null;
    while (!parentStack.isEmpty() || *t) {
        if (*t) {
            parentStack.push(node);
            t = t->lc;
        } else {
            peeknode = parentStack.peek();
            if (peeknode.rc != null and lastnodevisited != peeknode.rc)
                /* if right child exists AND traversing node from left child, move right */
                node = peeknode.rc;
            else {
                parentStack.pop();
                visit(peeknode);
                lastnodevisited = peeknode;
            }
        }
    }
}
                   
void traverse(tree*t){
	printf("\nPreorder  : ");
	preorder(t);
	printf("\nInorder   : ");
	inorder(t);
	printf("\nPostorder : ");
	postorder(t);
	printf("\n");
}

#include <stdio.h>
#include <stdlib.h>
struct bintree {
	int info;
	struct bintree *lc;
	struct bintree *rc;
} *root;
typedef struct bintree bintree;
bintree *create_bintree(bintree*, int);
int main (int argc, char const *argv[])
{
	int x;
	printf("Enter root node: ");
	scanf("%d", &x);
	root = (bintree*) malloc(sizeof(bintree));
	create_bintree(root, x);
	return 0;
}
bintree *create_bintree(bintree *node, int item) {
	char ch;
	node->info = item;
	printf("Does %d have left child (Y/N)? ", item);
	scanf(" %c", &ch);
	if(ch=='y'||ch=='Y') {
		node->lc = (bintree*) malloc(sizeof(bintree));
		printf("Enter left child: ");
		scanf("%d", &item);
		create_bintree(node->lc, item);
	}
	printf("Does %d have right child (Y/N)? ", item);
	scanf(" %c", &ch);
	if(ch=='y'||ch=='Y') {
		node->rc = (bintree*) malloc(sizeof(bintree));
		printf("Enter right child: ");
		scanf("%d", &item);
		create_bintree(node->rc, item);
	}
	return node;
}
#include<stdio.h>
void main() {
	int a[10],b[10],n,i;
	printf("Enter Array Size: ");
	scanf("%d",&n);
	printf("\n Enter Elements: \n");
	for(i=0;i<n;i++) 
		scanf("%d",&a[i]);
	
	for(i=0;i<n;i++) 
		b[n-i-1]=a[i];
	
	printf("\n Reversed Array \n");
	for(i=0;i<n;i++) 
		printf("%d ",b[i]);
	
	
	
}
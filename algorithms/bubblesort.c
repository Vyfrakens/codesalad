#include <stdio.h>
int main() {
	int i, j, n=10, a[n], temp;
	printf("Enter 10 numbers: ");
	for(i=0; i<n; ++i)
		scanf("%d", &a[i]);
	for(i=0; i<n-1; ++i)
		for(j=0; j<n-i-1; ++j)
			if(a[j]>a[j+1]) {
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
	printf("Sorted array: ");
	for(i=0; i<n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}
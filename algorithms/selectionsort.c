#include <stdio.h>
int main() {
	int i, j, n=10, a[n], pos, temp;
	printf("Enter 10 numbers: ");
	for(i=0; i<n; ++i)
		scanf("%d", &a[i]);
	for(i=0; i<n-1; ++i) {
		for(j=i+1, pos=i; j<n; ++j) {
			if(a[pos]>a[j])
				pos = j;
		}
		if(pos!=i) {
			temp = a[i];
			a[i] = a[pos];
			a[pos] = temp;
		}
	}
	printf("Sorted array: ");
	for(i=0; i<n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}
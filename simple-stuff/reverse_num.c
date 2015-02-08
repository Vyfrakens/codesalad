#include<stdio.h>

main() {
	int num, res=0;
	printf("Enter a number : ");
	scanf("%d", &num);
	int numcopy = num;
	while(num > 0) {
		res = res*10 + num%10;
		num/=10;
	}
	printf("%d ==> %d\n", numcopy, res);
}

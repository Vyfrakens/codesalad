#include <stdio.h>
int max(x,y)
int x, y;
{
	return (x>y ? x : y);
}

int main(int argc, char const *argv[])
{
	int result = max(5, 4);
	printf("%d\n", result);
	return 0;
}

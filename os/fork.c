#include "stdio.h"
#include "unistd.h"

int main() {
	pid_t pid;
	int i = 0, n;
	printf("Enter n: ");
	scanf("%d", &n);

	if((pid = fork ()) < 0) 
		return -1;

	char ch = pid == 0 ? 'C' : 'P';

	if(pid == 0) {
		i = 100;
		n += 100;
	}

	printf("pid = %d (%c)\n", pid, ch);
	printf("getpid() = %d (%c)\n", getpid(), ch);
	printf("getppid() = %d (%c)\n", getppid(), ch);

	while(i < n) {
		printf("%d (%c)\n", i++, ch);
		usleep(100000);
	}

	return 0;
}


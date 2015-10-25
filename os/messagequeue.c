#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	char msg[80];
	mqd_t fd = mq_open("/chat", O_RDWR | O_CREAT, 0777, NULL);

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <server/client>\n", argv[0]);
		return -1;
	}

	if(strcmp(argv[1], "server") == 0) {
		printf("Server:\n");
		while(1) {
			fgets(msg, sizeof(msg), stdin);
			mq_send(fd, msg, strlen(msg) + 1, 0);
			mq_receive(fd, msg, 8192, 0);
			printf("%s", msg);
		}
	}
	else if(strcmp(argv[1], "client") == 0) {
		printf("Client:\n");
		while(1) {
			mq_receive(fd, msg, 8192, 0);
			printf("%s", msg);
			fgets(msg, sizeof(msg), stdin);
			mq_send(fd, msg, strlen(msg) + 1, 0);
		}
	}
	mq_close(fd);
	mq_unlink("/chat");
	return 0;
}
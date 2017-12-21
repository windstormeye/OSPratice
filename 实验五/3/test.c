#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main() {
	int pid, fd[2];
	char buf[100];
	char parent[] = "233333";
	// 打开了一个读端和一个写端
	pipe(fd);
	// 可选择阻塞读终端的方式从终端接收用户输入
	// read(STDIN_FILENO, parent, 10);
	pid=fork();
	// 父进程
	if(pid > 0) {
		// 管道不可同时开启读写两端
		close(fd[0]);
		printf("父进程发送 %s 给子进程\n", parent);
		write(fd[1],parent,sizeof(parent));
		close(fd[1]);
		printf("父进程等待子进程结束...\n");
		// 等待子进程结束
		wait(0);
		printf("父进程结束\n");
	// 子进程
	} else if(pid == 0) {
		// 管道不可同时开启读写两端
		close(fd[1]);
		read(fd[0],buf,100);
		printf("子进程收到父进程发送的消息为 %s\n ",buf);
		close(fd[0]);
		printf("子进程结束\n");
	} else {
		printf("子进程创建失败\n");
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
	int p1, p2;
	int i, n=0;
	p1 = fork();
	// fork返回值为0，子进程
	if(p1 == 0) {
	// execl函数会取代执行它的当前进程，如果该函数执行成功直接结束，执行失败则继续，需要手动exit
	// execl()用来执行参数path 字符串所代表的文件路径, 其它参数代表执行该文件时传递过去的argv参数，最后一个参数需置空
	printf("我是子进程\n");
	execl("/bin/ls","ls","-l",0);
	// 验证
	execl("/bin/cat","cat","file2.txt",0);
	exit(1);
	// fork返回值大于0，父进程
	} else if(p1 > 0) {
		printf("我是父进程\n");
		// wait(int *status)，只要有子进程退出及结束等待
		// 指定等待子进程结束可使用waitpid()
		wait(NULL);
		for(i = 1; i <= 100; i++) {
			n = n + i;
		}
		printf("the add of 1-100 is:%d\n",n);
		execl("/bin/cat","cat","file1.txt",0);
	// 小于0，进程分叉错误
	} else
		printf("fork failed.\n");
	return 0;
}
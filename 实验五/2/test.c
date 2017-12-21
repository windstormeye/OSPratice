#include <unistd.h>
#include <stdio.h>
int main() {
	int p1, p2;
	p1 = fork();
	if(p1 == 0) {
		printf("我是子进程son\n");
	} else if(p1 > 0) {
		p2 = fork();
		if(p2 == 0) {
			printf("我是子进程daughter\n");
		} else if(p2 > 0) {
			printf("我是父进程parent\n");
		}
	}
	else
		printf("进程创建失败\n");
	return 0;
}
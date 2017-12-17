#include <sys/stat.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h> 
#include <time.h> 
#include <errno.h> 
extern int errno;  

int main(int argc,char* argv[]) {  
	struct stat buf1,buf2,buf3,buf4;  
	char* file1 = argv[2];
	char* file2 = argv[3];
	char* file3 = argv[4];
	if (argc != 5) {         
		printf("正确输入为: link oldFile linkFile symlinkFile\n");       
		exit(1);     
	}  
	// 进行硬链接  
	if (link(file1, file2) == -1) {       
		printf("硬链接错误，错误码为：%d\n", errno);    
	}    
	// 进行符号连接
	if (symlink(file1, file3) == -1) {       
		printf("符号链接错误，错误码为：%d\n", errno);     
	}  
	// 获取链接所指向的文件信息。需要写明文件路径，而不是使用open函数完后的文件描述符
	// 使用逻辑或 | 而不是 || 。必须要保证file2和file3都说是可以获取到文件状态信息。
	if((stat(file2, &buf1) == -1) | (stat(file3, &buf2) == -1)) {   
		printf("获取文件状态信息错误，错误码为：%d\n",errno);   
		exit(1);  
	}  
	printf("%s和%s的文件信息\n", file2, file3);  
	printf("%s的文件大小为：%d\n", file2, (int)buf1.st_size);  
	printf("%s的文件大小为：%d\n", file3, (int)buf2.st_size);  
	printf("%s的文件索引节点号为：%d\n", file2, (int)buf1.st_ino);  
	printf("%s的文件索引节点号为：%d\n", file3, (int)buf2.st_ino);  
	printf("%s文件的权限为：%d\n", file2, (int)buf1.st_mode);  
	printf("%s文件的权限为：%d\n", file3, (int)buf2.st_mode);  
	printf("%s文件的所在设备号为：%d\n", file2, (int)buf1.st_dev);  
	printf("%s文件的所在设备号为：%d\n", file3, (int)buf2.st_dev);  
	printf("%s文件的最后一次修改时间为：%d\n", file2, (int)buf1.st_mtime);  
	printf("%s文件的最后一次修改时间为：%d\n", file3, (int)buf2.st_mtime);
	if((lstat(file2, &buf3) == -1) | (lstat(file3, &buf4) == -1)) {   
	 	printf("lstar error\nerrno is %d\n",errno);  
	 	exit(1);  
	}  
	// 打印链接文件本身信息
	printf("===========================\n");  
	printf("%s和%s的文件信息\n", file2, file3);  
	printf("%s的文件大小为：%d\n", file2, (int)buf3.st_size);  
	printf("%s的文件大小为：%d\n", file3, (int)buf4.st_size);  
	printf("%s的文件索引节点号为：%d\n", file2, (int)buf3.st_ino);  
	printf("%s的文件索引节点号为：%d\n", file3, (int)buf4.st_ino);  
	printf("%s文件的权限为：%d\n", file2, (int)buf3.st_mode);  
	printf("%s文件的权限为：%d\n", file3, (int)buf4.st_mode);  
	printf("%s文件的所在设备号为：%d\n", file2, (int)buf3.st_dev);  
	printf("%s文件的所在设备号为：%d\n", file3, (int)buf4.st_dev);  
	printf("%s文件的最后一次修改时间为：%d\n", file2, (int)buf3.st_mtime);  
	printf("%s文件的最后一次修改时间为：%d\n", file3, (int)buf4.st_mtime);  
 } 



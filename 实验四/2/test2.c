#include <sys/stat.h>  
#include <unistd.h> 
#include <stdlib.h>   
#include <stdio.h>  
#include <errno.h> 
#include <time.h>   
#include <string.h>

int main(int argc,const char* argv[]) {         
	struct stat buf1,buf2;
	const char *file1, *file2;
	file1 = argv[2];
	file2 = argv[3];
    if ( argc != 4 || strcmp("rename", argv[1]) ) {
        printf("正确形式为: rename file1 file2\n");
        exit(1);
	}
	/*
	 * stat()函数：获取文件状态，详细内容见度娘🙂
	 * const char *: 文件名
	 * struct stat *: stat结构体变量
	 * 成功执行返回0，失败返回-1
	 */
	if(stat(file1,&buf1) == -1) {   
		printf("获取%s状态失败，错误码为：%d\n", file1 ,errno);   
		exit(1);  
	}  
	printf("%s的文件状态如下所示：\n", file1);  
	printf("%s的大小为：%d\n", file1, (int)buf1.st_size);  
	printf("%s的索引节点号好：%d\n", file1, (int)buf1.st_ino);  
	printf("%s最后一次修改时间为：%d\n", file1, (int)buf1.st_mtime);   
	/*
	 * rename()函数
	 * char * old: 旧文件路径
	 * char * new: 新文件路径
	 * 成功返回0，否则返回-1
	 * 如果new指定的文件存在，则会被删除
	 * 如果new与old不在一个目录下，则相当于移动文件
	 */
	if(rename(file1, file2) == -1){  
		printf("重命名失败，错误码为：%d\n",errno);      
		exit(1);   
	}   
	printf("重命名成功！\n");
	if(stat(file2 ,&buf2) == -1) {   
		printf("获取%s状态失败，错误码为：%d\n", file2, errno);   
		exit(1);  
	}  
	printf("%s的文件状态如下所示：\n", file2);  
	printf("%s的大小为：%d\n", file2, (int)buf1.st_size);  
	printf("%s的索引节点号好：%d\n", file2, (int)buf1.st_ino);  
	printf("%s最后一次修改时间为：%d\n", file2, (int)buf1.st_mtime);
	return 0;  
} 
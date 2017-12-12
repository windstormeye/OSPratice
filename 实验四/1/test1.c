/*
 * copy file1 file2 file3 off_size
 */


#include <fcntl.h> 
#include <stdlib.h>   
#include <errno.h>  
#include <stdio.h>  
#include <unistd.h>
#include <string.h>  
#include <math.h>

// ASCII码计算宏
#define PJCTN(x) (x-'0')

int main(int argc, char const *argv[])   {   
	int file1,file2,file3;   
	// 判断传入参数是否达到5个及命令是否为copy
	if ( argc != 6 || strcmp("copy", argv[1]) ) {         
		printf("正确形式为: copy file1 file2 file3\n");      
		exit(1);    
	}
	// 根据传入参数内容取值     
	/*
	 * open函数
	 * 引用格式: #include <fcntl.h>
	 * const char *: 文件名
	 * int : 文件mode（选择打开方式）
	 */
	// 只读打开
	file1 = open( argv[2], O_RDONLY );    
	// 只读打开
	file2 = open( argv[3], O_RDONLY );    
	// 若文件不存在则创建 | 以可读可写打开 | 所有者可读可写可执行
	file3 = open( argv[4], O_CREAT|O_RDWR, S_IRWXU );    
	
	int off_i = 0;
	long argv_sum = 0;
	char * numString = (char *)argv[5];
	while (numString[off_i] != '\0') {
		off_i ++;
	}
	int off_temp = 0;
	while (off_temp != off_i) {
		int temp = PJCTN(numString[off_temp]);
		argv_sum = argv_sum + (temp * pow(10, off_i - off_temp - 1));
		off_temp ++;
	}

	// 最好好用int *，能够保证计算出的文件字节数较大
	long n;
	// 此处最好也是char *，让文件缓冲区能够保证尽可能的充裕
	char buf[1024];  
	/*
	 * read函数（低级IO，也即无缓冲IO）
	 * 引用格式: #include <unistd.h>
	 * int : 文件描述词（用于唯一标识文件）
	 * void *: 文件内容区域块指针（存放文件内容区域）
	 * size_t : 读取文件内容中从零到第几个字节
	 * 返回值：代表读取到的字节数（不出意外，应该申请读取多少字节数，返回读取到的字节数）
	 */ 
	while ( (n = read(file1, buf, 1024)) > 0 )   
		/*
		 * write函数
		 * 引用格式:#include <unistd.h>
		 * int : 文件描述词（用于唯一标识文件）
		 * void *: 文件内容区域块指针
		 * size_t: 从文件内容区域块中读取的字节数
		 * 返回值：<0，写入部分或全部内容。>0,根据error值做判断
		 */
		if ( write(file3, buf, n) != n )    
		printf("写入错误\n");     
	if ( n < 0 )     
		// 此处errno为宏，在对应的.h文件中使用过该宏，直接po出的errno能够打印出该功能产生的错误码
		printf( "写入文件%s时出错\n错误码为：%d\n", argv[1], errno );            
	/*
	 * lseek函数
	 * int: 文件描述词（用于唯一标识文件）
	 * off_t: 偏移量（其实就是long long，64位int）
	 * int: 位移读写标识偏移参数（SEEK_END为文件末尾再追加off_t个字节数）
	 * 当成功时则返回当前的读写位置, 即距离文件开头多少个字节。若错误则返回-1, errno 会存放错误代码.
	 */
	if ( lseek(file3, argv_sum, SEEK_END) == -1 )   
		printf("移动文件读写位置出错，错误码为：%d\n", errno);    
	while (( n = read(file2,buf,1024)) > 0)  
		if ( write(file3, buf, n) != n )     
			printf("写入错误，错误码为：%d\n", errno);     
		if (n < 0)     
			printf("读取文件%s错误\n错误码为：%d\n", argv[2], errno);     
		// 数据写回磁盘, 并释放该文件所占用的资源. 参数int 为先前由open()或creat()所返回的文件描述词.        
		close(file1);    
		close(file2);    
		close(file3);    
		printf("操作成功！\n");   
		return 0;  
	}
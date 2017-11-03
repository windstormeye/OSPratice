#!/bin/bash

function menu() {
	echo "--------------------------------------------"
	curday=`date +%d/%m/%Y`
  
	printf "USER:${USER}	HOST:" 
	echo -n $(/sbin/ifconfig -a|grep inet|grep -v 127.0.0.1|grep -v inet6|awk '{print $2}'|tr -d "地址:")
    	printf "    DATE:${curday}\n"
	echo "--------------------------------------------"
	echo "	A:创建子目录并复制文件"
	echo "	B:文件权限测试"
	echo "	C:文件字符转换"
	echo "	D:文件总数及文本行数统计"
	echo "	E:文件查找"
	echo "	Q:推出系统"
}

function userChmodTest() {
	echo -n "请输入需要进行权限测试的文件路径:"
	read DIR
	if [ -r $DIR ]
	then
		echo "您可对该文件进行读操作"
	else 
		echo "您没有对该文件的读操作"
	fi
	if [ -w $DIR ]
	then
		echo "您可对该文件进行写操作"
	else
		echo "您没有对该文件的写操作"
	fi
	if [ -x $DIR ]
	then
		echo "您可对该文件进行执行"	 
	else 
		echo "您没有该文件的执行操作"
	fi
}

function mkChildDir() {
	path="../pjpjpj"
	# 判断当前目录是否存在
	if [ -d $path ]
	then
		echo "目录已存在,其具备的权限为:"
		if [ -r $path ]
	        then
        	        echo "您可对该文件进行读操作"
        	else
                	echo "您没有对该文件的读操作"
        	fi
        	if [ -w $path ]
        	then
                	echo "您可对该文件进行写操作"
        	else
                	echo "您没有对该文件的写操作"
        	fi
        	if [ -x $path ]
       		then
                	echo "您可对该文件进行执行"      
        	else
                	echo "您没有该文件的执行操作"
        	fi

	else 
		mkdir ../pjpjpj
		chmod 777 ../pjpjpj
		cat ./file1.txt ./file2.txt > ../pjpjpj/pjpjpj.txt
		:>./file1.txt :>file2.txt
		echo "转换成功,请在相应文件夹中查看"
	fi	
}

function lowerTohigher {
	cat file1.txt | tr a-z A-Z > newfile1.txt
	cat file2.txt | tr a-z A-Z > newfile2.txt
}

function allOfFileAndTextRow {
	echo -n "/dev目录下的目录文件数共有:"
	cd /dev 
	ls -l |grep "^d"|wc -l

	echo -n "/dev目录下的符号链接文件数共有:"
	find /dev -type l|wc -l

	echo -n "当前目录下的text.txt文件中的空行数有:"
	grep '^$' /home/pjpjpj/test2/text.txt | wc -l

	echo "系统中所有的环境变量为:"
	env
}

function findDir() {
	cd /dev
	find /dev -name 's????' | xargs file
}


################## main ##################
menu
while read ANSWER
do
	if [ "$ANSWER" = "A" -o "$ANSWER" = "a" ]
	then
		mkChildDir
	elif [ "$ANSWER" = "B" -o "$ANSWER" = "b" ]
	then
		userChmodTest
	elif [ "$ANSWER" = "C" -o "$ANSWER" = "c" ]
	then
		lowerTohigher
	elif [ "$ANSWER" = "D" -o "$ANSWER" = "d" ]
	then
		allOfFileAndTextRow
	elif [ "$ANSWER" = "E" -o "$ANSWER" = "e" ]
	then
		findDir
	elif [ "$ANSWER" = "Q" -o "$ANSWER" = "q" ]
	then
		echo "再见${USER},欢迎下次使用"
		exit 1
	fi
	menu
done

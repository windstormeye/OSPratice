#!/bin/bash

echo "请输入查找的内容所在目录:"
read DIR 
cd $DIR
echo "请输入需要在当前目录查找的内容:"
read CONTENT
grep -rn "$CONTENT" *


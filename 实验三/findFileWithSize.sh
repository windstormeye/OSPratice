#!/bin/bash

echo -n "请输入需要进行搜索的大小:"
read SIZE
echo -n "请输入需要进行搜索的路径:"
read DIR
cd $DIR
find $DIR -size +$SIZE -print  


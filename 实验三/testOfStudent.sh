#!/bin/bash 
SAVEDIFS=$IFS 
IFS=: 
uCOUNT1301=0 
COUNT1302=0 
COUNT1303=0 
COUNT1=0 
COUNT2=0 
COUNT3=0 
RATE1=0 
RATE2=0 
RATE3=0 
while read STUDENT CLASS GRADE 
do  
	case $CLASS in
	       	1301)       
		COUNT1301=`expr $COUNT1301 + 1`
       		;;
       		1302)
       		COUNT1302=`expr $COUNT1302 + 1` 
		;;
		1303)
       		COUNT1303=`expr $COUNT1303 + 1`       
		;; 
	esac
	echo $CLASS 
	if [ "$CLASS" -eq 1301 ]&&[ "$GRADE" -ge 90 ] 
	then 
		COUNT1=`expr $COUNT1 + 1`
		echo "$COUNT1 1301" 
	elif [ "$CLASS" -eq 1302 ]&&[ "$GRADE" -ge 90 ] 
	then 
		COUNT2=`expr $COUNT2 + 1`
	     	echo "$COUNT2 1302"  
	elif [ "$CLASS" -eq 1303 ]&&[ "$GRADE" -ge 90 ] 
	then 
		COUNT3=`expr $COUNT3  + 1` 
		echo "$COUNT3 1303" 
	fi 
done < ./pc.txt

	RATE1=`expr $COUNT1 / $COUNT1301 \* 100`
        RATE2=`expr $COUNT2 / $COUNT1302 \* 100`
        RATE3=$(printf "%d" `echo "scale=2;${COUNT3}/${COUNT1303} * 100"|bc`) 
IFS=SAVDEIFS 
echo "各个班级选课的学生人数" 
echo "1301 = $COUNT1301" 
echo "1302 = $COUNT1302" 
echo "1303 = $COUNT1303" 
echo "各个班级的优秀率为" 
echo "1301 = $RATE1%" 
echo "1302 = $RATE2%" 
echo "1303 = $RATE3%" 

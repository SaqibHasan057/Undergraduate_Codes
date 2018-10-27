#! /bin/bash

#The following program takes input from the user until the input is zero and 
# calcuates the sum of all positive inputs

sum=0

while [ 1 ]
do
	read a
	if [ $a -eq 0 ];then
		break
	fi
	if [ $a -lt 0 ];then
		continue
	fi
	sum=`expr $sum + $a`
done

echo sum is $sum
	

#! /bin/bash

for i in *; do
if [ -f "$i" ];then
	echo "$i" | grep -q [0-9]
	if [ $? = 0 ];then
		rm "$i"
	fi
fi
done

#!/bin/bash

# This is one of many ways to solve the problem. Your solution may be different.
# Notice the use of quotes to allow filenames with space in them. 

recursive_name_change()
{
	cd "$1"
	for i in *
	do
		#echo "${i##*.}"
		if [ -d "$i" ]
		then
			recursive_name_change "$i"
		elif [ "${i##*.}" = "cpp" ]
		then
			new_name=${i%.*}".c"
			mv "$i" "$new_name"
		fi
	done
	cd ../
}

recursive_name_change .


# Try the same problem using pushd and popd instead of explicit recursive function.

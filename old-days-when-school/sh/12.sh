#!/bin/bash

#test01
#basic for command
for test in Alabama Alaska Arizona Arkansas California Colorado
do
	echo "The test state is $test"
done
echo -e '\n'

#test01b
#testing the for variavle after the looping
for test in Alabama Alaska Arizona Arkansas California Colorado
do
	echo "The test state is $test"
done
echo "The last state we visit was $test"
test=Connecticut
echo "Wait.now we're visiting $test"
echo -e '\n'

#test02
#annother example of how not to use the for command
for testfor in i don't know if this'll work
do
	echo "word : $testfor"
done
echo -e '\n'

#test02b
#annother example of how not to use the for command
for testfor in i don\'t know if "this'll" work
do
	echo "word : $testfor"
done
echo -e '\n'

#test03
#
list="Alabama Alaska Arizona Arkzona Arkansas Colorado"" Connecticut"
#list=$list" Connecticut"
for state in $list
do
	echo "Have you ever visited $state?"
done
echo -e '\n'

#test
#
for filename in `ls`
do
	echo "$filename"
done
echo -e '\n'

IFSOLD=$IFS
IFS=\n::
echo $IFS
IFS=IFSOLD

#test06
#iterate through all the files in a directory
for file in ~/work/unp_1/*
do
	if [ -d "$file" ]
	then 
		echo "$file is a directory"
	elif [ -f "$file" ]
	then
		echo "$file is a file"
	fi
done

#test08
#test the C-Style for loop
for ((i = 1, j = 9; i < 10; i++, j--))
do
	echo "$i $j"
done

#test09
#while
#while [ 0 ]
#do
#	echo "***"
#done

#test10
#until
var=100
until [ $var -eq 0 ]
do
	echo "$var"
	var=$[ $var - 25 ]
done






















exit 0

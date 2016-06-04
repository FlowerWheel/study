#!/bin/bash

#test01
factorial=1
if [ -n "$1" ]
then 
	echo "$1"
else
	echo "have not arg 1"
	exit 1
fi
for (( number = 1; number<=$1; number ++))
do
	factorial=$[ $factorial * $number]
done
echo $factorial

echo `basename $0`
echo $#

exit 0

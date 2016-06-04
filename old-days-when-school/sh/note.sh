#!/bin/bash

if command
then
	commands
fi

if command
then
	commands
elif
then
	commands
else
	commands
fi

test condition #测试条件 数值比较 字符串比较 文件比较
[condition] #测试条件

(()) [[]]

case variable in
	pattern1 | pattern2)
		cmd1;;
	pattern3 | pattern2)
		cmd2;;
esac

for variable in list
do
	commands
done

for (( ; ; )) # c style for
do
	commands
done

while test command
do 
	commands
done

until test command
do
	commands
done

break n
continue n

$0 $1 $2 $3 ... $9 ${10} ${11} ...
$* $@

shift n

getopt 
getopts

read variable

basenme $0

#!/bin/bash

echo -e '\r'
#test01
#testint the if statement
if 
	date
then 
	echo "it worked"
fi

echo -e '\r'
#test02
#testing a bad command
if 
	asdf
then
	echo "id did not work"
fi
echo "we are outside of the if statement"

echo -e '\r'
#test03
#test multiple commands in the then section
testuser=lyj
if (grep $testuser /etc/passwd) then
	echo The bash file for user $testuser are:
	ls -a /home/$testuser/.b*
fi

echo -e '\r'
#test04
#testing the else section
testuser=llyj
if (grep $testuser /etc/passwd) then
	echo The bash files for user $testuser are:
	ls -a /home/$testuser/.b*
else
	echo "The user name $testuser does not exist on this system"
fi

echo -e '\r'
#test05
#using numeric test comparisons
val1=11
val2=13
val3=12

if [ $val2 -gt $val1 ]
then
	echo "************"
fi

if (test $val1 -gt 5)
then
	echo "The test value $val1 is greater than 5"
fi

if (test $val2 -eq $val3)
then
	echo "$val2 == $val3"
elif (test $val2 -gt $val3)
then
	echo "$val2 > $val3"
elif (test $val2 -lt $val3) 
then
	echo "$val2 < $val3"
else 
	echo "unkown"
fi

echo -e '\r'
#test06
#testing floating point numbers
val1=`echo "scale=3; 9/3" | bc`
echo "The test value is $val1"
if 	[ $val1 != 3 ]
then
	echo "The result is larger then 3"
fi

echo -e '\r'
#test07
#testing string equality
testuser=lyj
if [ $USER = $testuser ]
then
	echo "Welcome $testuser"
fi

echo -e '\r'
#test08
#testing string equality
testuser=llyj
if [ $USER != $testuser ]
then
	echo "This is not $testuser"
else
	echo "Welcome $testuser"
fi

echo -e '\r'
#test09
#mis-using string comparisons
val1=baseball
val2=hockey

if [ $val1 \> $val2 ]
then
	echo "$val1 > $val2"
else 
	echo "$val1 < $val2"
fi

echo -e '\r'
#test10
#testing string length
val1=testing
val2=''

if [ -n "$val1" ]
then
	echo 1
	echo "The string '$val1' is not empty"
else
	echo 2
	echo "The string '$val1' is empty"
fi

if [ -z "$val2" ]
then
	echo 3
	echo "The string '$val2' is empty"
else
	echo 4
	echo "The string '$val2' is not empty"
fi

if [ -z "$val10000" ]
then
	echo 5
	echo "The string '$val10000' is empty"
else
	echo 6
	echo "The string '$val10000' is not empty"
fi

echo -e '\r'
#test11
#look before you leap
if [ -d $HOME ]
then
	echo "Your HOME directory exist"
	cd $HOME 
	ls -a
else
	echo "Your HOME directory don't exist"
fi

echo -e '\r'
#test12
#

echo -e '\r'
#test13
#

echo -e '\r'
#test14
#

echo -e '\r'
#test15
#

echo -e '\r'
#test16
#

echo -e '\r'
#test17
#

echo -e '\r'
#test18
#

echo -e '\r'
#test19
#

echo -e '\r'
#test20
#

echo -e '\r'
#test21
#

echo -e '\r'
#test22
#testing compound comparisons
if [ -d $HOME ] && [ -w $HOME/work/shell/testw ]
then
	echo "The file exits and you can write to it"
else 
	echo "can not write to it"
fi

echo -e '\r'
#test23
#using (())

#test24
#using [[]]

case $USER in
	lyj )
		echo "Welcome lyj";;
	testing )
		echo "Test account";;
	jessica )
		echo "A friend";;
esac

exit 0


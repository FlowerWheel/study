#!/bin/bash
echo -e '\r'

#test01
#This script displays the date and who's logged on
echo The time and date are:
date
echo "Let's see who's logged into the system:"
who
echo -e '\r'

#test02
#display user information from the system
echo "User info for user id:$USER"
echo UID:$UID
echo HOME:$HOME
echo -e '\r'

#test03
#testing variables
days=10
guest="Katie"
echo "$guest checked in $days days ago"
days=5
guest="Jessica"
echo "$guest checked in $days days ago"
echo -e '\r'

#test04
#assigning a variable value to another varibale
value1=10
value2=$value1
echo value1=$value1 value2=$value2
echo -e '\r'

#test05
#using the backtick character
testing=`date`
echo "The date and time are : "$testing
echo -e '\r'

#test06
#An example of using the expr command
var1=10
var2=20
var3=`expr $var2 / $var1`
echo $var3
echo -e '\r'

#test07
#
var1=100
var2=50
var3=45
var4=$[ $var1 * ($var2 - $var3) ]
echo The final result is $var4
echo -e '\r'

#test08
#
var1=100
var2=45
var3=$[$var1 / $var2]
echo The final result is $var3
echo -e '\r'

#test09
#
var1=`echo "scale=4; 3.44 / 5" | bc`
echo The answer is $var1
echo -e '\r'

#test10
#
var1=100
var2=45
var3=`echo "scale=4;$var1 / $var2" | bc`
echo The answer is $var3
echo -e '\r'

#test11
#
var1=20
var2=3.141592654
var3=`echo "scale=5;$var1 * $var2" | bc`
var4=`echo "scale=5;$var3 * $var2" | bc`
echo The answer is $var4
echo -e '\r'

#test12
#
var1=10.46
var2=43.67
var3=33.2
var4=71

var5=`bc << EOF
scale = 4
a1 = ($var1 * $var2)
b1 = ($var3 * $var4)
a1 + b1
EOF
`
echo The answer is $var5
echo -e '\r'


exit 0

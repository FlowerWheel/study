#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
TARGET='/home/liuyanjie'
NOW=$(date +%Y%m%d%H%M)
start()
{
    mongobackup --port 27017 -h 127.0.0.1 -o ${TARGET}/${NOW} -stream
}
execute()
{
        start
        if [ $? -eq 0 ]
        then
                echo "back successfully"
        else
                echo "back failure!"
        fi
}
if [ ! -d "${TARGET}/${NOW}/" ]
then
        mkdir  ${TARGET}/${NOW}
fi
execute
echo "===========back end ${NOW}==================="

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

//#define SVMSGMODE (MSG_R | MSG_W | MSG_R >> 3 | MSG_W >> 3)
#define SVMSG_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

/*
struct msgbuf{
	long mtype;
	char mtext[1];
}
*/

int main (int argc, char **argv)
{
	int				msqid;
	struct msqid_ds	info;
	struct msgbuf	buf;

//	key = ftok();
	if((msqid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT)) == -1)
	{
		perror("msgget error");
		exit(EXIT_FAILURE);
	}

	buf.mtype = 1;
	buf.mtext[0] = 1;
	
	if(msgsend(msqid, &buf, 1, 0) == -1)
	{
		perror("msgget error");
		exit(EXIT_FAILURE);
	}

	if (msgctl(msqid, IPC_STAT, &info) == -1)
	{
		perror("msgget error");
		exit(EXIT_FAILURE);
	}

	printf("read-write:%03o, cbytes = %lu, qnum = %lu, qbytes = %lu\n", 
		 info.msg_perm.mode & 0777, (ulong_t)info.msg_cbytes, 
		(ulong_t)info.msg_qnum, (ulong_t)info.msg_qbytes );
	sys("ipcs -q");

	if (msgctl(msqid, IPC_RMID, NULL) == -1)
	{
		perror("msgget error");
		exit(EXIT_FAILURE);
	}
	return 0;
}

#include	<stdio.h>
#include	<time.h>
#include	<string.h>
#include	<stdlib.h>
#include	<mysql/mysql.h>


int main (int argc,  char * argv[])
{
	MYSQL		*conn;
	MYSQL_RES	*res;
	MYSQL_ROW	row;

	char		*server		= "127.0.0.1";
	char		*user		= argv[2];
	char		*password	= argv[4];
	char		*database	= "menagerie";
	int			last_length = 0;

	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	puts("Welcome to the MySQL monitor.  Commands end with ; or \\g.\n"
			"Your MySQL connection id is 61\n"
			"Server version: 5.5.32 MySQL Community Server (GPL)\n"
			"\n"
			"Copyright (c) 2000,  2013,  Oracle and/or its affiliates. All rights reserved.\n"
			"\n"
			"Oracle is a registered trademark of Oracle Corporation and/or its\n"
			"affiliates. Other names may be trademarks of their respective\n"
			"owners.\n"
			"\n"
			"Type 'help;' or '\\h' for help. Type '\\c' to clear the current input statement.");

	char	sql[1024];

	while ( (printf("mysql> "), fflush(stdout)),  fgets( sql, 1023,  stdin ) != NULL )
	{
		if ( ! strcmp(sql,  "quit\n") )
		{
			puts("Bye");
			return EXIT_SUCCESS;
		}
		if (mysql_query(conn, sql))
		{
			printf("mysql_field_count : %d\n", mysql_field_count(conn));
			fprintf(stderr, "%s\n", mysql_error(conn));
			exit(1);
		}

		int i;

		res = mysql_use_result(conn);
		int length = mysql_num_fields(res);
		for (i = 0; i < length; ++i)
			printf("--------");
		printf("\n");
		while ((row = mysql_fetch_row(res)) != NULL)
		{
			if (row[0] != NULL)
			{
				printf("|%s", row[0]);
				last_length = strlen(row[0]);
			}
			else 
			{
				printf("|NULL");
				last_length = 0;
			}
			for (i = 1; i < length; ++i)
			{
				if ( last_length >= 7 )
				{
					if (row[i] != NULL)
					{
						printf("\t|%s", row[i]);
						last_length = strlen(row[i]);
					}
					else 
					{
						printf("\t|NULL");
						last_length = 0;
					}
				}
				else
				{
					if (row[i] != NULL)
					{
						printf("\t\t|%s", row[i]);
						last_length = strlen(row[i]);
					}
					else 
					{
						printf("\t\t|NULL");
						last_length = 0;
					}
				}
			}
			if ( length >= 7 )
				printf("\t|\n");
			else
				printf("\t\t|\n");
			for (i = 0; i < length; ++i)
				printf("--------");
			printf("\n");
		}	
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}

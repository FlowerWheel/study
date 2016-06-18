#include	<stdio.h>
#include	<time.h>
#include	<string.h>
#include	<stdlib.h>
#include	"mysql.h"


int main (void)
{
	MYSQL		*conn;
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	MYSQL_FIELD *field;

	char		*server		= "127.0.0.1";
	char		*user		= "root";
	char		*password	= "123456";
	char		*database	= "menagerie";

	conn = mysql_init(NULL);


	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}

	mysql_debug("d:t:O, /tmp/client.trace");
	if (0 != mysql_dump_debug_info(conn))
		fprintf(stderr, "%s\n", mysql_error(conn));


	printf("character set : %s\n", mysql_character_set_name(conn));

/* 
 *     if (0 == mysql_autocommit(conn, 0))
 *         printf("********************************\n");
 */

	printf("mysql  info : %s\n", mysql_info(conn));
	printf("client info : %s\n", mysql_get_client_info());
	printf("client version : %ld\n", mysql_get_client_version());
	printf("server version : %ld\n", mysql_get_server_version(conn));

	printf("host info : %s\n", mysql_get_host_info(conn));
	printf("proto info : %d\n", mysql_get_proto_info(conn));

	printf("mysql  sqlstate : %s\n", mysql_sqlstate(conn));
	printf("mysql  stat : %s\n", mysql_stat(conn));
	printf("mysql  thread id : %ld\n", mysql_thread_id(conn));
//	mysql_kill(conn, mysql_thread_id(conn));// kill thread


	char	sql[1024] = "SELECT * FROM pets";

	if (mysql_query(conn, sql))
	{
		printf("mysql_field_count : %d\n", mysql_field_count(conn));
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}
	printf("mysql warning count : %d\n", mysql_warning_count(conn));

	printf("%s:\n", sql);
	int i;

	printf("mysql_affected_rows : %lld\n", mysql_affected_rows(conn));
	res = mysql_use_result(conn);// no affect
	printf("mysql_affected_rows : %lld\n", mysql_affected_rows(conn));

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		printf("%d\n",  mysql_num_fields(res));
		printf("%d\n",  *(int*)mysql_fetch_lengths(res));

		for (i = 0; i < mysql_num_fields(res); ++i)
		{
			if (row[i] != NULL)
				printf("%s\t", row[i]);
			else 
				printf("NULL\t");
		}
		printf("\n");
	}	
	printf("-----------------------------------------------------\n");

	if (mysql_query(conn, sql))
	{
		printf("mysql_field_count : %d\n", mysql_field_count(conn));
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}

	printf("mysql  info : %s\n", mysql_info(conn));

	printf("mysql_affected_rows : %lld\n", mysql_affected_rows(conn));
	res = mysql_store_result(conn); //affect from here 
	printf("mysql_affected_rows : %lld\n", mysql_affected_rows(conn));

	mysql_data_seek(res, 1);
	if ((row = mysql_fetch_row(res)) != NULL)
	{
		int		length = mysql_num_fields(res);
		printf("length = %d\n",  length);


		printf("%d\n",  *(int*)mysql_fetch_lengths(res));

		for (i = 0; i < length; ++i)
		{
			if (row[i] != NULL)
				printf("%s\t", row[i]);
			else 
				printf("NULL\t");
		}
		printf("\n");
	}	
	
	while ((field = mysql_fetch_field(res)))
		printf("field name : %s\n", field->name);


	printf("\n");
	if (0 != mysql_change_user(conn, "root", "123456", "pets")) //change the user and the linked database, similir to connect.
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}

	mysql_free_result(res);
	mysql_close(conn);
	return 0;
}

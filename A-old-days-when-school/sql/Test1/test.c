#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//static char * server_groups[] = {
//	"embedded", "server", "this_program_server", (char *)NULL
//};

int main (void)
{
	MYSQL		mysql;
	MYSQL_RES	*res;
	MYSQL_ROW	row;

	char		sqlcmd[200];
	int			t, r;

	//mysql_library_init(0, NULL, server_groups);
	mysql_init(&mysql);

	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "root", "test", 0, NULL, 0))
		fprintf(stderr, "MYSQL CONNECT FAILED!: %s", mysql_error(&mysql));
	else
	{
		printf("MYSQL CONNECT SUCCESS!\n");
		sprintf(sqlcmd, "%s", "insert into friends (name, telephone) Values ('xx', 'xx')");
		mysql_query(&mysql, sqlcmd);
		sprintf(sqlcmd, "%s", "insert into friends (name, telephone) Values ('yy', 'yy')");
		mysql_query(&mysql, sqlcmd);
		sprintf(sqlcmd, "%s", "select * from friends");
		t = mysql_real_query(&mysql, sqlcmd, (unsigned int)strlen(sqlcmd));
		if (t)
			;//printf("mysql_real_query error : ", mysql_error(&mysql));
		else 
		{
			res = mysql_store_result(&mysql);
			while (row = mysql_fetch_row(res), row)
			{
				for (t = 0; t < mysql_num_fields(res); t++)
					printf("%s\t", row[t]);
			}
			printf("\n");
		}
		mysql_free_result(res);
	}

	mysql_close(&mysql);
//	mysql_library_end();

	return 0;
}

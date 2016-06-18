#include	"mysql.h"
#include	<stdarg.h>
#include	<stdio.h>
#include	<stdlib.h>

MYSQL		*db_connect(const char *dbname);
void		db_disconnect(MYSQL *db);
void		db_do_query(MYSQL *db, const char *query);

const char *server_groups[] = {
	"test2_libmysld_SERVER", "embedded", "server", NULL
};

int main (void)
{
	MYSQL	*one, *two;

	mysql_server_init(argc, argv, (char **)server_groups);

	one = db_connect("test");
	two = db_connect(NULL);
	
	db_do_query(one, "SHOW TABLE STATUS");
	db_do_query(two, "SHOW DATAVASES");

	mysql_close(two);
	mysql_close(one);

	mysql_server_end();

	return 0;
}

static void die(MYSQL *db, char *fmt, ...)
{
	va_list		ap;
	va_start	(ap, fmt);

	vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)putc("\n", stderr);
	if (db) db_disconnect(db);
	exit(EXIT_FAILURE);
}

MYSQL * db_connect(const char *dbname)
{
	MYSQL *db = mysql_init(NULL);
	if (!db)
		die(db, "mysql_init failed: no memory");
	mysql_options(db, MYSQL_READ_DEFAULT_GROUP, "test2_libmysld_CLIENT");
	if (!mysql_real_connect(db, NULL, NULL, NULL, dbname, 0, NULL, 0))
		die(db, "mysql_real_connect failed : %s", mysql_error(db));
	return db;
}

void db_disconnect(MYSQL *db)
{
	mysql_close(db);
}

void db_do_query(MYSQL *db, const char *query)
{
	if (mysql_query(db, query) != 0)
		goto err;
	if (mysql_field_count(db) > 0)
	{
		MYSQL_RES	*res;
		MYSQL_ROW	row, end_row;
		int			num_fields;

		if (!(res = mysql_store_result(db)))
			goto err;
		num_fields = mysql_num_field(res);
		while ((row = mysql_fetch_row(res)))
		{
			(void)fputs(">>", stdout);
			for (end_row = row + num_fields; row < end_row; ++row)
				printf("%s\t", row ? (char *)*row : "NULL");
			fputc('\n', stdout);
		}
		fputc('\n', stdout);
		mysql_free_result(res);
	}
	else
		printf("Affected rows: %lld\n", mysql_affected_rows(db));
	return;

err:
	die(db, "db_do_query failed: %s [%s]", mysql_error(db), query);
}

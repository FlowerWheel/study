/* 
 * type :
 *
 * MYSQL
 *
 * MYSQL_RES
 *
 * MYSQL_ROW
 * MYSQL_ROW_OFFSET
 *
 * MYSQL_FIELD
 * MYSQL_FIELD_OFFSET
 *
 * my_bool
 * my_ulonglong
 */

/* 
 * function :
 */

int					mysql_library_init(int argc,  char **argv,  char **groups);
void				mysql_library_end(void);

MYSQL *				mysql_init(MYSQL *mysql);
void				mysql_close(MYSQL *mysql);

int					mysql_options(MYSQL *mysql,  enum mysql_option option,  const char *arg);
int					mysql_ssl_set(MYSQL *mysql,  const char *key,  const char *cert,
						const char *ca,  const char *capath,  const char *cipher); //need client OpenSSL support
MYSQL *				mysql_real_connect(MYSQL *mysql,  const char *host,  const char *user,  const char *passwd,
						const char *db, unsigned int port,  const char *unix_socket,  unsigned long client_flag);
my_bool				mysql_change_user(MYSQL *mysql,  const char *user,  const char *password,  const char *db);
int					mysql_select_db(MYSQL *mysql,  const char *db);

char *				mysql_info(MYSQL *mysql);
char *				mysql_stat(MYSQL *mysql);// similar to mysqladmin status
const char *		mysql_sqlstate(MYSQL *mysql); //return SQLSTATE error code
void				mysql_debug(const char *debug);
int					mysql_ping(MYSQL *mysql);//test connect
int					mysql_shutdown(MYSQL *mysql,  enum enum_shutdown_level shutdown_level);
int					mysql_dump_debug_info(MYSQL *mysql);
my_bool				mysql_rollback(MYSQL *mysql); ///
unsigned int		mysql_errno(MYSQL *mysql);
const char *		mysql_error(MYSQL *mysql);
unsigned int		mysql_warning_count(MYSQL *mysql);
my_ulonglong		mysql_insert_id(MYSQL *mysql); // AUTO_INCREMENT
unsigned long		mysql_thread_id(MYSQL *mysql); //return current thread id
int					mysql_kill(MYSQL *mysql,  unsigned long pid);
my_bool				mysql_commit(MYSQL *mysql); ///
my_bool				mysql_autocommit(MYSQL *mysql,  my_bool mode); ///
unsigned long		myql_hex_string(char *to,  const char *from,  unsigned long length);
unsigned long		mysql_real_escape_string(MYSQL *mysql,  char *to,  const char *from,  unsigned long length);
const char *		mysql_character_set_name(MYSQL *mysql);
int					mysql_set_character_set(MYSQL *mysql,  char *csname);
int					mysql_set_server_option(MYSQL *mysql,  enum enum_mysql_set_option option);
void				mysql_get_character_set_info(MYSQL *mysql,  MY_CHARSET_INFO *cs);
char *				mysql_get_host_info(MYSQL *mysql);
unsigned int		mysql_get_proto_info(MYSQL *mysql);
char *				mysql_get_client_info(void);
unsigned long		mysql_get_client_version(void);
char *				mysql_get_server_info(MYSQL *mysql);
unsigned long		mysql_get_server_version(MYSQL *mysql);

int					mysql_query(MYSQL *mysql,  const char *query);
int					mysql_real_query(MYSQL *mysql,  const char *query,  unsigned long length);
int					mysql_refresh(MYSQL *mysql,  unsigned int options);

/*RESULT*/
MYSQL_RES *			mysql_list_dbs(MYSQL *mysql,  const char *wild); //similar to SHOW DATABASES [LIKE wild]
MYSQL_RES *			mysql_list_tables(MYSQL *mysql,  const char *wild); //similar to SHOW TABLES [LIKE wild]
MYSQL_RES *			mysql_list_fields(MYSQL *mysql,  const char *table,  const char *wild); //SHOW COLUMNS FROM tbl_name [LIKE wild]
MYSQL_RES *			mysql_list_processes(MYSQL *mysql); //mysqladmin processlist OR SHOW PROCESSLIST

MYSQL_RES *			mysql_use_result(MYSQL *mysql);
MYSQL_RES *			mysql_store_result(MYSQL *mysql);
my_bool				mysql_more_results(MYSQL *mysql);
int					mysql_next_result(MYSQL *mysql); //操作服务器上的结果集，使下一次store返回下一个结果集。
void				mysql_free_result(MYSQL_RES *result);

my_ulonglong		mysql_affected_rows(MYSQL *mysql);
void				mysql_data_seek(MYSQL_RES *result,  my_ulonglong offset);

/*FIELD*/
unsigned int		mysql_field_count(MYSQL *mysql);
unsigned int		mysql_num_fields(MYSQL_RES *result);
MYSQL_FIELD_OFFSET	mysql_field_seek(MYSQL_RES *result,  MYSQL_FIELD_OFFSET offset);
MYSQL_FIELD *		mysql_fetch_field(MYSQL_RES *result);
MYSQL_FIELD_OFFSET	mysql_field_tell(MYSQL_RES *result);

MYSQL_FIELD *		mysql_fetch_field_direct(MYSQL_RES *result,  unsigned int fieldnr);//return field nr type
MYSQL_FIELD *		mysql_fetch_fields(MYSQL_RES *result);//return all fields
unsigned long *		mysql_fetch_lengths(MYSQL_RES *result);//return every field length

/*ROW*/
my_ulonglong		mysql_num_rows(MYSQL_RES *result);
MYSQL_ROW_OFFSET	mysql_row_seek(MYSQL_RES *result,  MYSQL_ROW_OFFSET offset);
MYSQL_ROW			mysql_fetch_row(MYSQL_RES *result);
MYSQL_ROW_OFFSET	mysql_row_tell(MYSQL_RES *result);


/* too old no use
 * MYSQL *				mysql_connect(MYSQL *mysql,  const char *host,  const char *user,  const char *passwd);//stale 
 * int					mysql_reload(MYSQL *mysql);
 * my_bool				mysql_eof(MYSQL_RES *result);//stop use
 * unsigned long		mysql_escape_string(MYSQL *mysql,  char *to,  const char *from,  unsigned long length);
 * 
 * int					mysql_create_db(MYSQL *mysql,  const char *db);//stale
 * int					mysql_drop_db(MYSQL *mysql,  const char *db);//stale 
 */



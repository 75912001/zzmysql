#include <mysql/mysqld_error.h>
#include <mysql/errmsg.h>

#include <lib_log.h>
#include <lib_err_code.h>

#include "libmysql_iface.h"

#define SAFE_STRNCPY(dst, src) {\
	if (src){\
	::strncpy(dst, src, sizeof(dst) - 1); \
	dst[sizeof(dst) - 1] = '\0'; \
	}else{\
	dst[0] = '\0'; \
	}\
}

el::lib_mysql_if::lib_mysql_if (const std::string& host, const std::string& user,
								  const std::string& pass,
								  uint16_t port, bool log_sql, const char * a_unix_socket)
{
	this->host = host;
	this->user = user;
	this->pass = pass;
	this->port = port;
	this->is_log_sql = log_sql;
	::memset(this->unix_socket, 0, sizeof(this->unix_socket));

	mysql_init(&handle);

	if (a_unix_socket!=NULL) {
		SAFE_STRNCPY(this->unix_socket, a_unix_socket);
	}

	DEBUG_LOG("======DB conn msg [host:%s][user:%s][pass:%s][port:%u][is_log_sql:%u][unix_socket:%s]======",
		this->host.c_str(), this->user.c_str(), this->pass.c_str(), 
		this->port, this->is_log_sql, this->unix_socket);
	this->connect_server();
}

void  el::lib_mysql_if::show_error_log(const char* sql) 
{
	ERROR_LOG("sqlerr[errno:%d, error:%s, sql:%s]", this->get_errno(), this->get_error(), sql);
}

el::lib_mysql_if::~lib_mysql_if ()
{
	mysql_close(&this->handle);
}

int el::lib_mysql_if::connect_server ()
{
	char* us = NULL;
	if ('\0' != this->unix_socket[0]){
		us = this->unix_socket;
	}

	my_bool reconnect = true;
	mysql_options(&this->handle, MYSQL_OPT_RECONNECT, (const char *)&reconnect);

	//CLIENT_FOUND_ROWS	//Return the number of found (matched) rows, not the number of changed rows.
	unsigned long flag = CLIENT_FOUND_ROWS;
	if (NULL == mysql_real_connect(&this->handle, this->host.c_str(), 
		this->user.c_str(), this->pass.c_str(), NULL, this->port, us, flag)){
		ALERT_LOG("db connect is err [code:%d, %s]\n", this->get_errno(), this->get_error());
		return el::ERR_DB::SYS;
	}
	DEBUG_LOG("db connect is ok [code:%d]\n", this->get_errno());

	DEBUG_LOG("New client character set: %s", mysql_character_set_name(&this->handle));
	int t_ret = mysql_set_character_set(&this->handle, "utf8");
	if (0 == t_ret){
		DEBUG_LOG("New client character set: %s", mysql_character_set_name(&this->handle));
	} else {
		DEBUG_LOG("New client character set: %s, %d",
			mysql_character_set_name(&this->handle), t_ret);
	}
	return this->close_db_autocommit();
}

int el::lib_mysql_if::exec_query_sql (const char* sql, MYSQL_RES** result)
{
	if (0 == this->execsql(sql)){
		if(NULL == (*result = mysql_store_result(&this->handle))){
			this->show_error_log(sql);
		} else {
			return 0;
		}
	}
	return el::ERR_DB::SYS;
}

int el::lib_mysql_if::exec_update_sql(const char* sql,int* affected_rows)
{
	if (0 == this->execsql(sql)){
		*affected_rows = (int)mysql_affected_rows(&(this->handle));
//        DEBUG_LOG("affect rows %d", *affected_rows);
		return 0;
	}
	return this->get_errno();
}
int el::lib_mysql_if::exec_update_sql(const char* sql, int len,int* affected_rows)
{
	if (0 == this->execsql(sql, len)){
		*affected_rows = (int)mysql_affected_rows(&(this->handle));
        DEBUG_LOG("affect rows %d", *affected_rows);
		return 0;
	}
	return this->get_errno();
}

int el::lib_mysql_if::execsql(const char* sql, int len)
{
	if (0 != this->is_log_sql){
		DEBUG_LOG("sql:[%s]", sql);
	}
	if(len == 0){
		len = strlen(sql) + 1;
	}

	int ret = mysql_real_query(&this->handle, sql, len);
	if (0 == ret){//SUCC
		return ret;
	} else if (CR_SERVER_GONE_ERROR == this->get_errno()){//server go away, must reconnect
		if (0 == this->connect_server()){
			ret = mysql_query(&this->handle, sql);
			if (0 != ret){
				ret = this->get_errno(); 
			}
		}else{
			ret = this->get_errno(); 
		}
	}else{
		this->show_error_log(sql);
		ret = this->get_errno();
	}	
	return ret;
}

int el::lib_mysql_if::select_db(char* db_name)
{
	int ret = mysql_select_db(&this->handle, db_name);
	if (0 != ret) {
		this->show_error_log(db_name);
	}
	return this->get_errno();
}

int el::lib_mysql_if::close_db_autocommit()
{
	if (0 != mysql_autocommit(&this->handle, 0)){
		ALERT_LOG("db mysql_autocommit close is err [code:%d, %s]\n", this->get_errno(), this->get_error());
		return el::ERR_DB::SYS;
	}
	return 0;
}

int el::lib_mysql_if::db_commit()
{
	if (0 != mysql_commit(&this->handle)){
		ALERT_LOG("db mysql_commit is err [code:%d, %s]\n", this->get_errno(), this->get_error());
		return el::ERR_DB::SYS;
	}
	return 0;
}

int el::lib_mysql_if::db_rollback()
{
	TRACE_LOG("");
	mysql_rollback(&this->handle);
	return 0;
}


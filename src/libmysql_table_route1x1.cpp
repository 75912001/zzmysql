#include <mysql/mysqld_error.h>

#include <lib_log.h>
#include <lib_err_code.h>

#include "libmysql_table_route1x1.h"

el::lib_mysql_table_route1x1::lib_mysql_table_route1x1(el::lib_mysql_if* db,
													   const char* dbname_pre, const char* tablename_pre) 
{ 
	this->db = db;
	::strcpy(this->db_name, dbname_pre);
	::strcpy(this->table_name, tablename_pre);
	::strcpy(this->db_name_pre, dbname_pre);
	::strcpy(this->table_name_pre, tablename_pre);
	this->ret = 0;
}

char* el::lib_mysql_table_route1x1::get_table_name()
{
//	this->db->select_db(this->db_name_pre);

	::sprintf(this->db_table_name, "%s.%s", this->db_name, this->table_name);
	return this->db_table_name;
}

int el::lib_mysql_table_route1x1::exec_delete_sql(char* sql_str, int nofind_err)
{
	return this->exec_update_sql(sql_str, nofind_err);
}

int el::lib_mysql_table_route1x1::exec_update_sql(char* sql_str, int nofind_err )
{
	int acount; 
	if (0 == this->db->exec_update_sql(sql_str, &acount)){
		if (1 != acount){
			return nofind_err;	
		}
	}else {
		return el::ERR_DB::SYS;
	}
	return 0;
}	

int  el::lib_mysql_table_route1x1::record_is_existed(char* sql_str, bool& p_existed)
{
	p_existed = false;
	STD_QUERY_ONE_BEGIN(sql_str, 0);
		p_existed=true;
	STD_QUERY_ONE_END();
}

int el::lib_mysql_table_route1x1::exec_insert_sql(char* sql_str, int existed_err )
{
 	int dbret;
	int acount; 
	if (0 != (dbret = this->db->exec_update_sql(sql_str, &acount))){
		if (ER_DUP_ENTRY == dbret){
			return  existed_err;
		} else {
			return el::ERR_DB::SYS;
		}
	}
	return 0;
}

int el::lib_mysql_table_route1x1::exec_insert_sql_get_auto_increment_id(char * sql_str, int existed_err,
												  uint32_t& increment_id )
{
	int dbret;
	int acount; 

	if (0 == (dbret = this->db->exec_update_sql(sql_str, &acount))){
		increment_id = (uint32_t)mysql_insert_id(&(this->db->handle));
	}else {
		if (ER_DUP_ENTRY == dbret){
			return  existed_err;
		} else {
			return el::ERR_DB::SYS;
		}
	}
	return 0;
}

int el::lib_mysql_table_route1x1::exec_update_sqls(char * sql_str)
{
	int acount;
	if (0 == this->db->exec_update_sql(sql_str, &acount)){
		return 0;
	}
	return el::ERR_DB::SYS;
}

// int el::lib_mysql_table_route1x1::set_uint32_value_bit(uint32_t userid, 
// 									const char * field_type, uint32_t bitid, uint32_t  value)
// {
// 	if (bitid == 0 || bitid > 32 || value > 1){
// 		return el::ERR_DB_ENUM_OUT_OF_RANGE_ERR;
// 	}
// 	if (1 == value){
// 		value = (1<<(bitid-1));
// 		sprintf( this->sqlstr, "update %s set %s =%s |%u    where %s=%u " ,
// 			this->get_table_name(userid),field_type,field_type ,  value , this->id_name ,userid );
// 
// 	}else{
// 		value=0xFFFFFFFF-(1<<(bitid-1));
// 		sprintf( this->sqlstr, "update %s set %s =%s &%u    where %s=%u " ,
// 			this->get_table_name(userid),field_type,field_type ,  value , this->id_name ,userid );
// 	}
// 	return this->exec_update_sql(this->sqlstr,KEY_NOFIND_ERR );
// }

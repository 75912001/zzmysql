/********************************************************************
	platform:	
	author:		kevin
	copyright:	All rights reserved.
	purpose:	
	brief:		表1x1
*********************************************************************/

#pragma once

#include <lib_include.h>

#include "libmysql_macro.h"
#include "libmysql_iface.h"

namespace el{
	class lib_mysql_table_route1x1
	{
	public:
		el::lib_mysql_if* db;
		uint32_t ret;
		char sqlstr[SQL_STR_MAX_LEN];
		char db_name[DB_NAME_MAX_LEN];
		char table_name[TABLE_NAME_MAX_LEN];
		//: db.table 
		char db_table_name[DB_TABLE_NAME_MAX_LEN];

		char table_name_pre[TABLE_NAME_MAX_LEN];
		char db_name_pre[DB_NAME_MAX_LEN];
		//char dbser_return_buf[PROTO_MAX_SIZE];
	public:
		virtual char*  get_table_name();	
		//查询一条记录是否存在
		int record_is_existed(char* sql_str,  bool& p_existed);
		//更新数据
		int exec_update_sql(char* sql_str, int nofind_err);
		//插入数据(一行)
		int exec_insert_sql(char* sql_str, int existed_err);
		int exec_insert_sql_get_auto_increment_id(char * sql_str, int existed_err, uint32_t& increment_id );

		//删除数据
		int exec_delete_sql(char* sql_str, int nofind_err);
		//影响行数为多行的接口(insert ,update ,delete,都可以使用)
		int exec_update_sqls(char* sql_str);

		lib_mysql_table_route1x1(el::lib_mysql_if* db, const char* dbname_pre, const char* tablename_pre); 
		virtual ~lib_mysql_table_route1x1(void){}
#if 0
		int select_data( char *&_p_result,	uint32_t &_pkg_len, MYSQL_RES* &res , uint32_t * p_count)
		{

			this->db->set_id(this->id);

			if (DB_SUCC != ( this->db->exec_query_sql(sqlstr,&res))){
				return DB_ERR;
			}

			*p_count=mysql_num_rows(res);
			return SUCC;
		}
		int exec_insert_sql_get_auto_increment_id(char * sql_str, int existed_err,
			uint32_t *p_increment_id )
		{
			int dbret;
			int acount; 

			this->db->set_id(this->id);
			if ((dbret=this->db->exec_update_sql(sql_str,&acount ))==DB_SUCC)
			{
				*p_increment_id=mysql_insert_id(&(this->db->handle));
				return DB_SUCC;
			}else {
				if (dbret==ER_DUP_ENTRY)
					return  existed_err;
				else return DB_ERR;
			}

		}
#endif
	};
}

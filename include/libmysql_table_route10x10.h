/********************************************************************
	platform:	
	author:		kevin
	copyright:	All rights reserved.
	purpose:	
	brief:		表路由10x10
*********************************************************************/

#pragma once
#include "libmysql_table_route1x1.h"

namespace el{
	class lib_mysql_table_route10x10 : public el::lib_mysql_table_route1x1
	{
	public:
		virtual char* get_table_name(uint32_t id);
		virtual char* get_table_name(uint64_t id);
	public:
		lib_mysql_table_route10x10(el::lib_mysql_if* db, const char* db_name_pre, const char* table_name_pre)
			: el::lib_mysql_table_route1x1(db, db_name_pre, table_name_pre){}
		virtual ~lib_mysql_table_route10x10(void){}; 
	};
}
 
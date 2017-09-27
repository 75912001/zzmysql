/********************************************************************
	platform:	
	author:		kevin
	copyright:	All rights reserved.
	purpose:	使用时,需要创建表权限..随时创建当前时间对应的数据表
	brief:		表路由1x1
*********************************************************************/

#include "libmysql_table_route1x1.h"

namespace el{
	class lib_mysql_table_route_date1x1 : public el::lib_mysql_table_route1x1 
	{
	protected:
		virtual char* get_table_name(time_t logtime);
	public:
		lib_mysql_table_route_date1x1(el::lib_mysql_if* db, const char* db_name_pre, const char* table_name_pre)
			: el::lib_mysql_table_route1x1(db, db_name_pre, table_name_pre){}
		virtual ~lib_mysql_table_route_date1x1(void){}; 
	};
}

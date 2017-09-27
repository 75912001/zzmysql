/********************************************************************
	platform:	
	author:		kevin
	copyright:	All rights reserved.
	purpose:	
	brief:		表路由(默认100x100)
*********************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "libmysql_table_route1x1.h"

namespace el{
	class lib_mysql_table_route100x100 : public el::lib_mysql_table_route1x1 
	{
	protected:

		/**
		 * @brief	获取DB.TABLE形式的表名
		 */
		virtual char* get_table_name(uint32_t id);
	public:
		/**
		 * @brief	表名的前面部分：如： t_user_pet_00 --  t_user_pet_99, 写入的是t_user_pet
		 */
		lib_mysql_table_route100x100(el::lib_mysql_if* db, const char* db_name_pre, const char* table_name_pre)
					 : el::lib_mysql_table_route1x1(db, db_name_pre, table_name_pre){}
		virtual ~lib_mysql_table_route100x100(void){} 
	};
}

#include "libmysql_table_route_date1x1.h"

#include <lib_time.h>
char* el::lib_mysql_table_route_date1x1::get_table_name(time_t logtime)
{
//	this->db->select_db(this->db_name);

	::sprintf (this->db_table_name, "%s.%s_%8.8d",
		this->db_name, this->table_name, el::lib_time_t::get_date_yyyymmdd(logtime));
	return this->db_table_name;
}

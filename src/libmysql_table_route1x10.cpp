#include "libmysql_table_route1x10.h"

char * el::lib_mysql_table_route1x10::get_table_name(uint32_t id)
{
//	this->db->select_db(this->db_name);

	sprintf (this->db_table_name, "%s.%s_%01d",
	this->db_name, this->table_name_pre, id%10);
	return this->db_table_name;
}

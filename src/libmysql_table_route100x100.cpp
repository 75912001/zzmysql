#include "libmysql_table_route100x100.h"

char* el::lib_mysql_table_route100x100::get_table_name(uint32_t id)
{
	::sprintf(this->db_name,"%s_%02d", this->db_name_pre, id%100);
//	this->db->select_db(this->db_name);

	::sprintf(this->db_table_name,"%s.%s_%02d",
	this->db_name, this->table_name_pre,(id/100)%100);
	return this->db_table_name;
}

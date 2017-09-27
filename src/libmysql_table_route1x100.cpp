#include "libmysql_table_route1x100.h"

char * el::lib_mysql_table_route1x100::get_table_name(uint32_t id)
{
//	this->db->select_db(this->db_name);

	sprintf (this->db_table_name,"%s.%s_%02d",
	this->db_name,this->table_name_pre,id%100);
	return this->db_table_name;
}

#include "libmysql_table_route10x10.h"

char* el::lib_mysql_table_route10x10::get_table_name(uint32_t id)
{
	::sprintf (this->db_name,"%s_%01d", this->db_name_pre,id%10 );
//	this->db->select_db(this->db_name);

	::sprintf (this->db_table_name,"%s.%s_%01d",
	this->db_name, this->table_name_pre,(id/10)%10);
	return this->db_table_name;
}

char* el::lib_mysql_table_route10x10::get_table_name( uint64_t id )
{
	::sprintf (this->db_name,"%s_%01" PRIu64, this->db_name_pre,id%10 );
	//	this->db->select_db(this->db_name);

	::sprintf (this->db_table_name,"%s.%s_%01" PRIu64,
		this->db_name, this->table_name_pre,(id/10)%10);
	return this->db_table_name;
}

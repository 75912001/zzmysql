#include "CtableMonth.h"


CtableMonth::CtableMonth(el::lib_mysql_if * db,const char * db_name_pre,  
	const	char * table_name_pre,const char* id_name ) : el::lib_mysql_table_route100x100(
	db,db_name_pre,table_name_pre)
{ 

}

char*  CtableMonth::get_table_name()
{
	return get_table_name( el::lib_time_t::get_date_yyyymm(time(NULL)) );
}

char * CtableMonth::get_table_name(uint32_t id)
{
	if (id>100000000)//�ǽ��׺�
	{
		uint32_t months=id/100000000-1;
		id=(2008+months/12)*100+months%12+1;
	}
	this->db->select_db(this->db_name);

	sprintf (this->db_table_name,"%s.%s_%6.6d",
	this->db_name_pre, this->table_name_pre,id);
	return this->db_table_name;
}

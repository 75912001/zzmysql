#ifndef  CTABLEMONTH_INCL
#define  CTABLEMONTH_INCL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CtableRoute.h"

class CtableMonth : public el::lib_mysql_table_route100x100 {
	protected:
	public:
		virtual char*  get_table_name();
		//֧��transid:3100000000 ,��ֱ��ָ���·�:200805
		virtual char*  get_table_name(uint32_t id);
		CtableMonth(el::lib_mysql_if * db,const char * db_name_pre,  
		const char * table_name_pre,const  char* id_name ) ;
		virtual ~CtableMonth(void){} 
};

#endif   /* ----- #ifndef CTABLEMONTH_INCL  ----- */


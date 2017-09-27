#ifndef  CtableDate_100_INCL
#define  CtableDate_100_INCL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proto_header.h"
#include "CtableRoute.h"


class CtableDate_100 : public el::lib_mysql_table_route100x100 {
	private:
	public:
		char*  get_table_name(uint32_t id, time_t logtime );
	protected:
		CtableDate_100(el::lib_mysql_if * db,const char * db_name_pre,  
			const char * table_name_pre,const  char* id_name ) ;

		virtual ~CtableDate_100(void){} 
};

#endif   /* ----- #ifndef CtableDate_100_INCL  ----- */


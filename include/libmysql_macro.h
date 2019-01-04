
#pragma once

#include <mysql/mysql.h>

#include <lib_log.h>
#include <lib_util.h>

#define  GEN_SQLSTR(sqlstr, ...)  ::snprintf(sqlstr, sizeof(sqlstr), __VA_ARGS__)
const uint32_t SQL_STR_MAX_LEN = 16384;//sql str 最大长度	
const uint32_t DB_NAME_MAX_LEN = 50;
const uint32_t TABLE_NAME_MAX_LEN = 50;
const uint32_t DB_TABLE_NAME_MAX_LEN = DB_NAME_MAX_LEN + TABLE_NAME_MAX_LEN;

#define MYSQL_STR_LEN(n) ((n) * 2 + 1)

#define SET_MYSQL_STRING(dst, src, n) \
	mysql_real_escape_string(&(this->db->handle), dst, src, n)

#ifdef WIN32
#define GEN_MYSQL_STRING(new_name__, val_name__, val_len__) \
	char new_name__[102400] = {0};\
	SET_MYSQL_STRING(new_name__, val_name__, val_len__);
#else
#define GEN_MYSQL_STRING(new_name__, val_name__, val_len__) \
	char new_name__[MYSQL_STR_LEN(val_len__)];\
	memset(new_name__, 0, sizeof(new_name__));\
	SET_MYSQL_STRING(new_name__, val_name__, val_len__);
#endif

//依次得到row[i]	
// 在STD_QUERY_WHILE_BEGIN  和 STD_QUERY_ONE_BEGIN	
#define NEXT_FIELD 	 (row[++_fi])

#define GET_FIELD_UINT64(out)\
	(out) = (decltype(out))el::atoi_safe(NEXT_FIELD)

#define GET_NEXT_FIELD_INT_WITH_TYPE(out, __type__)\
	(out) = (__type__)el::atoi_safe(NEXT_FIELD)

#define GET_NEXT_FIELD_BIN(out, max_len)\
{\
	++_fi;\
	mysql_fetch_lengths(res);\
	uint32_t real_len = res->lengths[_fi] < max_len ? res->lengths[_fi] : max_len;\
	::memcpy(out, row[_fi], real_len);\
}

#define GET_NEXT_FIELD_BIN_REAL_LEN(out, max_len, __real_len__)\
{\
	++_fi;\
	mysql_fetch_lengths(res);\
	__real_len__ = res->lengths[_fi] < max_len ? res->lengths[_fi] : max_len;\
	::memcpy(out, row[_fi], __real_len__);\
}

#define GET_NEXT_FIELD_STRING16(out, max_len)\
{\
	++_fi;\
	mysql_fetch_lengths(res);\
	uint32_t real_len = res->lengths[_fi] < max_len ? res->lengths[_fi] : max_len;\
	out.append(row[_fi], real_len);\
}

#define STD_QUERY_ONE_BEGIN(sqlstr, no_find_err) {\
	uint32_t ret;\
	MYSQL_RES* res;\
	MYSQL_ROW row;\
	ret = this->db->exec_query_sql(sqlstr, &res);\
	if (0 == ret){\
	auto rowcount = mysql_num_rows(res);\
	if (1 != rowcount) {\
		mysql_free_result(res);\
		return no_find_err;\
	}else {\
		row = mysql_fetch_row(res);\
		int _fi;\
		_fi = -1;

#define STD_QUERY_ONE_END()\
		mysql_free_result(res);\
		return 0;\
	}\
	}else {\
	return el::ERR_DB::SYS;\
	}\
}

#define STD_QUERY_AFFECTED_ROWS(sqlstr, rowcount) { \
	uint32_t ret;\
	MYSQL_RES* res;\
	ret = this->db->exec_query_sql(sqlstr, &res);\
	if (0 == ret){\
	    rowcount = mysql_num_rows(res);\
        mysql_free_result(res);\
    }\
}


//----------------------列表模式-----------------------------	
#define STD_QUERY_WHILE_BEGIN( sqlstr, item_list )  \
{ \
	decltype(item_list)&_item_list = item_list;\
	MYSQL_RES *res;\
	MYSQL_ROW  row;\
	if (0 == (this->db->exec_query_sql(sqlstr, &res))){\
		while((row = mysql_fetch_row(res))){\
			decltype(item_list[0]) _item ;\
			int _fi;\
			_fi = -1;

#define STD_QUERY_WHILE_END()  \
			_item_list.push_back(_item);\
		}\
		mysql_free_result(res);	\
	}else {\
		return el::ERR_DB::SYS;\
	}\
	return 0;\
}

#define STD_QUERY_WHILE_END_FOR_SET()  \
			_item_list.insert(_item);\
		}\
		mysql_free_result(res);	\
	}else {\
		return el::ERR_DB::SYS;\
	}\
	return 0;\
}

#define STD_QUERY_WHILE_END_WITHOUT_RETURN()  \
			_item_list.push_back(_item);\
		}\
		mysql_free_result(res);	\
	}else {\
		return el::ERR_DB::SYS;\
	}\
}

//----------------------列表模式(type)-----------------------------	
#define STD_QUERY_WHILE_BEGIN_WITH_TYPE( sqlstr, item_list, __type__ )  \
{ \
	decltype(item_list)&_item_list = item_list;\
	MYSQL_RES *res;\
	MYSQL_ROW  row;\
	if (0 == (this->db->exec_query_sql(sqlstr, &res))){\
		while((row = mysql_fetch_row(res))){\
			__type__ _item ;\
			int _fi;\
			_fi = -1;

//----------------------用于protobuf的列表模式-----------------------------	
#define PB_STD_QUERY_WHILE_BEGIN( sqlstr, p_out, add_member)  \
{ \
	MYSQL_RES *res;\
	MYSQL_ROW  row;\
	if (0 == (this->db->exec_query_sql(sqlstr, &res))){\
		while((row = mysql_fetch_row(res))){\
            auto member = p_out->add_member();\
			int _fi;\
			_fi = -1;

#define PB_STD_QUERY_WHILE_BEGIN_NO_ADD( sqlstr)  \
{ \
	MYSQL_RES *res;\
	MYSQL_ROW  row;\
	if (0 == (this->db->exec_query_sql(sqlstr, &res))){\
	while((row = mysql_fetch_row(res))){\
	int _fi;\
	_fi = -1;

#define PB_STD_QUERY_WHILE_END()  \
		}\
		mysql_free_result(res);	\
	}else {\
		return el::ERR_DB::SYS;\
	}\
	return 0;\
}

#define PB_STD_QUERY_WHILE_END_WITHOUT_RETURN()  \
		}\
		mysql_free_result(res);	\
	}else {\
		return el::ERR_DB::SYS;\
	}\
}

/*#define PB_STD_QUERY_WHILE_END_WITHOUT_RETURN()  \*/
/*}\*/
/*mysql_free_result(res);	\*/
/*}else {\*/
/*return el::ERR_DB::SYS;\*/
/*}\*/
/*}*/

#if 0
//多条记录	
#define STD_QUERY_WHILE_BEGIN(sqlstr, count) \
{\
	MYSQL_RES* res;\
	MYSQL_ROW  row;\
	this->ret = this->db->exec_query_sql(sqlstr, &res);\
	if (0 == this->ret){\
		count = mysql_num_rows(res);\
		while((row = mysql_fetch_row(res))){\
			int _fi = -1;

#define STD_QUERY_WHILE_END() \
		}\
		mysql_free_result(res);	\
	}else {\
		this->ret = el::ERR_DB::SYS;\
	}\
}

//如果	
#ifdef DB_GET_LIST_NO_MALLOC   /* 没有malloc */	
// use dbser_return_buf for list ,set record count to count
/*
#define STD_QUERY_WHILE_BEGIN( sqlstr, pp_list, p_count )  \
{   MYSQL_RES *res;\
	MYSQL_ROW  row;\
	int list_size;\
	int i;\
	this->db->set_id(this->id);\
	if (( this->db->exec_query_sql(sqlstr,&res))==el::SUCC){\
		*p_count=mysql_num_rows(res);\
		*pp_list =(decltype(*pp_list))this->dbser_return_buf;\
		list_size = sizeof(decltype(**pp_list))*(*p_count);\
		if(list_size > PROTO_MAX_SIZE ){\
		DEBUG_LOG("THE SYS_ERR");\
		return el::ERR_DB_SYS;\
	}\
	::memset(*pp_list,0,PROTO_MAX_SIZE );\
	i=0;\
	while((row = mysql_fetch_row(res))){\
		int _fi;\
		_fi=-1;
*/
#define STD_QUERY_WHILE_END()  \
		i++;\
	}\
	mysql_free_result(res); \
		return el::SUCC;\
	}else {\
		return el::ERR_DB::SYS;\
	}\
}
#endif
//////////////////////////////////////////////////////////////////////////

#define GET_ROUTE(cmd_id) ((cmd_id&0x8000)?(70+((cmd_id&0x7E00)>>6)+((cmd_id &0x00E0)>>5)):(cmd_id>>9))

inline double atof_safe (char *str) 
{
	return 	(str!= NULL ? atof(str):0 );
}

//正常的db 连接	
#define STD_OPEN_AUTOCOMMIT()	   mysql_autocommit(&(this->db->handle), T)

//变长方式copy	
#define BIN_CPY_NEXT_FIELD( dst,max_len)  ++_fi; \
		mysql_fetch_lengths(res); \
		res->lengths[_fi]<max_len? \
		memcpy(dst,row[_fi],res->lengths[_fi] ): memcpy(dst,row[_fi],max_len)

//得到double的值	
#define DOUBLE_CPY_NEXT_FIELD(value )  (value)=atof_safe(NEXT_FIELD)

#endif

#define STD_QUERY_WHILE_BEGIN_NEW( sqlstr,item_list ) \
	{ \
		decltype(item_list)&_item_list=item_list;\
		MYSQL_RES *res;\
		MYSQL_ROW  row;\
        this->db->set_id(this->id);\
		if (( this->db->exec_query_sql(sqlstr,&res))==el::SUCC){\
			decltype(item_list[0]) item ;\
			while((row = mysql_fetch_row(res))){\
				int _fi;\
			   	_fi=-1;
	
#define STD_QUERY_WHILE_END_NEW()  \
            _item_list.push_back(item);\
            }\
            mysql_free_result(res); \
            return el::SUCC;\
        }else {\
		return el::ERR_DB::SYS;\
        }\
    }

#define STD_QUERY_ONE_END_WITHOUT_RETURN()  \
				mysql_free_result(res);		 \
			} \
		}else { \
		return el::ERR_DB::SYS;	 \
		}\
	}


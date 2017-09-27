/********************************************************************
	platform:	
	author:		kevin
	copyright:	All rights reserved.
	purpose:	
	brief:		
*********************************************************************/

#pragma once

#include <lib_net/lib_tcp_client.h>
#include <lib_log.h>
#include <lib_util.h>
#include <lib_proto/lib_cmd_map.h>
#include <lib_err_code.h>
#include <lib_proto/lib_msgbuf.h>
#include <service_if.h>

#include "libmysql_iface.h"
#include <proto_header.h>
#include <common.h>

class Cfunc_route;

class Cfunc_route_base 
{
public:
	el::lib_mysql_if* db;//db 连接
	CMD_ID cmd;/*用于保存当前命令号，只是为了方便 */

public:
    el::lib_tcp_peer_info_t* peer;  //连接信息
    int ret;                       //用于保存操作返回值，只是为了方便
    proto_head_t head;              //包头
    server_send_data_t send_buf;    //发送缓冲区
public:
	Cfunc_route_base(el::lib_mysql_if* db){
		this->db = db;
		this->cmd = 0;
        this->peer = NULL;
        this->ret = 0;
	}
	virtual ~Cfunc_route_base(){}

    void send_to_client(uint32_t send_len)
    {
		el_async::s2peer(this->peer, this->send_buf.send_data, send_len);
    }

    virtual int do_s2err(el::lib_tcp_peer_info_t* peer_fd_info, proto_head_t& head, uint32_t err)
    {
        this->head.result = err;
		this->head.length = proto_head_t::PROTO_HEAD_LEN;
        WARN_LOG("[uid:%" PRIu64 ", cmd:%#x, len:%u, seq:%u, ret:%x]", 
                head.id, head.cmd, head.length, head.seq, head.result);
		return el_async::s2peer(this->peer, this->head.get_data_pointer(), proto_head_t::PROTO_HEAD_LEN);
    }
};



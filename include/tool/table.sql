	CREATE TABLE IF NOT EXISTS t_user_99 (
	 user_id int(10) unsigned  not null ,
	 reg_time int(10) unsigned  not null,
	 nick char(16) not null,
	 primary key(user_id)
	) ENGINE=innodb CHARSET=UTF8;

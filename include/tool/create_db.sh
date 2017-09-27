#!/bin/sh

user="root"
password="m2@mole2"
host="localhost"
tmp_file="table.sql"
dbname_prefix="TEST_"

#数据库索引
db_index=0
db_end_index=100

#创建数据库
create_sql(){
cat << EOF > $tmp_file
	CREATE DATABASE IF NOT EXISTS $1
EOF
}

#删除数据库
drop_sql(){
cat << EOF > $tmp_file
	drop DATABASE $1
EOF
}

while [ $db_index -lt $db_end_index ] ; do
	dbx=`printf "%02d" $db_index`
	echo $dbname_prefix$dbx
	create_sql $dbname_prefix$dbx
	cat $tmp_file | mysql -u $user --password="$password" -h $host
	db_index=`expr $db_index + 1`
done

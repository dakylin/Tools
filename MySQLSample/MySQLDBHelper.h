#ifndef _MY_SQL_DB_HELPER_H_
#define _MY_SQL_DB_HELPER_H_

#include <mysql.h>
#include <string>

enum ConnStatus
{
	NONE,
	Init,
	Connected,
	Closed
};

class MySQLDBHelper
{
public:
	MySQLDBHelper();
	~MySQLDBHelper();
	bool Connect(std::string host, std::string user, std::string pwd, std::string db_name);
	bool ExecQuerySQL(std::string sql);
	bool ExecSQL(std::string sql);

private:
	ConnStatus m_Status;
	MYSQL *connection;
	MYSQL_RES *result;
	MYSQL_ROW row;
};

#endif

#ifndef _MY_SQL_DB_HELPER_H_
#define _MY_SQL_DB_HELPER_H_

#include <string>
#include "MySQLDBConn.h"

class MySQLDBHelper
{
public:
	MySQLDBHelper();
	~MySQLDBHelper();
	bool InitMySQLConn(const std::string &host, const std::string &user, const std::string &pwd, const std::string &db_name, std::string &errmsg);
	//bool Connect(std::string host, std::string user, std::string pwd, std::string db_name);
	bool ExecQuerySQL(const std::string &sql, unsigned long length, std::string &errmsg);
	bool ExecSQL(const std::string &sql, unsigned long length, std::string &errmsg);

private:
	MySQLDBConn *m_DBConnection;
	MYSQL_RES *result;
	MYSQL_ROW row;
	pthread_mutex_t m_Mutex;
};

#endif

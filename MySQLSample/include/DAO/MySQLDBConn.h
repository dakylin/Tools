#ifndef _MY_SQL_DB_CONN_H_
#define _MY_SQL_DB_CONN_H_

#include <string>
#include <mysql.h>

enum ConnStatus
{
	NONE,
	Init,
	Connected,
	Closed
};

/*
This is not thread safe. Client should try to keep thread safe when using it
*/
class MySQLDBConn
{
public:
	MySQLDBConn();
	~MySQLDBConn();
	MySQLDBConn(const MySQLDBConn &);
	MySQLDBConn &operator=(const MySQLDBConn &);

private:
	//static MySQLDBConn *m_SingleInstance;
	ConnStatus m_Status;
	MYSQL *m_Connection;

private:
	void Disconnect();

public:
	bool InitConn(/*out*/ std::string &errmsg);
	bool Connect(const std::string &host, const std::string &user, const std::string &pwd, const std::string &db_name, /*out*/ std::string &errmsg);

	bool ResetConn(std::string &errmsg);
	MYSQL *getConnection() const;
	bool ExecSQLReady() const;
	ConnStatus getConnectionStatus() const;
};

#endif
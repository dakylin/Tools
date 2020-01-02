#ifndef _MY_SQL_DB_CONN_H_
#define _MY_SQL_DB_CONN_H_

#include <string>

enum ConnStatus
{
	NONE,
	Init,
	Connected,
	Closed
};

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

public:
	bool InitConn();
	bool Connect(const std::string &host, const std::string &user, const std::string &pwd, const std::string &db_name);
	void Disconnect();
	bool ResetConn();
	MYSQL* getConnection() const;
	bool ExecSQLReady() const;
	//ConnStatus getConnectionStatus() const;
};

#endif
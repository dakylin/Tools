#include <mysql.h>
#include "MySQLDBConn.h"
#include <iostream>

MySQLDBConn::MySQLDBConn()
{
	m_Status = NONE;
	connection = NULL;
}

MySQLDBConn::~MySQLDBConn()
{
	m_Status = NONE;
}

MySQLDBConn::MySQLDBConn(const MySQLDBConn &)
{
	throw;
}
MySQLDBConn & MySQLDBConn::operator=(const MySQLDBConn &)
{
	throw;
}

bool MySQLDBConn::InitConn()
{
	connection = mysql_init(NULL);
	if (NULL == connection)
	{
		std::cout << "Connection init failed" << std::endl;
		return false;
	}
	m_Status = Init;
	return true;
}

bool MySQLDBConn::Connect(const std::string &host, const std::string &user, const std::string &pwd, const std::string &db_name)
{
	if (m_Status != Init)
	{
		std::cout << "Cannot connect before init" << std::endl;
		return false;
	}
	mysql_options(connection, MYSQL_READ_DEFAULT_GROUP, "socket");
	connection = mysql_real_connect(connection, host.c_str(),
									user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
	if (connection == NULL)
	{
		std::cout << "Connection connect failed" << std::endl;
		return false;
	}
	m_Status = Connected;
	return true;
}

void MySQLDBConn::Disconnect()
{
	if (NULL != connection && m_Status == Connected)
		mysql_close(connection);
	m_Status = Closed;
}

MYSQL* MySQLDBConn::getConnection() const
{
	return connection;
}

bool MySQLDBConn::ExecSQLReady() const
{
	return (m_Status == Connected);
}


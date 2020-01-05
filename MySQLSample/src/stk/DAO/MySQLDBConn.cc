#include <iostream>
#include "MySQLDBConn.h"

MySQLDBConn::MySQLDBConn()
{
	m_Status = NONE;
	m_Connection = NULL;
}

MySQLDBConn::~MySQLDBConn()
{
	m_Status = NONE;
}

MySQLDBConn::MySQLDBConn(const MySQLDBConn &)
{
	throw;
}
MySQLDBConn &MySQLDBConn::operator=(const MySQLDBConn &)
{
	throw;
}

bool MySQLDBConn::InitConn(std::string &errmsg)
{
	m_Connection = mysql_init(NULL);
	if (NULL == m_Connection)
	{
		//std::cout << "Connection init failed" << std::endl;
		errmsg = "Connection init failed";
		return false;
	}
	m_Status = Init;
	return true;
}

bool MySQLDBConn::Connect(const std::string &host, const std::string &user, const std::string &pwd, const std::string &db_name, std::string &errmsg)
{
	if (m_Status != Init)
	{
		//std::cout << "Cannot connect before init" << std::endl;
		errmsg = "Cannot connect before init";
		return false;
	}
	//mysql_options(m_Connection, MYSQL_READ_DEFAULT_GROUP, "socket");
	m_Connection = mysql_real_connect(m_Connection, host.c_str(),
									  user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
	if (m_Connection == NULL)
	{
		//std::cout << "Connection connect failed" << std::endl;
		errmsg = "Connection connect failed";
		return false;
	}
	m_Status = Connected;
	return true;
}

bool MySQLDBConn::ResetConn(std::string &errmsg)
{
	//if (m_Status == Connected) return true;
	if (m_Status == Closed)
	{
		delete m_Connection;
		m_Connection = NULL;
		return InitConn(errmsg);
	}
	else
	{
		//std::cout << "Cannot call Reset before close connection!" << std::endl;
		errmsg = "Cannot call Reset before close connection";
		return false;
	}
}

void MySQLDBConn::Disconnect()
{
	if (NULL != m_Connection && ExecSQLReady())
		mysql_close(m_Connection);
	m_Status = Closed;
}

MYSQL *MySQLDBConn::getConnection() const
{
	return m_Connection;
}

ConnStatus MySQLDBConn::getConnectionStatus() const
{
	return m_Status;
}

bool MySQLDBConn::ExecSQLReady() const
{
	return (m_Status == Connected);
}

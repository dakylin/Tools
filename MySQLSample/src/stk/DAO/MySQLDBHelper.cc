#include <mysql.h>
#include <pthread.h>
#include "MySQLDBHelper.h"
#include <iostream>

MySQLDBHelper::MySQLDBHelper()
{
	m_DBConnection = new MySQLDBConn();
	pthread_mutex_init(&m_Mutex, NULL);
}

MySQLDBHelper::~MySQLDBHelper()
{
	//m_DBConnection->Disconnect();
	pthread_mutex_destroy(&m_Mutex);
}

bool MySQLDBHelper::InitMySQLConn(const std::string &host, const std::string &user, const std::string &pwd, const std::string &db_name, std::string &errmsg)
{
	if (m_DBConnection->getConnectionStatus() == NONE)
	{
		bool ret = m_DBConnection->InitConn(errmsg);
		if (!ret)
			return ret;

		ret = m_DBConnection->Connect(host, user, pwd, db_name, errmsg);
		return ret;
	}
	else
	{
		errmsg = "Status is not NONE, cannot Init";
		return false;
	}
	
}

bool MySQLDBHelper::ExecQuerySQL(const std::string &sql, unsigned long length, std::string &errmsg)
{
	bool ret = m_DBConnection->ExecSQLReady();
	if (!ret)
	{
		//std::cout << "MySQL connection is not ready!" << std::endl;
		errmsg = "MySQL connection is not ready";
		return ret;
	}
	if (mysql_real_query(
			m_DBConnection->getConnection(),
			sql.c_str(), length))
	{
		//std::cout << "Execute SQL failed" << std::endl;
		errmsg = "Execute SQL failed";
		return false;
	}
	else
	{
		result = mysql_use_result(m_DBConnection->getConnection());
		size_t numfields = mysql_field_count(m_DBConnection->getConnection());
		while (true)
		{
			row = mysql_fetch_row(result);
			if (row <= 0)
				break;
			for (size_t i = 0; i < numfields; i++)
			{
				std::cout << row[i] << " ";
			}
			std::cout << std::endl;
		}
		mysql_free_result(result);
		return true;
	}
}

bool MySQLDBHelper::ExecSQL(const std::string &sql, unsigned long length, std::string &errmsg)
{
	bool ret = m_DBConnection->ExecSQLReady();
	if (!ret)
	{
		//std::cout << "MySQL connection is not ready!" << std::endl;
		errmsg = "MySQL connection is not ready";
		return ret;
	}
	pthread_mutex_lock(&m_Mutex);
	if (mysql_real_query(m_DBConnection->getConnection(), sql.c_str(), length))
	{
		errmsg = "Execute SQL failed";
		ret = false;
	}
	else
	{
		ret = true;
	}
	pthread_mutex_unlock(&m_Mutex);
	return ret;
}

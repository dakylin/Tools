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

bool MySQLDBHelper::InitMySQLConn(const std::string &host, const std::string &user, const std::string &pwd, const std::string &db_name)
{
	bool ret = m_DBConnection->InitConn();
	if (!ret) return ret;

	ret = m_DBConnection->Connect(host, user, pwd, db_name);
	return ret;
}


bool MySQLDBHelper::ExecQuerySQL(const std::string &sql, unsigned long length)
{
	bool ret = m_DBConnection->ExecSQLReady();
	if (!ret) 
	{
		std::cout << "MySQL connection is not ready!" << std::endl;
		return ret;
	}
	//if (m_Status != Connected)
	//	return false;

	//if (mysql_query(connection, sql.c_str()))
	if (mysql_real_query(
		m_DBConnection->getConnection(), 
		sql.c_str(), length))
	{
		std::cout << "Execute SQL failed" << std::endl;
		return false;
	}
	else
	{
		result = mysql_use_result(m_DBConnection->getConnection());	
		size_t numfields = mysql_field_count(m_DBConnection->getConnection());
		while (true)
		{
			row = mysql_fetch_row(result);
			if (row <= 0) break;
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

bool MySQLDBHelper::ExecSQL(const std::string &sql, unsigned long length)
{
	//if (m_Status != Connected)
	//	return false;

	//if (mysql_query(connection, sql.c_str()))
	if (mysql_real_query(m_DBConnection->getConnection(), sql.c_str(), length))
	{
		return false;
	}
	else
	{
		return true;
	}
}

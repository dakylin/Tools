#include "MySQLDBHelper.h"

#include <iostream>

MySQLDBHelper::MySQLDBHelper()
{
	m_Status = NONE;
	connection = mysql_init(NULL);
	if (NULL == connection)
	{
		std::cout << "Connection init failed" << std::endl;
	}
	m_Status = Init;
}

MySQLDBHelper::~MySQLDBHelper()
{
	if (NULL != connection)
		mysql_close(connection);
	m_Status = Closed;
}

bool MySQLDBHelper::Connect(std::string host, std::string user, std::string pwd, std::string db_name)
{
	if (m_Status != Init)
		return false;

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

bool MySQLDBHelper::ExecQuerySQL(std::string sql)
{
	if (m_Status != Connected)
		return false;

	if (mysql_query(connection, sql.c_str()))
	{
		std::cout << "Execute SQL failed" << std::endl;
		return false;
	}
	else
	{
		result = mysql_use_result(connection);
		size_t numfields = mysql_field_count(connection);
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

bool MySQLDBHelper::ExecSQL(std::string sql)
{
	if (m_Status != Connected)
		return false;

	if (mysql_query(connection, sql.c_str()))
	{
		return false;
	}
	else
	{
		return true;
	}
}

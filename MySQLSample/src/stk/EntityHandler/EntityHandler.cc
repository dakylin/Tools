#include "EntityHandler.h"

#include <stdio.h>

EntityHandler::EntityHandler()
{
	m_Entity = NULL;
	m_DBHelper = NULL;
}

bool EntityHandler::InitHandler(const std::string &ServerIP, const std::string &User, const std::string &Password, const std::string &DB)
{
	bool ret = false;
	m_DBHelper = new MySQLDBHelper();
	if (m_DBHelper != NULL)
	{
		std::string errmsg("");
		ret = m_DBHelper->InitMySQLConn(ServerIP, User, Password, DB, errmsg);
	}
	return ret;
}

EntityHandler::~EntityHandler()
{
	if (m_DBHelper != NULL)
	{
		delete m_DBHelper;
		m_DBHelper = NULL;
	}
}

bool EntityHandler::FetchEntity(EnumEntityType eType)
{
	if (m_DBHelper == NULL)
	{
		return false;
	}
	if (eType == e_UserEntity)
	{
		m_Entity = new UserEntity();
		m_FetchProcedure = "call FetchUsers()";
	}
	std::string errmsg("");
	//CallBack
	return m_DBHelper->ExecQuerySQL(m_FetchProcedure, m_FetchProcedure.length(), errmsg);
}

//void CallBack(const std::string &log, int value);
void EntityHandler::CallBack(const std::string &log, int value)
{
	printf("In call back log=%s, value=%d.\n", log.c_str(), value);
}

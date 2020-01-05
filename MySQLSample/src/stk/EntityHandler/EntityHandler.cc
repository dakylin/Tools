#include "EntityHandler.h"


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
	return m_DBHelper->ExecQuerySQL(m_FetchProcedure, m_FetchProcedure.length(), errmsg);
}

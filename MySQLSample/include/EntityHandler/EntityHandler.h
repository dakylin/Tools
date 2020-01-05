#ifndef _ENTITY_HANDLER_H_
#define _ENTITY_HANDLER_H_

#include <string>
#include <Entity/EntityBase.h>
#include <Entity/UserEntity.h>
#include <DAO/MySQLDBHelper.h>
#include <DAO/MySQLDBConn.h>

class EntityHandler
{
public:
	EntityHandler();
	~EntityHandler();

	bool InitHandler(const std::string &ServerIP, const std::string &User, const std::string &Password, const std::string &DB);
	bool FetchEntity(EnumEntityType eType);
private:
	EntityBase *m_Entity;
	MySQLDBHelper *m_DBHelper;
	std::string m_FetchProcedure;
};

#endif

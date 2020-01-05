#ifndef _ENTITY_BASE_H_
#define _ENTITY_BASE_H_

#include <string>

enum EnumEntityType
{
	e_UserEntity,
};

class EntityBase
{
public:
	EntityBase();
	virtual ~EntityBase() = 0;

	void setEntityID(int EntityID);
	int getEntityID() const;
	void setEntityType(EnumEntityType EntityType);
	EnumEntityType getEntityType() const;
protected:
	int m_EntityID;
	EnumEntityType m_EntityType;
	std::string m_FetchProcedure;
};
#endif

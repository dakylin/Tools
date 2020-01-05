#include "EntityBase.h"

EntityBase::EntityBase()
{
}

EntityBase::~EntityBase()
{
}

void EntityBase::setEntityID(int EntityID)
{
	m_EntityID = EntityID;
}
int EntityBase::getEntityID() const
{
	return m_EntityID;
}
void EntityBase::setEntityType(EnumEntityType EntityType)
{
	m_EntityType = EntityType;
}
EnumEntityType EntityBase::getEntityType() const
{
	return m_EntityType;
}

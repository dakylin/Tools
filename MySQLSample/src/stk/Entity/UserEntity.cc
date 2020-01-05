#include "EntityBase.h"
#include "UserEntity.h"

UserEntity::UserEntity()
{

}
UserEntity::UserEntity(int UserID, const std::string &UserName) : m_UserID(UserID), m_UserName(UserName)
{
}

UserEntity::~UserEntity()
{
}

void UserEntity::setUserID(int UserID)
{
	m_UserID = UserID;
}
int UserEntity::getUserID() const
{
	return m_UserID;
}
void UserEntity::setUserName(const std::string &UserName)
{
	m_UserName.assign(UserName);
}
const std::string &UserEntity::getUserName() const
{
	return m_UserName;
}

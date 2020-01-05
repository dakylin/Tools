#ifndef _USER_ENTITY_H_
#define _USER_ENTITY_H_

#include <string>

class UserEntity: public EntityBase
{
private:
	int m_UserID;
	std::string m_UserName;

public:
	UserEntity();
	UserEntity(int UserID, const std::string &UserName);
	~UserEntity();
	void setUserID(int UserID);
	int getUserID() const;
	void setUserName(const std::string &UserName);
	const std::string& getUserName() const;
};

#endif

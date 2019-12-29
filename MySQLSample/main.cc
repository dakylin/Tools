#include "MySQLDBHelper.h"

int main()
{
	MySQLDBHelper db;
	db.Connect("192.168.75.130", "root", "mysql", "CRM");
	db.ExecQuerySQL("call FetchUsers");
	//("select * from User");
	return 0;
}


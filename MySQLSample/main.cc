#include <mysql.h>
#include "MySQLDBHelper.h"
#include <string>


int main()
{
	MySQLDBHelper db;
				/*MySQL Server    user    password   DB/schema*/
	db.InitMySQLConn("192.168.75.130", "CRM", "mysql", "CRM");
	//db.Connect("192.168.75.130", "CRM", "mysql", "CRM");
	std::string SQL("call FetchUsers");
	db.ExecQuerySQL(SQL, SQL.length());
	//("select * from User");
	return 0;
}


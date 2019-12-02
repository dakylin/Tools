#ifndef _LINUX_INI_H_
#define _LINUX_INI_H_
#include <map>
#include <string>
using namespace std;

#define CONFIGLEN 256

enum INI_RES
{
	INI_SUCCESS,
	INI_ERROR,
	INI_OPENFILE_ERROR,
	INI_NO_SECTION,
	INI_NO_ENTRY
};

typedef map<std::string, std::string> KEYMAP;

typedef map<std::string, KEYMAP> MAINKEYMAP;

class LinuxIni
{
public:
	LinuxIni();
	virtual ~LinuxIni();

public:
	bool GetInt(const char *mAttr, const char *cAttr, int &nRes);
	bool GetStr(const char *mAttr, const char *cAttr, char *cValue, size_t nSize);
	INI_RES OpenFile(const char *pathName, const char *type);
	INI_RES CloseFile();

protected:
	INI_RES GetKey(const char *mAttr, const char *cAttr, char *value);

protected:
	FILE *m_fp;
	char m_szKey[CONFIGLEN];
	MAINKEYMAP m_Map;
};

#endif

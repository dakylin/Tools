#include "LinuxIni.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

LinuxIni::LinuxIni()
{
	//memset(m_szKey, 0, sizeof(m_szKey));
	m_fp = NULL;
}

LinuxIni::~LinuxIni()
{
	m_Map.clear();
}

INI_RES LinuxIni::OpenFile(const char *pathName, const char *type)
{
	string szLine, szMainKey, szLastMainKey, szSubKey;
	char strLine[CONFIGLEN] = {0};
	KEYMAP mLastMap;
	int nIndexPos = -1;
	int nLeftPos = -1;
	int nRightPos = -1;
	m_fp = fopen(pathName, type);

	if (m_fp == NULL)
	{
		printf("open inifile %s error!\n", pathName);
		return INI_OPENFILE_ERROR;
	}

	m_Map.clear();

	// TODO:
	// add code to process blank " " for the line like "key = value"
	while (fgets(strLine, CONFIGLEN, m_fp))
	{
		szLine.assign(strLine);
		nLeftPos = szLine.find("\n");
		if (string::npos != nLeftPos)
		{
			szLine.erase(nLeftPos, 1);
		}
		nLeftPos = szLine.find("\r");
		if (string::npos != nLeftPos)
		{
			szLine.erase(nLeftPos, 1);
		}
		nLeftPos = szLine.find("[");
		nRightPos = szLine.find("]");
		if (nLeftPos != string::npos && nRightPos != string::npos)
		{
			szLine.erase(nLeftPos, 1);
			nRightPos--;
			szLine.erase(nRightPos, 1);
			m_Map[szLastMainKey] = mLastMap;
			mLastMap.clear();
			szLastMainKey = szLine;
		}
		else
		{
			if (nIndexPos = szLine.find("="), string::npos != nIndexPos)
			{
				string szSubKey, szSubValue;
				szSubKey = szLine.substr(0, nIndexPos);
				szSubValue = szLine.substr(nIndexPos + 1, szLine.length() - nIndexPos - 1);
				mLastMap[szSubKey] = szSubValue;
			}
			else
			{
				//This is an invalid line?
			}
		}
	}
	m_Map[szLastMainKey] = mLastMap;

	return INI_SUCCESS;
}

INI_RES LinuxIni::CloseFile()
{

	if (m_fp != NULL)
	{
		fclose(m_fp);
		m_fp = NULL;
	}

	return INI_SUCCESS;
}

INI_RES LinuxIni::GetKey(const char *mAttr, const char *cAttr, char *pValue)
{
	if (m_Map.find(mAttr) == m_Map.end())
	{
		fprintf(stdout, "Cannot get Section [%s].\n", mAttr);
		return INI_NO_SECTION;
	}
	KEYMAP mKey = m_Map[mAttr];
	if (mKey.find(cAttr) == mKey.end())
	{
		fprintf(stdout, "Cannot get Entry [%s].\n", cAttr);
		return INI_NO_ENTRY;
	}
	string sTemp = mKey[cAttr];
	strcpy(pValue, sTemp.c_str());
	return INI_SUCCESS;
}

INI_RES LinuxIni::GetInt(const char *mAttr, const char *cAttr, int &nRes)
{
	nRes = 0;
	char szKey[CONFIGLEN];
	memset(szKey, 0, sizeof(szKey));
	INI_RES ret = GetKey(mAttr, cAttr, szKey);
	if (INI_SUCCESS == ret)
	{
		nRes = atoi(szKey);
		return INI_SUCCESS;
	}

	return ret;
}

INI_RES LinuxIni::GetStr(const char *mAttr, const char *cAttr, char *cValue, size_t nSize)
{
	char szKey[CONFIGLEN];
	memset(szKey, 0, sizeof(szKey));
	INI_RES ret = GetKey(mAttr, cAttr, szKey);
	if (INI_SUCCESS != ret)
	{
		//strcpy( m_szKey,"NULL" );
		memset(cValue, 0, nSize);
		return ret;
	}
	strncpy(cValue, szKey, nSize);
	return INI_SUCCESS;
}

// I didn't find a way to check map itmes till now.
const MAINKEYMAP &LinuxIni::getMap() const
{
	return m_Map;
}

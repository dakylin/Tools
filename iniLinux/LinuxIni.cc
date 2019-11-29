#include "LinuxIni.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

LinuxIni::LinuxIni( )
{
 memset( m_szKey,0,sizeof(m_szKey) );
 m_fp = NULL;
}

LinuxIni::~LinuxIni()
{
 m_Map.clear();
}

INI_RES LinuxIni::OpenFile(const char* pathName, const char* type)
{
 string szLine,szMainKey,szLastMainKey,szSubKey;
 char strLine[ CONFIGLEN ] = { 0 };
 KEYMAP mLastMap;
 int  nIndexPos = -1;
 int  nLeftPos = -1;
 int  nRightPos = -1;
    m_fp = fopen(pathName, type);
    
    if (m_fp == NULL)
    {
  printf( "open inifile %s error!\n",pathName );
        return INI_OPENFILE_ERROR;
    }
 
 m_Map.clear();
 
 while( fgets( strLine, CONFIGLEN,m_fp) )
 {  
  szLine.assign( strLine );
  nLeftPos = szLine.find("\n" );
  if( string::npos != nLeftPos )
  {
   szLine.erase( nLeftPos,1 );
  }
  nLeftPos = szLine.find("\r" );
  if( string::npos != nLeftPos )
  {
   szLine.erase( nLeftPos,1 );
  }   
  nLeftPos = szLine.find("[");
  nRightPos = szLine.find("]");
  if(  nLeftPos != string::npos && nRightPos != string::npos )
  {
   szLine.erase( nLeftPos,1 );
   nRightPos--;
   szLine.erase( nRightPos,1 );
   m_Map[ szLastMainKey ] = mLastMap;
   mLastMap.clear();
   szLastMainKey =  szLine ;
  }
  else
  {  
   if( nIndexPos = szLine.find("=" ),string::npos != nIndexPos)
   {
    string szSubKey,szSubValue;
    szSubKey = szLine.substr( 0,nIndexPos );
    szSubValue = szLine.substr( nIndexPos+1,szLine.length()-nIndexPos-1);
    mLastMap[szSubKey] = szSubValue ;
   }
   else
   {
    
   }
  }
 
 }
 m_Map[ szLastMainKey ] = mLastMap;
 
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
 

INI_RES LinuxIni::GetKey(const char* mAttr, const char* cAttr, char* pValue)
{
 
    KEYMAP mKey = m_Map[ mAttr ];
 
 string sTemp = mKey[ cAttr ];
 
 strcpy( pValue,sTemp.c_str() );
 
    return INI_SUCCESS;
}

bool LinuxIni::GetInt(const char* mAttr, const char* cAttr, int &nRes )
{
 nRes = 0;
 
 memset( m_szKey,0,sizeof(m_szKey) );
 
 if( INI_SUCCESS == GetKey( mAttr,cAttr,m_szKey ) )
 {
  nRes = atoi( m_szKey );
  return true;
 }
 return false;
}

bool LinuxIni::GetStr(const char* mAttr, const char* cAttr, char *cValue, size_t nSize )
{
 memset( m_szKey,0,sizeof(m_szKey) );
 
 if( INI_SUCCESS != GetKey( mAttr,cAttr,m_szKey ) )
 {
  //strcpy( m_szKey,"NULL" );
  memset( cValue,0,nSize );
  return false;
 }
 strncpy(cValue, m_szKey, nSize);
 //strcpy(cValue, m_szKey);
 return true;;
}

int main()
{
	std::string INIFile="/home/daniel/text.ini";
	LinuxIni  ini;
	ini.OpenFile(INIFile.c_str(), "r");
	char pVal1[3] = {0}; 
	bool ret1 = ini.GetStr("Section1","key2", pVal1, 2);
	if (ret1)
		printf("pVal1=%s.\n",pVal1);
	int  nKey = -1;
    bool ret2	= ini.GetInt("Section2","key1", nKey);
	printf("nKey=%d.\n",nKey);
	
	printf("pVal1=%s, nKey=%d.\n",pVal1, nKey);
}

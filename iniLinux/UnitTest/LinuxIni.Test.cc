#include "../LinuxIni.h"
#include "LinuxIni.Mock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>


TEST(LinuxIniTest, OpenFile1)
{
	this->RecordProperty("Description", "Return 2 if fopen return NULL");
	//RecordProperty("Description", "Return 2 if fopen return NULL");
	//CASE_DESC("Return 2 if fopen return NULL");
	Mock_C_FUN mockCFun;
	EXPECT_CALL(mockCFun, fopen("","")).WillRepeatedly(ReturnNull());
	LinuxIni ini;
	EXPECT_EQ(2, ini.OpenFile("test.ini","rw"));
}

TEST(LinuxIniTest, OpenFile2)
{
	this->RecordProperty("Description", "Map is zero when fget return 0");
	/*
	MOCK_METHOD3(fgets, int( char *pathName, int Length, FILE *pfile));*/

	Mock_C_FUN mockCFun;
	char strArray[256] = {0};
	int length = 256;
	//FILE *pFile = NULL;
	//EXPECT_CALL(mockCFun, fopen("","")).WillRepeatedly(ReturnNull());
	EXPECT_CALL(mockCFun, fgets(strArray,length, NULL)).WillRepeatedly(Return(0));
	LinuxIni ini;
	ini.OpenFile("./test.ini","rw");
	size_t m_Count = ini.getMap().size();
	EXPECT_EQ(3, m_Count);
}



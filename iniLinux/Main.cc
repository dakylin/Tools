#include <string>
#include <stdio.h>
#include "LinuxIni.h"

int main()
{
	std::string INIFile = "/home/daniel/text.ini";
	LinuxIni ini;
	ini.OpenFile(INIFile.c_str(), "r");
	char pVal1[3] = {0};
	INI_RES ret1 = ini.GetStr("Section1", "key2", pVal1, 2);
	if (ret1 == INI_SUCCESS)
		printf("pVal1=%s.\n", pVal1);
	int nKey2 = -1;
	int nKey3 = -1;
	int nKey4 = -1;
	INI_RES ret2 = ini.GetInt("Section2", "key1", nKey2);
	if (ret2 == INI_SUCCESS)
		printf("nKey=%d.\n", nKey2);
	
	INI_RES ret3 = ini.GetInt("Section6", "key1", nKey3);
	if (ret3 == INI_SUCCESS)
		printf("nKey=%d.\n", nKey3);
	
	INI_RES ret4 = ini.GetInt("Section2", "key9", nKey4);
	if (ret4 == INI_SUCCESS)
		printf("nKey=%d.\n", nKey4);

	printf("pVal1=%s, nKey2=%d, nKey3=%d, nKey4%d.\n", pVal1, nKey2, nKey3, nKey4);
}

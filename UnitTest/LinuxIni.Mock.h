#include <string>
#include <gmock/gmock.h>
#include "../LinuxIni.h"

//MOCK_METHOD2(fopen, FILE*(const char *pathName, const char *type));

using namespace testing;
class Mock_C_FUN 
{
public:
    MOCK_METHOD2(fopen, FILE*( char *pathName,  char *type));
	MOCK_METHOD3(fgets, int( char *pathName, int Length, FILE *pfile));
};


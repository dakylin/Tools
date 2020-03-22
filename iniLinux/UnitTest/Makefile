MODULE=gtestIniLinux
CROSS =
CC = $(CROSS)gcc
CXX = $(CROSS)g++ -std=c++11
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf

SRCS = $(wildcard ./*.cc)
OBJS = $(patsubst %.cc, %.o, $(SRCS))



#HEADER_PATH = -I./include/
#LIB_PATH = -L./lib/

STATIC_LIBPATH=/CI/tools/thirdparty/staticlib

LIBS = -L/CI/tools/thirdparty/lib -lgtest -lgmock -lpthread $(STATIC_LIBPATH)/gtest_main.a
#ODBCROOT=/ODBC
#INC=$(ODBCROOT)/include
#HEADER_PATH=-I$(INC) ./
#LIB_PATH =-L$(ODBCROOT)/lib
HEADER_PATH=-I./ -I/CI/tools/gtest/googletest/googletest/include -I/CI/tools/gtest/googletest/googlemock/include

TARGET = $(MODULE)

$(TARGET) : $(OBJS)
		$(CXX) LinuxIni.o $^ -o $@ $(LIB_PATH) $(LIBS) $(DEBUG)

$(OBJS):%.o : %.cc
		$(CXX) $(CFLAGS) $< -o $@ $(HEADER_PATH)
		$(CXX) $(CFLAGS) $(HEADER_PATH) -c ../LinuxIni.cc 

clean:
		$(RM) $(TARGET) *.o

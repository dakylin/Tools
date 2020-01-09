MODULE=libEntityHandler.so
CROSS = 
CC = $(CROSS)gcc
CXX = $(CROSS)g++
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c -fPIC
RM = rm -rf

SRCS = $(wildcard ./*.cc)
OBJS = $(patsubst %.cc, %.o, $(SRCS))

MYSQL_ROOT = /daniel/mysql
MYSRC_ROOT = /daniel/src/MySQLSample/stk

HEADER_PATH=-I$(MYSQL_ROOT)/include -I$(MYSRC_ROOT)

TARGETPATH = /daniel/lib

TARGET = $(TARGETPATH)/$(MODULE)

$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ $(LIB_PATH) $(LIBS) $(DEBUG) -shared -fPIC

$(OBJS):%.o : %.cc
	$(CXX) $(CFLAGS) $< -o $@ $(HEADER_PATH)
clean:
	$(RM) *.o 

MODULE=MySQL
CROSS = 
CC = $(CROSS)gcc
CXX = $(CROSS)g++
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf

SRCS = $(wildcard ./*.cc)
OBJS = $(patsubst %.cc, %.o, $(SRCS))

MYSQL_ROOT = /daniel/mysql
MYSRC_ROOT = /daniel/src

HEADER_PATH=-I$(MYSQL_ROOT)/include -I$(MYSRC_ROOT)/MySQLSample/lib


LIBS=-L$(MYSQL_ROOT)/lib -L$(MYSRC_ROOT)/MySQLSample/lib -Wl,-R,$(MYSQL_ROOT)/lib -lmysqlclient -lpthread -lm -lrt -lssl -lcrypto -ldl -lMySQL

VERSION = 1.0.0.1
TARGET = $(MODULE).$(VERSION)

$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ $(LIB_PATH) $(LIBS) $(DEBUG)

$(OBJS):%.o : %.cc
	$(CXX) $(CFLAGS) $< -o $@ $(HEADER_PATH)
clean:
	$(RM) $(TARGET) *.o 

MODULE=libEntity.so
CROSS = 
CC = $(CROSS)gcc
CXX = $(CROSS)g++
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c -fPIC
RM = rm -rf

SRCS = $(wildcard ./*.cc)
OBJS = $(patsubst %.cc, %.o, $(SRCS))

MYSQL_ROOT = /daniel/mysql

HEADER_PATH=-I$(MYSQL_ROOT)/include

TARGETPATH = /daniel/lib

TARGET = $(MODULE)

$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ $(LIB_PATH) $(LIBS) $(DEBUG) -shared -fPIC
	mv $(TARGET) $(TARGETPATH)/

$(OBJS):%.o : %.cc
	$(CXX) $(CFLAGS) $< -o $@ $(HEADER_PATH)
clean:
	$(RM) $(TARGET) *.o 

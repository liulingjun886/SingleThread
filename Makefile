CC = gcc
CXX = g++

LIB_DIR = ./lib
INC = -I./include/core -I./common
CFLAGS = -Werror -O0
LDFLAGS = -Wl,--export-dynamic 

LIBS := -L$(LIB_DIR)/core -lcore -lpthread -ldl

all:SmartEMS

SmartEMS_SRC = $(wildcard ./common/*.cpp) main.cpp
SmartEMS_OBJ = $(SmartEMS_SRC:.cpp=.o)

SmartEMS:$(SmartEMS_OBJ)
	$(CXX) $(CFLAGS) $^ -o $@ $(LIBS) $(LDFLAGS)

%.o:%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@ $(INC)
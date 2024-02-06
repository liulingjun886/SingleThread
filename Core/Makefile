ROOT_DIR = ./
INCLUDEPATH = -I./include
SRCPATH = ./src
SRC = $(wildcard ./src/*.cpp)
LIBOBJ := $(SRC:.cpp=.o)

./src/%.o : ./src/%.cpp
	g++ -c -g $< -o $@ $(INCLUDEPATH)

libcore.a : $(LIBOBJ)
	ar -rcs $@ $^

test : ./Test.cpp
	g++ -g $< -o $@ $(INCLUDEPATH) -L. -lcore -lpthread

clean:
	rm -f ./src/*.o
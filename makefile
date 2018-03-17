CXX=g++
CPPFLAGS=-std=c++11 -pthread #-ggdb -I /home/ubuntu/boost_1_66_0/ 
#LDFLAGS=-L/home/ubuntu/boost_1_66_0/stage/lib/ 
#LDLIBS=-lboost_regex -lpthread -lboost_system

SRC=server.cpp
OBJ=$(subst .cpp,.o,$(SRC))

all: compile

clean:
	rm src/*.o

#server: $(OBJ)
#$(CXX) $(LDFLAGS) -o server $(OBJ) $(LDLIBS)
compile c:
	$(CXX) *.cpp -o server $(CPPFLAGS)

main.o: server.cpp

#connection_pool.o: src/connection_pool.cpp

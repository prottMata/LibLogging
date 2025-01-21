CXX=g++
CXXFLAGS=-std=c++17 -pthread
INCLUDES=-Iinclude
LIBS=-llogging


all: liblogging.so main

liblogging.so: src/logging.cpp
	$(CXX) $(CXXFLAGS) -fpic -shared src/logging.cpp $(INCLUDES) -o liblogging.so

main: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o main $(INCLUDES) $(LIBS) -L.

test: main
	./main log.txt info
    
clean:
	rm -f main liblogging.so
	

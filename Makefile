CXX=g++
CXXFLAGS= -Wall -Werror -Wextra-semi -O1 -g -std=c++23 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tracer: main.o
	$(CXX) $(CXXFLAGS) $? -o $@


CPP      = g++
CPPFLAGS = -O3 -g -Wall -pedantic -std=c++11

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

SRC = graph.cpp union_find.cpp 
H   = edge.hpp graph.hpp mst.hpp union_find.hpp

foo: main.cpp path.cpp 
	$(CPP) $(CPPFLAGS) -o foo main.cpp path.cpp graph.cpp matrix.cpp

all: foo bar

bar: main2.cpp path.cpp
	$(CPP) $(CPPFLAGS) -o bar main2.cpp path.cpp graph.cpp matrix.cpp

# libgraph.a: graph.o matrix.o
#	ar vr libgraph.a $?
#	ranlib libgraph.a

clean: 
	rm -r -f main.o main2.o path.o foo bar

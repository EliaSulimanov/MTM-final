CC = /usr/local/bin/gcc
CXX = /usr/local/bin/g++
OBJS = gcalc.o graph.o graphHelper.o graphWarper.o
SOBJS = graph.o graphHelper.o graphWarper.o
EXEC = gcalc
DEBUG_FLAG = -g
COMP_FLAG = -std=c++11 --pedantic-errors -Wall -Werror -fPIC

$(EXEC): $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

gcalc.o: gcalc.cpp graphHelper.h graphException.h graph.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

graph.o: graph.cpp graph.h graphHelper.h graphException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

graphHelper.o: graphHelper.cpp graphHelper.h graph.h graphException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

graphWarper.o: graphWarper.cpp graphWarper.h graph.h graphException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

libgraph.a: $(SOBJS)
	ar -rs $@ $^

clean:
	rm -f $(OBJS) $(EXEC)

CXX = g++
OBJS = gcalc.o Graph.o GraphHelper.o
EXEC = gcalc
DEBUG_FLAG = -g
COMP_FLAG = -std=c++11 --pedantic-errors -Wall -Werror

$(EXEC): $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

gcalc.o: gcalc.cpp GraphHelper.h GraphException.h Graph.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Graph.o: Graph.cpp Graph.h GraphHelper.h GraphException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

GraphHelper.o: GraphHelper.cpp GraphHelper.h GraphException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)
CC = /usr/local/bin/gcc
CXX = /usr/local/bin/g++
OBJS = gcalc.o graph.o graphHelper.o
SOBJS = graph.o graphHelper.o
EXEC = gcalc
DEBUG_FLAG = -g
COMP_FLAG = -std=c++11 --pedantic-errors -Wall -Werror -fPIC
FNAM = gcalc.zip
UTILF = design.pdf Makefile test_in.txt test_out.txt
FILIST = gcalc.cpp graph.cpp graph.h graphHelper.cpp graphHelper.h graphException.h 

$(EXEC): $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

gcalc.o: gcalc.cpp graphHelper.h graphException.h graph.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

graph.o: graph.cpp graph.h graphHelper.h graphException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

graphHelper.o: graphHelper.cpp graphHelper.h graph.h graphException.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

libgraph.a: $(SOBJS)
	ar -rs $@ $^

tar:
	zip $(FNAM) $(UTILF) $(FILIST)

clean:
	rm -f $(OBJS) $(EXEC) libgraph.a

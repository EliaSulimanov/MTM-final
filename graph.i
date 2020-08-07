%module graph
%include <std_string.i>
%{
#include "graph.h"
%}

graph* create();
void destroy(graph* graph);
graph* addVertex(graph* graph, char* v);
graph* addEdge(graph* graph, char* v1, char* v2);
void disp(graph& graph);

graph* graphUnion(graph& graph_in1, graph& graph_in2, graph& graph_out);
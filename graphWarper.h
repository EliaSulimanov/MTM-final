#ifndef GRAPH_WARPER_H
#define GRAPH_WARPER_H

#include "graph.h"
#include <string>

class graphWarper
{
public:
	graph* create();
	void destroy(graph* graph);
	graph* addVertex(graph* graph, std::string v);
	graph* addEdge(graph* graph, std::string v1, std::string v2);
	void disp(graph* graph);

	graph* graphUnion(graph* graph_in1, graph* graph_in2, graph* graph_out);
	graph* graphIntersection(graph* graph_in1, graph* graph_in2, graph* graph_out);
	graph* graphDifference(graph* graph_in1, graph* graph_in2, graph* graph_out);
	graph* graphProduct(graph* graph_in1, graph* graph_in2, graph* graph_out);
	graph* graphComplement(graph* graph_in, graph* graph_out);

};
#endif // GRAPH_WARPER_H


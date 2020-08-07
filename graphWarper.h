#ifndef GRAPH_WARPER_H
#define GRAPH_WARPER_H

#include "graph.h"
#include <string>

class graphWarper
{
public:
	gcalc::graph* create();
	void destroy(gcalc::graph* graph);
	gcalc::graph* addVertex(gcalc::graph* graph, std::string v);
	gcalc::graph* addEdge(gcalc::graph* graph, std::string v1, std::string v2);
	void disp(gcalc::graph* graph);

	gcalc::graph* graphUnion(gcalc::graph* graph_in1, gcalc::graph* graph_in2, gcalc::graph* graph_out);
	gcalc::graph* graphIntersection(gcalc::graph* graph_in1, gcalc::graph* graph_in2, gcalc::graph* graph_out);
	gcalc::graph* graphDifference(gcalc::graph* graph_in1, gcalc::graph* graph_in2, gcalc::graph* graph_out);
	gcalc::graph* graphProduct(gcalc::graph* graph_in1, gcalc::graph* graph_in2, gcalc::graph* graph_out);
	gcalc::graph* graphComplement(gcalc::graph* graph_in, gcalc::graph* graph_out);

};
#endif // GRAPH_WARPER_H


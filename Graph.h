#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <vector>
#include <string>

class graph
{
private:
	std::set<std::string> vertex_set;
	std::set<std::vector<std::string> > edge_set;
public:
	graph();
	graph(const graph& rhg);
	//~graph() = default;
	graph& operator=(const graph& rhg);
	void insertVertex(std::string vertex);
	void insertEdge(std::string src, std::string dest);
	std::vector<std::pair<size_t, std::string> > flatgraph();
	static graph unite(const graph& lhg, const graph& rhg);
	static graph intersect(const graph& lhg, const graph& rhg);
	static graph diff(const graph& lhg, const graph& rhg);
	static graph cross(const graph& lhg, const graph& rhg);
	static graph complement(const graph& grap);
	static void printGraph(const graph& grap);
};
graph* create();
/*void destroy(graph& graph);
graph addVertex(graph& graph, std::string v);
graph addEdge(graph& graph, std::string v1, std::string v2);
void disp(graph& graph);

graph graphUnion(graph& graph_in1, graph& graph_in2, graph& graph_out);
graph graphIntersection(graph& graph_in1, graph& graph_in2, graph& graph_out);
graph graphDifference(graph& graph_in1, graph& graph_in2, graph& graph_out);
graph graphProduct(graph& graph_in1, graph& graph_in2, graph& graph_out);
graph graphComplement(graph& graph_in, graph& graph_out);*/
#endif


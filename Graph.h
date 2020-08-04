#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <vector>
#include <string>

namespace gcalc
{
	class Graph
	{
	private:
		std::set<std::string> vertex_set;
		std::set<std::vector<std::string> > edge_set;
	public:
		Graph();
		Graph(const Graph& rhg);
		~Graph() = default;
		Graph& operator=(const Graph& rhg);
		void insertVertex(std::string vertex);
		void insertEdge(std::string src, std::string dest);
		friend Graph unite(const Graph& lhg, const Graph& rhg);
		friend Graph intersect(const Graph& lhg, const Graph& rhg);
		friend Graph diff(const Graph& lhg, const Graph& rhg);
		friend Graph cross(const Graph& lhg, const Graph& rhg);
		friend Graph complement(const Graph& grap);
		friend void print(const Graph& grap);
	};
	Graph unite(const Graph& lhg, const Graph& rhg);
	Graph intersect(const Graph& lhg, const Graph& rhg);
	Graph diff(const Graph& lhg, const Graph& rhg);
	Graph cross(const Graph& lhg, const Graph& rhg);
	Graph complement(const Graph& grap);
	void print(const Graph& grap);
}
#endif


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
		std::string name;
		std::set<std::string> vertex_set;
		std::set<std::vector<std::string> > edge_set;
	public:
		Graph() = delete;
		Graph(std::string name);
		Graph(const Graph& rhg) = delete;
		~Graph() = default;
		Graph& operator=(const Graph& rhg); // TODO: this.
	};
}
#endif


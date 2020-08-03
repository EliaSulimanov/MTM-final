#include "Graph.h"
#include "GraphHelper.h"
#include "GraphException.h"

gcalc::Graph::Graph()
{
	vertex_set.clear();
	edge_set.clear();
}

gcalc::Graph::Graph(const Graph& rhg)
{
	this->vertex_set = rhg.vertex_set;
	this->edge_set = rhg.edge_set;
}

gcalc::Graph& gcalc::Graph::operator=(const Graph& rhg)
{
	this->vertex_set = rhg.vertex_set;
	this->edge_set = rhg.edge_set;
	return *this;
}

void gcalc::Graph::insertVertex(std::string vertex)
{
	if (gcalc::GraphHelper::vertexNameCheck(vertex))
	{
		if (this->vertex_set.find(vertex) != this->vertex_set.end())
		{
			throw gcalc::GraphException("Invalid graph syntax.");
		}
		else 
		{
			this->vertex_set.insert(vertex);
		}
	}
}

void gcalc::Graph::insertEdge(std::string src, std::string dest)
{
	if (gcalc::GraphHelper::vertexNameCheck(src) && gcalc::GraphHelper::vertexNameCheck(dest))
	{
		if (src.compare(dest) == 0) // self loop
		{
			throw gcalc::GraphException("Invalid graph syntax.");
		}
		else if (this->vertex_set.find(src) == this->vertex_set.end() || this->vertex_set.find(dest) == this->vertex_set.end()) // vertex not exist
		{
			throw gcalc::GraphException("Invalid graph syntax.");
		}
		else
		{
			std::vector<std::string> temp {src, dest};
			if (this->edge_set.find(temp) != this->edge_set.end()) // edge exist
			{
				throw gcalc::GraphException("Invalid graph syntax.");
			}
			else
			{
				this->edge_set.insert(temp);
			}
		}
	}
}

gcalc::Graph gcalc::unite(const Graph& lhg, const Graph& rhg)
{
	gcalc::Graph result(lhg);
	result.vertex_set.insert(rhg.vertex_set.begin(), rhg.vertex_set.end()); 
	result.edge_set.insert(rhg.edge_set.begin(), rhg.edge_set.end()); // TODO: check if this works as expected

	return result;
}

gcalc::Graph gcalc::intersect(const Graph& lhg, const Graph& rhg)
{
	gcalc::Graph result;
	for (auto vertex : lhg.vertex_set)
	{
		if (rhg.vertex_set.find(vertex) != rhg.vertex_set.end()) // exists in both
		{
			result.insertVertex(vertex);
		}
	}

	for (auto edge : lhg.edge_set) // TODO: check if this works as expected
	{
		if (rhg.edge_set.find(edge) != rhg.edge_set.end()) // exists in both
		{
			result.insertEdge(edge[0], edge[1]);
		}
	}

	return result;
}

gcalc::Graph gcalc::diff(const Graph& lhg, const Graph& rhg)
{
	gcalc::Graph result;
	for (auto vertex : lhg.vertex_set)
	{
		if (rhg.vertex_set.find(vertex) == rhg.vertex_set.end()) // exists on left graph but not on right
		{
			result.insertVertex(vertex);
		}
	}

	for (auto edge : lhg.edge_set) // TODO: check if this works as expected
	{
		if (result.vertex_set.find(edge[0]) != result.vertex_set.end() &&
			result.vertex_set.find(edge[1]) != result.vertex_set.end()) // edge vertexes are in the result graph
		{
			result.insertEdge(edge[0], edge[1]);
		}
	}

	return result;
}

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

gcalc::Graph gcalc::unite(const Graph& lhg, const Graph& rhg)
{
	gcalc::Graph result(lhg);
	result.vertex_set.insert(rhg.vertex_set.begin(), rhg.vertex_set.end()); 
	result.edge_set.insert(rhg.edge_set.begin(), rhg.edge_set.end()); // TODO: check if this works as expected
	return result;
}

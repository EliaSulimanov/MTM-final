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
		if (this->vertex_set.find(vertex) != this->vertex_set.end()) // vertex already exists
		{
			throw gcalc::GraphException("Invalid graph syntax - vertex already exists");
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
			throw gcalc::GraphException("Invalid graph syntax - self loop edge not allowed");
		}
		else if (this->vertex_set.find(src) == this->vertex_set.end() || this->vertex_set.find(dest) == this->vertex_set.end()) // vertex not exist
		{
			throw gcalc::GraphException("Invalid graph syntax - edge vertex not exist");
		}
		else
		{
			std::vector<std::string> temp {src, dest};
			if (this->edge_set.find(temp) != this->edge_set.end()) // edge exist
			{
				throw gcalc::GraphException("Invalid graph syntax - edge already exist");
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

gcalc::Graph gcalc::cross(const Graph& lhg, const Graph& rhg)
{
	gcalc::Graph result; // TODO: test this. Not sure about the product

	for (auto left_v : lhg.vertex_set)
	{
		for (auto right_v : rhg.vertex_set)
		{
			result.insertVertex("[" + left_v + ";" + right_v + "]");
		}
	}

	for (auto left_e : lhg.edge_set)
	{
		for (auto right_e : rhg.edge_set)
		{
			result.insertEdge("[" + left_e[0] + ";" + right_e[0] + "]", "[" + left_e[1] + ";" + right_e[1] + "]"); // TODO: check if vector is the right size
		}
	}

	return result;
}

gcalc::Graph gcalc::complement(const Graph& grap)
{
	gcalc::Graph result; // TODO: check on complex graphs
	result.vertex_set = grap.vertex_set; // TODO: check if it alloc new memory for this or use the same
	for (auto left_v : grap.vertex_set) 
	{
		for (auto right_v : grap.vertex_set)
		{
			if (left_v.compare(right_v) == 0) // No self loops allowed
			{
				continue;
			}
			else
			{
				std::vector<std::string> temp = { left_v , right_v };
				
				if (grap.edge_set.find(temp) == grap.edge_set.end()) // Edge is not in the original graph
				{
					result.insertEdge(left_v, right_v);
				}
				else
				{
					continue;
				}
			}
		}
	}
	return result;
}

void gcalc::print(const Graph& grap)
{
	for (auto vertex : grap.vertex_set)
	{
		std::cout << vertex << std::endl;
	}

	std::cout << "$" << std::endl;
	
	for (auto edge : grap.edge_set)
	{
		std::cout << edge[0] + " " + edge[1] << std::endl;
	}
}


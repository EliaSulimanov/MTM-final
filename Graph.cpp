#include "graph.h"
#include "graphHelper.h"
#include "graphException.h"

gcalc::graph::graph()
{
	vertex_set.clear();
	edge_set.clear();
}

gcalc::graph::graph(const graph& rhg)
{
	this->vertex_set = rhg.vertex_set;
	this->edge_set = rhg.edge_set;
}

gcalc::graph& gcalc::graph::operator=(const graph& rhg)
{
	this->vertex_set = rhg.vertex_set;
	this->edge_set = rhg.edge_set;
	return *this;
}

void gcalc::graph::insertVertex(std::string vertex)
{
	if (gcalc::graphHelper::vertexNameCheck(vertex))
	{
		if (this->vertex_set.find(vertex) != this->vertex_set.end()) // vertex already exists
		{
			throw gcalc::graphException("Invalid graph syntax - vertex already exists");
		}
		else 
		{
			this->vertex_set.insert(vertex);
		}
	}
}

void gcalc::graph::insertEdge(std::string src, std::string dest)
{
	if (gcalc::graphHelper::vertexNameCheck(src) && gcalc::graphHelper::vertexNameCheck(dest))
	{
		if (src.compare(dest) == 0) // self loop
		{
			throw gcalc::graphException("Invalid graph syntax - self loop edge not allowed");
		}
		else if (this->vertex_set.find(src) == this->vertex_set.end() || this->vertex_set.find(dest) == this->vertex_set.end()) // vertex not exist
		{
			throw gcalc::graphException("Invalid graph syntax - edge vertex not exist");
		}
		else
		{
			std::vector<std::string> temp {src, dest};
			if (this->edge_set.find(temp) != this->edge_set.end()) // edge exist
			{
				throw gcalc::graphException("Invalid graph syntax - edge already exist");
			}
			else
			{
				this->edge_set.insert(temp);
			}
		}
	}
}

std::vector<std::pair<size_t, std::string> > gcalc::graph::flatgraph()
{
	std::vector<std::pair<size_t, std::string> > flat_graph;

	flat_graph.push_back(std::pair<size_t, std::string>(vertex_set.size(), ""));
	flat_graph.push_back(std::pair<size_t, std::string>(edge_set.size(), ""));

	for (auto vertex : vertex_set)
	{
		flat_graph.push_back(std::pair<size_t, std::string>(vertex.size(), vertex));
	}

	for (auto edge : edge_set)
	{
		flat_graph.push_back(std::pair<size_t, std::string>(edge[0].size(), edge[0]));
		flat_graph.push_back(std::pair<size_t, std::string>(edge[1].size(), edge[1]));
	}

	return flat_graph;
}

gcalc::graph gcalc::unite(const graph& lhg, const graph& rhg)
{
	gcalc::graph result(lhg);
	result.vertex_set.insert(rhg.vertex_set.begin(), rhg.vertex_set.end()); 
	result.edge_set.insert(rhg.edge_set.begin(), rhg.edge_set.end()); // TODO: check if this works as expected

	return result;
}

gcalc::graph gcalc::intersect(const graph& lhg, const graph& rhg)
{
	gcalc::graph result;
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

gcalc::graph gcalc::diff(const graph& lhg, const graph& rhg)
{
	gcalc::graph result;
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

gcalc::graph gcalc::cross(const graph& lhg, const graph& rhg)
{
	gcalc::graph result; // TODO: test this. Not sure about the product

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

gcalc::graph gcalc::complement(const graph& grap)
{
	gcalc::graph result; // TODO: check on complex graphs
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

void gcalc::printGraph(const graph& grap)
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


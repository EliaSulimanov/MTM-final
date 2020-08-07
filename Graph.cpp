#include "graph.h"
#include "graphHelper.h"
#include "graphException.h"

graph::graph()
{
	vertex_set.clear();
	edge_set.clear();
}

graph::graph(const graph& rhg)
{
	this->vertex_set = rhg.vertex_set;
	this->edge_set = rhg.edge_set;
}

graph& graph::operator=(const graph& rhg)
{
	this->vertex_set = rhg.vertex_set;
	this->edge_set = rhg.edge_set;
	return *this;
}

void graph::insertVertex(std::string vertex)
{
	if (graphHelper::vertexNameCheck(vertex))
	{
		if (this->vertex_set.find(vertex) != this->vertex_set.end()) // vertex already exists
		{
			throw graphException("Invalid graph syntax - vertex already exists");
		}
		else 
		{
			this->vertex_set.insert(vertex);
		}
	}
}

void graph::insertEdge(std::string src, std::string dest)
{
	if (graphHelper::vertexNameCheck(src) && graphHelper::vertexNameCheck(dest))
	{
		if (src.compare(dest) == 0) // self loop
		{
			throw graphException("Invalid graph syntax - self loop edge not allowed");
		}
		else if (this->vertex_set.find(src) == this->vertex_set.end() || this->vertex_set.find(dest) == this->vertex_set.end()) // vertex not exist
		{
			throw graphException("Invalid graph syntax - edge vertex not exist");
		}
		else
		{
			std::vector<std::string> temp {src, dest};
			if (this->edge_set.find(temp) != this->edge_set.end()) // edge exist
			{
				throw graphException("Invalid graph syntax - edge already exist");
			}
			else
			{
				this->edge_set.insert(temp);
			}
		}
	}
}

std::vector<std::pair<size_t, std::string> > graph::flatgraph()
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

graph graph::unite(const graph& lhg, const graph& rhg)
{
	graph result(lhg);
	result.vertex_set.insert(rhg.vertex_set.begin(), rhg.vertex_set.end()); 
	result.edge_set.insert(rhg.edge_set.begin(), rhg.edge_set.end()); // TODO: check if this works as expected

	return result;
}

graph graph::intersect(const graph& lhg, const graph& rhg)
{
	graph result;
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

graph graph::diff(const graph& lhg, const graph& rhg)
{
	graph result;
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

graph graph::cross(const graph& lhg, const graph& rhg)
{
	graph result; // TODO: test this. Not sure about the product

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

graph graph::complement(const graph& grap)
{
	graph result; // TODO: check on complex graphs
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

void graph::printGraph(const graph& grap)
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

graph* create()
{
	try
	{
		graph* return_graph = new graph();
		return return_graph;
	}
	catch (std::exception&)
	{
		std::cout << "Error: error occurred while creating new graph" << std::endl;
		return nullptr;
	}
}

void destroy(graph* graph)
{
	if (graph != nullptr)
	{
		delete graph;
	}
}

graph* addVertex(graph* graph, char* v)
{
	if (graph != nullptr)
	{
		if (v == NULL)
		{
			std::cout << "Error: memory error, vertex name is lost" << std::endl;
			return graph;
		}
		std::string vertex = v;
		try {
			graph->insertVertex(vertex);
			return graph;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			return nullptr;
		}
	}
	else
	{
		std::cout << "Error: The graph is null, can not add vertex" << std::endl;
		return nullptr;
	}
}

graph* addEdge(graph* graph, char* v1, char* v2)
{
	if (graph != nullptr)
	{
		if (v1 == NULL || v2 == NULL)
		{
			std::cout << "Error: memory error, vertex name is lost" << std::endl;
			return graph;
		}
		std::string vertex1 = v1;
		std::string vertex2 = v2;

		try {
			graph->insertEdge(vertex1, vertex2);
			return graph;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			return nullptr;
		}
	}
	else
	{
		std::cout << "Error: The graph is null, can not add edge" << std::endl;
		return nullptr;
	}
}

void disp(graph* graph)
{
	if (graph != nullptr)
	{
		try {
			graph::printGraph(*graph);
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Error: The graph is null, can not print" << std::endl;
	}
}

graph* graphUnion(graph* graph_in1, graph* graph_in2, graph* graph_out)
{
	if (graph_in1 != nullptr && graph_in2 != nullptr && graph_out != nullptr)
	{
		try {
			graph result = graph::unite(*graph_in1, *graph_in2);
			*graph_out = result;
			return graph_out;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			return graph_out;
		}
	}
	else
	{
		std::cout << "Error: Passed null graph, can not unite" << std::endl;
		return graph_out;
	}
}

graph* graphIntersection(graph* graph_in1, graph* graph_in2, graph* graph_out)
{
	if (graph_in1 != nullptr && graph_in2 != nullptr && graph_out != nullptr)
	{
		try {
			graph result = graph::intersect(*graph_in1, *graph_in2);
			*graph_out = result;
			return graph_out;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			return graph_out;
		}
	}
	else
	{
		std::cout << "Error: Passed null graph, can not intersect" << std::endl;
		return graph_out;
	}
}

graph* graphDifference(graph* graph_in1, graph* graph_in2, graph* graph_out)
{
	if (graph_in1 != nullptr && graph_in2 != nullptr && graph_out != nullptr)
	{
		try {
			graph result = graph::diff(*graph_in1, *graph_in2);
			*graph_out = result;
			return graph_out;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			return graph_out;
		}
	}
	else
	{
		std::cout << "Error: Passed null graph, can not difference" << std::endl;
		return graph_out;
	}
}

graph* graphProduct(graph* graph_in1, graph* graph_in2, graph* graph_out)
{
	if (graph_in1 != nullptr && graph_in2 != nullptr && graph_out != nullptr)
	{
		try {
			graph result = graph::cross(*graph_in1, *graph_in2);
			*graph_out = result;
			return graph_out;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			return graph_out;
		}
	}
	else
	{
		std::cout << "Error: Passed null graph, can not product" << std::endl;
		return graph_out;
	}
}

graph* graphComplement(graph* graph_in, graph* graph_out)
{
	if (graph_in != nullptr && graph_out != nullptr)
	{
		try {
			graph result = graph::complement(*graph_in);
			*graph_out = result;
			return graph_out;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			return graph_out;
		}
	}
	else
	{
		std::cout << "Error: Passed null graph, can not complement" << std::endl;
		return graph_out;
	}
}

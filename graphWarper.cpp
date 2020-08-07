#include "graphWarper.h"
#include "graphException.h"

graph* graphWarper::create()
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

void graphWarper::destroy(graph* graph)
{
    if (graph != nullptr)
    {
        delete graph;
    }
}

graph* graphWarper::addVertex(graph* graph, std::string v)
{
    if (graph != nullptr)
    {
		try {
			graph->insertVertex(v);
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

graph* graphWarper::addEdge(graph* graph, std::string v1, std::string v2)
{
	if (graph != nullptr)
	{
		try {
			graph->insertEdge(v1, v2);
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

void graphWarper::disp(graph* graph)
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

graph* graphWarper::graphUnion(graph* graph_in1, graph* graph_in2, graph* graph_out)
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

graph* graphWarper::graphIntersection(graph* graph_in1, graph* graph_in2, graph* graph_out)
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

graph* graphWarper::graphDifference(graph* graph_in1, graph* graph_in2, graph* graph_out)
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

graph* graphWarper::graphProduct(graph* graph_in1, graph* graph_in2, graph* graph_out)
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

graph* graphWarper::graphComplement(graph* graph_in, graph* graph_out)
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

#include "graphWarper.h"
#include "graphException.h"

gcalc::graph* graphWarper::create()
{
    try
    {
        gcalc::graph* return_graph = new gcalc::graph();
        return return_graph;
    }
    catch (std::exception&)
    {
        std::cout << "Error: error occurred while creating new graph" << std::endl;
        return nullptr;
    }
}

void graphWarper::destroy(gcalc::graph* graph)
{
    if (graph != nullptr)
    {
        delete graph;
    }
}

gcalc::graph* graphWarper::addVertex(gcalc::graph* graph, std::string v)
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

gcalc::graph* graphWarper::addEdge(gcalc::graph* graph, std::string v1, std::string v2)
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

void graphWarper::disp(gcalc::graph* graph)
{
	if (graph != nullptr)
	{
		try {
			gcalc::printGraph(*graph);
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

gcalc::graph* graphWarper::graphUnion(gcalc::graph* graph_in1, gcalc::graph* graph_in2, gcalc::graph* graph_out)
{
	if (graph_in1 != nullptr && graph_in2 != nullptr && graph_out != nullptr)
	{
		try {
			gcalc::graph result = gcalc::unite(*graph_in1, *graph_in2);
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

gcalc::graph* graphWarper::graphIntersection(gcalc::graph* graph_in1, gcalc::graph* graph_in2, gcalc::graph* graph_out)
{
	if (graph_in1 != nullptr && graph_in2 != nullptr && graph_out != nullptr)
	{
		try {
			gcalc::graph result = gcalc::intersect(*graph_in1, *graph_in2);
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

gcalc::graph* graphWarper::graphDifference(gcalc::graph* graph_in1, gcalc::graph* graph_in2, gcalc::graph* graph_out)
{
	if (graph_in1 != nullptr && graph_in2 != nullptr && graph_out != nullptr)
	{
		try {
			gcalc::graph result = gcalc::diff(*graph_in1, *graph_in2);
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

gcalc::graph* graphWarper::graphProduct(gcalc::graph* graph_in1, gcalc::graph* graph_in2, gcalc::graph* graph_out)
{
	if (graph_in1 != nullptr && graph_in2 != nullptr && graph_out != nullptr)
	{
		try {
			gcalc::graph result = gcalc::cross(*graph_in1, *graph_in2);
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

gcalc::graph* graphWarper::graphComplement(gcalc::graph* graph_in, gcalc::graph* graph_out)
{
	if (graph_in != nullptr && graph_out != nullptr)
	{
		try {
			gcalc::graph result = gcalc::complement(*graph_in);
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

#include "GraphHelper.h"
#include "Graph.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>

void gcalcLoop(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map);
void gcalcLoop(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, char* argv[]);
void deleteGraph(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::string GraphName);
void eval(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> command);

void gcalcLoop(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map) {
	while (true)
	{
		try
		{
			std::string command;

			std::cout << "Gcalc> ";
			std::getline(std::cin, command);
			std::vector<std::string> split_command = gcalc::GraphHelper::splitCommand(command);

 			if (split_command.size() == 0)
 			{
				if (std::cin.eof())
				{
					break;
				}
 				continue;
 			}
			else if (split_command.size() == 1)
			{
				if (split_command[0].compare("quit") == 0)
				{
					break;
				}
				else if (split_command[0].compare("reset") == 0)
				{
					symbol_map.clear();
				}
				else if (split_command[0].compare("who") == 0)
				{
					for (auto grap : symbol_map)
					{
						if (grap.second != nullptr)
						{
							std::cout << grap.first << std::endl;
						}
					}
				}
				else
				{
					std::cout << "Error: Unrecognized command" << std::endl;
				}
			}
			else {
				eval(symbol_map, split_command);
			}
		}
		catch (gcalc::FatalGraphException& e)
		{
			std::cerr << "Fatal Error: " << e.what() << std::endl;
			return;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}

void gcalcLoop(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, char* argv[]) {
	std::ifstream ifs(argv[0]);
	if (!ifs.is_open())
	{
		std::cerr << "Fatal error: Error opening input file" << std::endl;
		return;
	}
	try
	{
		std::cin.rdbuf(ifs.rdbuf());
	}
	catch (const std::exception&)
	{
		std::cerr << "Fatal error: Error redirecting input" << std::endl;
		return;
	}

	std::ofstream ofs(argv[1]);
	if (!ofs.is_open())
	{
		std::cerr << "Fatal error: Error opening output file" << std::endl;
		return;
	}
	try
	{
		std::cout.rdbuf(ofs.rdbuf());
	}
	catch (const std::exception&)
	{
		std::cerr << "Fatal error: Error redirecting output" << std::endl;
		return;
	}

	std::string command;
	while (std::getline(std::cin, command) && command.compare("quit") != 0)
	{
		try
		{
			std::vector<std::string> split_command = gcalc::GraphHelper::splitCommand(command);

			if (split_command.size() == 0)
			{
				continue;
			}
			else if (split_command.size() == 1)
			{
				if (split_command[0].compare("quit") == 0)
				{
					break;
				}
				else if (split_command[0].compare("reset") == 0)
				{
					symbol_map.clear();
				}
				else if (split_command[0].compare("who") == 0)
				{
					for (auto grap : symbol_map)
					{
						if (grap.second != nullptr)
						{
							std::cout << grap.first << std::endl;
						}
					}
				}
				else
				{
					std::cout << "Error: Unrecognized command" << std::endl;
				}
			}
			else {
				eval(symbol_map, split_command);
			}
		}
		catch (gcalc::FatalGraphException& e)
		{
			std::cerr << "Fatal Error: " << e.what() << std::endl;
			return;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}

void deleteGraph(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::string GraphName) 
{
	try
	{
		symbol_map.erase(GraphName); // TODO: check for memory leaks
	}
	catch (std::exception)
	{}
}

void eval(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> command)
{
	try
	{
		if (gcalc::GraphHelper::checkNoDuplicateCommands(command)) // TODO: see if this is a good check
		{
			if (command[0].compare("print") == 0)
			{
				if (command[1].compare("(") != 0)
				{
					throw gcalc::GraphException("Invalid syntax");
				}
				if (command.size() == 4) // The arg is graph name
				{
					if (symbol_map.find(command[2]) != symbol_map.end())
					{
						gcalc::print(*(symbol_map.at(command[2])));
					}
					else
					{
						throw gcalc::GraphException("Undefined variable");
					}
				}
				else // The arg is complex graph def
				{
					// TODO check on complex graphs
					auto graph_start = command.begin() + 2;
					std::vector<std::string> temp_vector(graph_start, command.end());
					gcalc::print(*(gcalc::GraphHelper::commandOperation(symbol_map, temp_vector)));
				}
				
			}
			else if (command[0].compare("delete") == 0) // Delete can only work on existing graph.
			{
				if (command[1].compare("(") != 0 || command.size() != 4)
				{
					throw gcalc::GraphException("Invalid syntax");
				}
				deleteGraph(symbol_map, command[2]);
			}
			else // assignment
			{
				if (gcalc::GraphHelper::checkGraphName(command[0]))
				{
					if (command[1].compare("=") != 0)
					{
						throw gcalc::GraphException("Unrecognized command");
					}
					else
					{
						auto graph_start = command.begin() + 2;
						std::vector<std::string> temp_vector(graph_start, command.end());
						// TODO: temp check. need to add a functionality for more than one graph

						auto symbol_map_iter = symbol_map.find(command[0]);
						if (symbol_map_iter != symbol_map.end())
						{
							std::shared_ptr<gcalc::Graph> temp_graph = gcalc::GraphHelper::commandOperation(symbol_map, temp_vector);
							symbol_map_iter->second = temp_graph;
						}
						else
						{
							symbol_map.insert(std::pair<std::string, std::shared_ptr<gcalc::Graph>>(command[0], gcalc::GraphHelper::commandOperation(symbol_map, temp_vector)));
						}
					}
				}
			}
		}
	}
	catch (gcalc::FatalGraphException& e)
	{
		// TODO
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

int main(int argc, char* argv[]) {
	std::map<std::string, std::shared_ptr<gcalc::Graph>> symbol_map;
	if (argc == 1)
	{
		gcalcLoop(symbol_map);
	}
	else if (argc == 3) 
	{
		gcalcLoop(symbol_map, argv);
	}
	else
	{
		std::cerr << "Fatal Error: Invalid number of arguments" << std::endl;
		return 0;
	}
}
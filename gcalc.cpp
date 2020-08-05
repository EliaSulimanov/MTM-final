#include "GraphHelper.h"
#include "Graph.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>

void gcalcLoop(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map);
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
			// TODO
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
					// TODO
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
						if (symbol_map.find(command[0]) != symbol_map.end())
						{
							throw gcalc::GraphException("Variable already exist");
						}
						else
						{
							// TODO: temp check. need to add a functionality for more than one graph
							auto graph_start = command.begin() + 2;
							std::vector<std::string> temp_vector(graph_start, command.end());

							symbol_map.insert(std::pair<std::string, std::shared_ptr<gcalc::Graph>>(command[0], gcalc::GraphHelper::commandToGraph(temp_vector)));
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
	//map graphs name and pointer to the graph
	std::map<std::string, std::shared_ptr<gcalc::Graph>> symbol_map;
	if (argc == 1)
	{
		gcalcLoop(symbol_map);
	}
	else if (argc == 3) 
	{
		// TODO: check arguments and so on...
	}
	else
	{
		// TODO: invalid number of args, print error and quit.
	}
}
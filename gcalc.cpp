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
			// TODO
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
		if (gcalc::GraphHelper::checkNoDuplicateCommands(command) && gcalc::GraphHelper::checkSpecialChars(command)) // TODO: see if this is a good check
		{
			if (command.size() == 4) //easy command, no graph evaluation
			{
				if (command[0].compare("print") == 0)
				{
					auto graph_name = symbol_map.find(command[2]);
					if (graph_name != symbol_map.end()) // Variable exist
					{
						if (graph_name->second != nullptr)
						{
							gcalc::print(*(graph_name->second));
						}
						else // Lost a graph
						{

						}
					} 
					else
					{
					}
				}
			}
			else // complex command
			{
				// TODO
			}
		}
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
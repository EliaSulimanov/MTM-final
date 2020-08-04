#include "GraphHelper.h"
#include "Graph.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>

void gcalcLoop(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map);
void deleteGraph(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::string GraphName);
void executeCommand(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> split_command);


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
			else // it is a one block command (no white spaces)
			{
				try 
				{
					executeCommand(symbol_map, split_command); // TODO: continue
				}
				catch (gcalc::FatalGraphException())
				{
					// TODO: write about that error and close the program.
					break;
				}
				catch (std::exception& e)
				{
					std::cout << "Error: " << e.what() << std::endl;
				}
			}
		}
		else {
			
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

void executeCommand(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> split_command)
{
	if (split_command[0].rfind("print(", 0) != std::string::npos)
	{
		if (split_command[0][split_command[0].size() - 1] != ')') 
		{
			throw gcalc::GraphException("Invalid syntax");
		}
		else
		{

		}
	}
	else if (split_command[0].rfind("delete(", 0) != std::string::npos)
	{
		if (split_command[0][split_command[0].size() - 1] != ')')
		{
			throw gcalc::GraphException("Invalid syntax");
		}
		else
		{

		}
	}
	else // Must be assignment
	{

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
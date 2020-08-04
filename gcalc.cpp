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
			else
			{
				try 
				{
					executeCommand(symbol_map, split_command);
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
	if (split_command[0].find("print") != std::string::npos)
	{
		if (gcalc::GraphHelper::checkCommand(split_command))
		{

		}
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
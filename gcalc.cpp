#include "graphHelper.h"
#include "graph.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>

void gcalcLoop(std::map<std::string, std::shared_ptr<graph>>& symbol_map);
void gcalcLoop(std::map<std::string, std::shared_ptr<graph>>& symbol_map, char* argv[]);
void deletegraph(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::string graphName);
void eval(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> command, std::string real_command);

void gcalcLoop(std::map<std::string, std::shared_ptr<graph>>& symbol_map) {
	while (true)
	{
		try
		{
			std::string command;

			std::cout << "Gcalc> ";
			std::getline(std::cin, command);
			std::vector<std::string> split_command = graphHelper::splitCommand(command);

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
				eval(symbol_map, split_command, command);
			}
		}
		catch (FatalgraphException& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			return;
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}

void gcalcLoop(std::map<std::string, std::shared_ptr<graph>>& symbol_map, char* argv[])
{
	std::string command;

	std::ifstream ifs(argv[1]);
	std::ofstream ofs(argv[2]);

	std::streambuf *backup_in_stream, * backup_out_stream;

	bool run = true;

	if (ifs.is_open())
	{
		if (ofs.is_open())
		{
			backup_in_stream = std::cin.rdbuf();
			backup_out_stream = std::cout.rdbuf();

			std::cin.rdbuf(ifs.rdbuf());
			std::cout.rdbuf(ofs.rdbuf());
			while (run && getline(ifs, command))
			{
				
				try
				{
					std::vector<std::string> split_command = graphHelper::splitCommand(command);
					if (split_command.size() == 0)
					{
						if (std::cin.eof())
						{
							break;
						}
					}
					else if (split_command.size() == 1)
					{
						if (split_command[0].compare("quit") == 0)
						{
							run = false;
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
						eval(symbol_map, split_command, command);
					}
				}
				catch (FatalgraphException& e)
				{
					std::cerr << "Error: " << e.what() << std::endl;
					return;
				}
				catch (std::exception& e)
				{
					std::cout << "Error: " << e.what() << std::endl;
				}
			}
			
			std::cin.rdbuf(backup_in_stream);
			std::cout.rdbuf(backup_out_stream);

			ifs.close();
			ofs.close();
		}
		else
		{
			ifs.close();
			std::string output_file_path(argv[2]);
			std::cerr << "Error: unable to open output file: " << output_file_path << std::endl;
			return;
		}
	}
	else
	{
		std::string input_file_path(argv[1]);
		std::cerr << "Error: unable to open input file: " << input_file_path << std::endl;
		return;
	}
}

void deletegraph(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::string graphName) 
{
	try
	{
		symbol_map.erase(graphName); 
	}
	catch (std::exception)
	{}
}

void eval(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> command, std::string real_command)
{
	if (graphHelper::checkNoDuplicateCommands(command))
	{
		if (command[0].compare("print") == 0)
		{
			if (command[1].compare("(") != 0)
			{
				throw graphException("Invalid syntax- missing opening bracket after print command");
			}
			if (command[1].compare("(") == 0 && command[command.size() - 1].compare(")") != 0)
			{
				throw graphException("Invalid syntax- print command missing bracket");
			}
			if (command.size() == 4) // The argument is graph name
			{
				if (symbol_map.find(command[2]) != symbol_map.end())
				{
					graph::printGraph(*(symbol_map.at(command[2])));
				}
				else
				{
					throw graphException("Undefined variable: " + command[2]);
				}
			}
			else // The argument is complex graph def
			{
				auto graph_start = command.begin() + 2;
				std::vector<std::string> temp_vector(graph_start, command.end());
				temp_vector.pop_back();
				graph::printGraph(*(graphHelper::commandOperation(symbol_map, temp_vector, real_command)));
			}
		}
		else if (command[0].compare("delete") == 0) // Delete can only work on existing graph.
		{
			if (command[1].compare("(") != 0 || command.size() != 4)
			{
				throw graphException("Invalid syntax- delete can only take graph name");
			}
			if (command[1].compare("(") == 0 && command[command.size() - 1].compare(")") != 0)
			{
				throw graphException("Invalid syntax- missing ) sign");
			}
			deletegraph(symbol_map, command[2]);
		}
		else if (command[0].compare("save") == 0)
		{
			if (command[1].compare("(") != 0)
			{
				throw graphException("Invalid syntax, missing starting parentheses on save command");
			}
			if (command[1].compare("(") == 0 && command[command.size() - 1].compare(")") != 0)
			{
				throw graphException("Invalid syntax, missing ending parentheses on save command");
			}

			auto command_start = command.begin() + 2;
			std::vector<std::string> temp_vector(command_start, command.end());
			temp_vector.pop_back();

			auto last_comma = std::find(temp_vector.rbegin(), temp_vector.rend(), ",");
			if (last_comma == temp_vector.rend())
			{
				throw graphException("Invalid syntax, missing filename or graph in save command");
			}

			std::vector<std::string> filename(last_comma.base(), temp_vector.end());
			
			if (graphHelper::checkFileName(filename))
			{
				std::vector<std::string> temp_graph_command(temp_vector.begin(), last_comma.base() - 1);
				graph temp_graph = *(graphHelper::commandOperation(symbol_map, temp_graph_command, real_command));

				size_t last_comma_index = real_command.find_last_of(",");
				auto file_path = real_command.substr(last_comma_index + 1);
				file_path.erase(std::find(file_path.begin(), file_path.end(), ')'), file_path.end());
				graphHelper::clearWhiteSpaces(file_path);

				try
				{
					auto flat_g = temp_graph.flatgraph();

					std::ofstream fd(file_path, std::ios_base::binary);
					if (fd.is_open())
					{
						if (flat_g.size() < 2)
						{
							throw graphException("Error while saving graph to file");
						}
						for (size_t i = 0; i < flat_g.size(); i++)
						{
							fd.write((char*)&flat_g[i].first, sizeof(size_t));
							for (auto ch : flat_g[i].second)
							{
								fd.write(&ch, sizeof(char));
							}
						}
						fd.close();
					}
					else
					{
						throw graphException("Error occurred while saving the graph to the file: " + file_path);
					}
					if (fd.bad())
					{
						throw graphException("Error occurred while saving the graph to the file: " + file_path);
					}
				}
				catch (const std::exception&)
				{
					throw graphException("Error occurred while saving the graph to the file: " + file_path);
				}
			}
		}
		else // assignment
		{
			if (graphHelper::checkgraphName(command[0]))
			{
				if (command[1].compare("=") != 0)
				{
					throw graphException("Unrecognized command");
				}
				else
				{
					auto graph_start = command.begin() + 2;
					std::vector<std::string> temp_vector(graph_start, command.end());

					auto symbol_map_iter = symbol_map.find(command[0]);
					if (symbol_map_iter != symbol_map.end())
					{
						std::shared_ptr<graph> temp_graph = graphHelper::commandOperation(symbol_map, temp_vector, real_command);
						symbol_map_iter->second = temp_graph;
					}
					else
					{
						symbol_map.insert(std::pair<std::string, std::shared_ptr<graph>>(command[0], graphHelper::commandOperation(symbol_map, temp_vector, real_command)));
					}
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
	std::map<std::string, std::shared_ptr<graph>> symbol_map;
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
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		return 0;
	}
}
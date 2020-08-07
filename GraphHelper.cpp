#include "graphHelper.h"
#include <stack>
#include <set>
#include <cctype>
#include <algorithm>

const std::set<std::string> invalid_names = {"quit", "reset", "who", "print", "delete", "load", "save" };

const std::set<std::string> special_chars = {"=", "{", "}", ",", "|", "<", ">", "(", ")", "!", "+", "^", "-", "*"};

bool graphHelper::vertexNameCheck(std::string vertex_name) {
	if (vertex_name.empty()) {
		throw graphException("Empty vertex name");
	}
	if (invalid_names.find(vertex_name) != invalid_names.end()) // function name
	{
		throw graphException("Vertex name can not be a function name");
	}
	std::stack<char> pranthesis_stack;
	for(char ch : vertex_name)
	{
		if (!isalnum(ch) && ch != '[' && ch != ']' && ch != ';') {
			throw graphException("Vertex name can not have this sign: " + ch);
		}
		else
		{
			if (ch == '[') {
				pranthesis_stack.push(ch);
				continue;
			}
			if (ch == ']') {
				if (pranthesis_stack.empty()) {
					throw graphException("Bad vertex name");
				}
				pranthesis_stack.pop();
				continue;
			}
			if (ch == ';') {
				if (pranthesis_stack.empty())
				{
					throw graphException("Bad vertex name");
				}
			}
		}
	}
	if (!pranthesis_stack.empty()) {
		throw graphException("Bad vertex name");
	}
	return true;
}

size_t graphHelper::findNextTokenPos(std::string command) {
	char ch;
	size_t i = 0;
	for (; i < command.size(); i++)
	{
		ch = command[i];
		if (special_chars.find(std::string(1, ch)) != special_chars.end()) // TODO: add catch for bad_alloc and throw fatal exception
		{
			return i;
		}
	}
	return i;
}

void graphHelper::clearWhiteSpaces(std::string& command)
{
	clearChar(command, ' ');
	clearChar(command, '\t');
	clearChar(command, '\n');
	clearChar(command, '\v');
	clearChar(command, '\f');
	clearChar(command, '\r');
}

void graphHelper::clearChar(std::string& command, char ch)
{
	size_t left = command.find_first_not_of(ch);
	size_t right = command.find_last_not_of(ch);
	command.erase(right + 1);
	command.erase(0, left);
}

std::vector<std::string> graphHelper::splitCommand(const std::string command)
{
	std::vector<std::string> split_command;
	if (checkParenthesesBalance(command))
	{
		std::string temp_command = command;

		while (!temp_command.empty())
		{
			size_t len = findNextTokenPos(temp_command);
			std::string sub_command = temp_command.substr(0, len);
			if (!sub_command.empty() && sub_command.find_first_not_of(' ') != std::string::npos)
			{
				clearWhiteSpaces(sub_command);
				split_command.push_back(sub_command);
			}

			temp_command.erase(0, len);
			std::string oper = temp_command.substr(0, 1);
			if (!oper.empty() && oper.find_first_not_of(' ') != std::string::npos)
			{
				clearWhiteSpaces(oper);
				split_command.push_back(oper);
			}
			temp_command.erase(0, 1);
		}
	}
	return split_command;
}

bool graphHelper::checkNoDuplicateCommands(std::vector<std::string> command)
{
	int num_of_print = 0;
	int num_of_delete = 0;
	int num_of_equal = 0;
	int num_of_who = 0;
	int num_of_quit = 0;
	int num_of_reset = 0;
	for (auto word : command)
	{
		if (word.compare("print") == 0)
		{
			num_of_print++;
		}
		else if (word.compare("delete") == 0)
		{
			num_of_delete++;
		}
		else if (word.compare("=") == 0)
		{
			num_of_equal++;
		}
		else if (word.compare("who") == 0)
		{
			num_of_who++;
		}
		else if (word.compare("quit") == 0)
		{
			num_of_quit++;
		}
		else if (word.compare("reset") == 0)
		{
			num_of_reset++;
		}
	}

	if (num_of_who > 0 || num_of_quit > 0 || num_of_reset > 0)
	{
		throw graphException("Invalid syntax, only one command per line allowed");
	}

	if (num_of_print > 1 || num_of_delete > 1 || num_of_equal > 1)
	{
		throw graphException("Invalid syntax, only one command per line allowed");
	}

	if ((num_of_print == 1 && (num_of_delete > 0 || num_of_equal > 0)) ||
		(num_of_delete == 1 && (num_of_print > 0 || num_of_equal > 0)) ||
		(num_of_equal == 1 && (num_of_delete > 0 || num_of_print > 0)))
	{
		throw graphException("Invalid syntax, only one command per line allowed");

	}

	return true;
}

bool graphHelper::checkgraphSyntax(std::vector<std::string> command)
{
	if (command.size() < 2)
	{
		throw graphException("Invalid graph syntax, graph definition is too short");
	}
	if (command[0].compare("{") != 0 || command[command.size() - 1].compare("}") != 0)
	{
		throw graphException("Invalid graph syntax, graph definition missing parentheses");
	}
	if (command.size() == 2) // Empty graph
	{
		return true;
	}
	if (std::count(command.begin(), command.end(), "|") > 1)
	{
		throw graphException("Invalid graph syntax, max 1 pipe allowed");
	}
	if (std::count(command.begin(), command.end(), "=") != 0)
	{
		throw graphException("Invalid graph syntax, no equal sign allowed inside definition");
	}
	
	const std::set<std::string> allowed_signs = { "," ,"<" ,">" };
	bool alt_sign = false;

	auto pipe_pos = std::find(command.begin(), command.end(), "|");
	auto vertex_side_iter = command.begin() + 1;
	while (vertex_side_iter != pipe_pos)
	{
		if (alt_sign == true) // Should be a sign
		{
			if ((*vertex_side_iter).compare(",") != 0) // Should be a sign but it is not, or it is not allowed sign
			{
				if ((*vertex_side_iter).compare("}") == 0 && vertex_side_iter + 1 == command.end()) // new check, for one vertex
				{
					return true;
				}
				throw graphException("Invalid graph syntax");
			}
			alt_sign = false;
		}
		else // Should be a word
		{
			if (vertexNameCheck((*vertex_side_iter)))
			{
				alt_sign = true;
			}
		}
		vertex_side_iter++;
	}

	if (pipe_pos != command.end())
	{
		int sign_type = 0; // 0='<', 1=',' ,2='>' 
		bool inside_edge = false;
		auto edge_side_iter = pipe_pos + 1;
		while (edge_side_iter != command.end())
		{
			if ((*edge_side_iter).compare("}") == 0)
			{
				if (edge_side_iter + 1 == command.end())
				{
					break;
				}
				else
				{
					throw graphException("Invalid graph syntax");
				}
			}

			if (alt_sign == true)
			{
				switch (sign_type)
				{
				case 0:
					if ((*edge_side_iter).compare("<") != 0) // Should be a sign but it is not, or it is not allowed sign
					{
						throw graphException("Invalid graph syntax");
					}
					sign_type = 1;
					alt_sign = false;
					inside_edge = true;
					break;
				case 1:
					if ((*edge_side_iter).compare(",") != 0) // Should be a sign but it is not, or it is not allowed sign
					{
						throw graphException("Invalid graph syntax");
					}
					if (inside_edge)
					{
						alt_sign = false;
						sign_type = 2;
					}
					else
					{
						sign_type = 0;
					}
					break;
				case 2:
					if ((*edge_side_iter).compare(">") != 0) // Should be a sign but it is not, or it is not allowed sign
					{
						throw graphException("Invalid graph syntax");
					}
					sign_type = 1;
					alt_sign = true;
					inside_edge = false;
					break;
				default:
					throw FatalgraphException("Fatal error while checking graph syntax");
					break;
				}
			}
			else
			{
				if (vertexNameCheck((*edge_side_iter)))
				{
					alt_sign = true;
				}
			}
			edge_side_iter++;
		}
	}

	return true;
}

std::shared_ptr<graph> graphHelper::commandTograph(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> split_command)
{
	graph result_graph;

	std::vector<std::string> command = split_command;

	if (command.size() == 0)
	{
		throw graphException("Invalid syntax, empty command is not allowed");
	}
	// TODO: test that, as commandOper is doing the complemention.
	/*
	if (command[0].compare("!") == 0)
	{
		command.erase(command.begin());
		return std::shared_ptr<graph>(new graph(complement(*(commandTograph(symbol_map, command)))));
	}*/

	if (command.size() == 1) // It is a variable name
	{
		if (symbol_map.find(command[0]) == symbol_map.end())
		{
			throw graphException("Undefined variable");
		}
		else
		{	
			return symbol_map.at(command[0]);
		}
	}

	if (command[0].compare("{") != 0 || command[command.size() - 1].compare("}") != 0)
	{
		throw graphException("Invalid syntax");
	}

	if (checkgraphSyntax(command))
	{
		int i = 1;
		bool in_the_egde_block = false;
		bool inside_edge = false;
		while (command[i].compare("}") != 0)
		{
			if (command[i].compare("|") == 0)
			{
				in_the_egde_block = true;
				i++;
				continue;
			}
			if (in_the_egde_block)
			{
				if (!inside_edge)
				{
					if (command[i].compare(",") == 0)
					{
						if (!(command[i - 1].compare(">") == 0 && command[i + 1].compare("<") == 0))
						{
							throw graphException("Invalid syntax");
						}
					}
					if (command[i].compare("<") == 0)
					{
						inside_edge = true;
					}
				}
				else
				{
					if (command[i + 1].compare(",") != 0 || command[i + 3].compare(">") != 0)
					{
						throw graphException("Invalid syntax");
					}
					else
					{
						result_graph.insertEdge(command[i], command[i + 2]);
						i += 3; // jump to >
						inside_edge = false;
					}
				}
			}
			else
			{
				if (command[i].compare(",") == 0) // TODO: add check for it.
				{
					i++;
					continue;
				}
				result_graph.insertVertex(command[i]);
			}
			i++;
		}
	}

	return std::shared_ptr<graph>(new graph(result_graph));
}

bool graphHelper::checkgraphName(std::string graph_name)
{
	if (graph_name.empty())
	{
		throw graphException("Invalid graph name");
	}
	if (!isalpha(graph_name[0]))
	{
		throw graphException("Invalid graph name");
	}
	for (auto ch : graph_name)
	{
		if (!isalnum(ch))
		{
			throw graphException("Invalid graph name");
		}
	}
	if (invalid_names.find(graph_name) != invalid_names.end()) // function name
	{
		throw graphException("Invalid graph name");
	}

	// TODO: add check if it is function name

	return true;
}

std::shared_ptr<graph> graphHelper::evaluateBinaryOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> left_graph, std::vector<std::string> right_graph, std::string oper, std::string real_command)
{
	if (!isBinaryOper(oper))
	{
		throw graphException("Invalid syntax, Unknown operation");
	}

	std::string l_graph, r_graph;
	for (auto word : left_graph)
	{
		l_graph.append(word);
	}
	
	for (auto word : right_graph)
	{
		r_graph.append(word);
	}
	
	if (l_graph.empty() || r_graph.empty())
	{
		throw graphException("Invalid syntax, binary operation must have 2 args");
	}
	
	if (checkgraphParentheses(l_graph) && checkgraphParentheses(r_graph))
	{

		graph l_g = (*(commandOperation(symbol_map, left_graph, real_command)));
		graph r_g = (*(commandOperation(symbol_map, right_graph, real_command)));

		return evaluateBinaryOperation(symbol_map, std::shared_ptr<graph>(new graph(l_g)), std::shared_ptr<graph>(new graph(r_g)), oper);
	}
	else
	{
		throw graphException("Invalid graph syntax");
	}
}

std::shared_ptr<graph> graphHelper::evaluateBinaryOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::shared_ptr<graph> left_graph, std::shared_ptr<graph> right_graph, std::string oper)
{
	graph result_graph;

	switch (oper[0])
	{
	case '+':
		result_graph = graph::unite(*left_graph, *right_graph);
		break;
	case '-':
		result_graph = graph::diff(*left_graph, *right_graph);
		break;
	case '^':
		result_graph = graph::intersect(*left_graph, *right_graph);
		break;
	case '*':
		result_graph = graph::cross(*left_graph, *right_graph);
		break;
	default:
		throw FatalgraphException("Fatal error while evaluating operation");
		break;
	}

	return std::shared_ptr<graph>(new graph(result_graph));
}

std::shared_ptr<graph> graphHelper::evaluateBinaryOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> left_graph, std::shared_ptr<graph> right_graph, std::string oper)
{
	if (!isBinaryOper(oper))
	{
		throw graphException("Invalid syntax, Unknown operation");
	}

	std::string l_graph;
	for (auto word : left_graph)
	{
		l_graph.append(word);
	}
	
	if (l_graph.empty())
	{
		throw graphException("Invalid syntax, binary operation must have 2 args");
	}

	if (checkgraphParentheses(l_graph))
	{
		graph l_g = (*(commandTograph(symbol_map, left_graph)));

		return evaluateBinaryOperation(symbol_map, std::shared_ptr<graph>(new graph(l_g)), right_graph, oper);
	}
	else
	{
		throw graphException("Invalid graph syntax");
	}
}

std::shared_ptr<graph> graphHelper::evaluateBinaryOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::shared_ptr<graph> left_graph, std::vector<std::string> right_graph, std::string oper)
{
	if (!isBinaryOper(oper))
	{
		throw graphException("Invalid syntax, Unknown operation");
	}

	std::string r_graph;
	for (auto word : right_graph)
	{
		r_graph.append(word);
	}

	if (r_graph.empty())
	{
		throw graphException("Invalid syntax, binary operation must have 2 args");
	}

	if (checkgraphParentheses(r_graph))
	{
		graph r_g = (*(commandTograph(symbol_map, right_graph)));

		return evaluateBinaryOperation(symbol_map, left_graph, std::shared_ptr<graph>(new graph(r_g)), oper);
	}
	else
	{
		throw graphException("Invalid graph syntax");
	}
}

bool graphHelper::isBinaryOper(std::string oper)
{
	if (oper.size() != 1)
		return false;
	if (oper.compare("+") == 0 || oper.compare("-") == 0 || oper.compare("^") == 0 || oper.compare("*") == 0)
	{
		return true;
	}
	return false;
}

bool graphHelper::isOpeningSign(std::string oper)
{
	return oper.compare("(") == 0;
}

bool graphHelper::isClosingSign(std::string oper)
{
	return oper.compare(")") == 0;
}

std::shared_ptr<graph> graphHelper::commandOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> command, std::string real_command)
{
	if (command.empty())
	{
		throw graphException("Empty command");
	}

	if (command[0].compare("(") == 0 && command[command.size() - 1].compare(")") == 0) // TODO: NEW TEST
	{
		command.pop_back();
		command.erase(command.begin());
		return graphHelper::commandOperation(symbol_map, command, real_command);
	}

	std::stack<std::string> brackets_stack;
	
	std::stack<std::string> crully_stack;

	for (auto iter = command.rbegin(); iter != command.rend(); iter++)
	{
		if ((*iter).compare(")") == 0)
		{
			brackets_stack.push(*iter);
		}

		if ((*iter).compare("(") == 0)
		{
			brackets_stack.pop();
		}

		if (brackets_stack.empty())
		{
			if (isBinaryOper(*iter))
			{
				std::vector<std::string> left_v(command.begin(), iter.base() - 1);
				std::string op = (*iter);
				std::vector<std::string> right_v(iter.base(), command.end());
				return graphHelper::evaluateBinaryOperation(symbol_map, left_v, right_v, op, real_command); //TODO: check if slice went well
			}
		}
	}

	if (command[0].compare("!") == 0) // TODO check it out
	{
		command.erase(command.begin());
		return std::shared_ptr<graph>(new graph(graph::complement(*(commandOperation(symbol_map, command, real_command)))));
	}

	if (command[0].compare("{") == 0 && command[command.size() - 1].compare("}") == 0)
	{
		return graphHelper::commandTograph(symbol_map, command);
	}

	if (symbol_map.find(command[0]) == symbol_map.end())
	{
		if (command[0].compare("load") == 0)
		{
			if (command.size() != 4)
			{
				throw graphException("Invalid load command");
			}
			return loadgraph(symbol_map, command, real_command);
		}
		throw graphException("Undefined variable");
	}

	return symbol_map.at(command[0]);
}

std::shared_ptr<graph> graphHelper::loadgraph(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> command, std::string real_command)
{
	auto file_path = command[2];

	if (command[1].compare("(") != 0)
	{
		throw graphException("Invalid syntax, missing starting parentheses on load command");
	}
	if (command[1].compare("(") == 0 && command[command.size() - 1].compare(")") != 0)
	{
		throw graphException("Invalid syntax, missing ending parentheses on load command");
	}
	std::vector<std::string> name_check = { file_path };
	graph temp_graph;
	if (checkFileName(name_check))
	{
		try
		{
			std::ifstream fd(file_path, std::ios_base::binary);
			if (fd.is_open())
			{
				size_t num_of_vertexs = 0;
				fd.read((char*)&num_of_vertexs, sizeof(int));

				size_t num_of_edges = 0;
				fd.read((char*)&num_of_edges, sizeof(int));

				for (size_t i = 0; i < num_of_vertexs; i++)
				{
					size_t vertex_name_len = 0;

					fd.read((char *)&vertex_name_len, sizeof(int));

					char* temp = new char[vertex_name_len + 1];
					
					for (size_t i = 0; i < vertex_name_len; i++)
					{
						fd.read((char*)&temp[i], sizeof(char));
					}
					temp[vertex_name_len] = '\0';
					std::string vertex_name(temp);
					delete[] temp; // Check if memory leaks
					temp_graph.insertVertex(vertex_name);
				}

				for (size_t i = 0; i < num_of_edges; i++)
				{
					size_t src_vertex_name_len = 0;
					fd.read((char*)&src_vertex_name_len, sizeof(int));
					char* temp = new char[src_vertex_name_len + 1];
					for (size_t i = 0; i < src_vertex_name_len; i++)
					{
						fd.read((char*)&temp[i], sizeof(char));
					}
					temp[src_vertex_name_len] = '\0';

					size_t dest_vertex_name_len = 0;
					fd.read((char*)&dest_vertex_name_len, sizeof(int));
					char* temp_b = new char[dest_vertex_name_len + 1];
					for (size_t i = 0; i < dest_vertex_name_len; i++)
					{
						fd.read((char*)&temp_b[i], sizeof(char));
					}
					temp_b[dest_vertex_name_len] = '\0';

					std::string src_vertex_name(temp);
					std::string dest_vertex_name(temp_b);

					delete[] temp; // TODO: check if memory leaks
					delete[] temp_b; // TODO: check if memory leaks
					
					temp_graph.insertEdge(src_vertex_name, dest_vertex_name);
				}
				fd.close();
			}
			else
			{
				throw graphException("Unable to open the file: " + file_path);
			}
		}
		catch (std::bad_alloc& e)
		{
			throw FatalgraphException("Fatal error- out of memory");
		}
		catch (const std::exception&)
		{
			throw graphException("Error occurred while loading the graph from the file: " + file_path);
		}
	}

	return std::shared_ptr<graph>(new graph(temp_graph));
}

bool graphHelper::checkgraphParentheses(std::string normal_command)
{
	std::stack<char> pre_stack;
	for (char ch : normal_command)
	{
		if (ch == '{')
		{
			pre_stack.push(ch);
		}
		else if (ch == '}')
		{
			if (pre_stack.empty())
			{
				throw graphException("Invalid syntax");
			}
			pre_stack.pop();
		}

		if (pre_stack.size() > 1)
		{
			throw graphException("Invalid syntax");
		}
	}
	if (!pre_stack.empty())
	{
		throw graphException("Invalid syntax");
	}

	return true;
}

bool graphHelper::checkFileName(std::vector<std::string> filename)
{
	if (filename.empty())
	{
		throw graphException("Invalid file name- empty file name is not allowed");
	}

	std::set<std::string> disallowed_signs = { ",", "{", "}", "[", "]", "(", ")" , "\r", "\f", "\v", "\n", "\t"};

	for (auto word : filename)
	{
		if (disallowed_signs.find(word) != disallowed_signs.end())
		{
			throw graphException("Invalid file name- brackets and commas are disallowed");
		}
	}

	auto last_name_split = filename[filename.size() - 1];
	if (filename[0][0] == '"' || last_name_split[last_name_split.size() - 1] == '"')
	{
		throw graphException("Invalid file name- no brackets around file name allowed");
	}

	return true;
}

bool graphHelper::checkParenthesesBalance(std::string normal_command)
{
	if (checkgraphParentheses(normal_command))
	{
		std::stack<char> pre_stack;

		for (auto ch : normal_command)
		{
			if (ch == '[' || ch == '(' || ch == '{' || ch == '<')
			{
				pre_stack.push(ch);
				continue;
			}

			switch (ch)
			{
			case ']':
				if (pre_stack.top() == '(' || pre_stack.top() == '{' || pre_stack.top() == '<')
				{
					throw graphException("Invalid syntax");
				}
				else
				{
					pre_stack.pop();
				}
				break;
			case ')':
				if (pre_stack.top() == '[' || pre_stack.top() == '{' || pre_stack.top() == '<')
				{
					throw graphException("Invalid syntax");
				}
				else
				{
					pre_stack.pop();
				}
				break;
			case '}':
				if (pre_stack.top() == '[' || pre_stack.top() == '(' || pre_stack.top() == '<')
				{
					throw graphException("Invalid syntax");
				}
				else
				{
					pre_stack.pop();
				}
				break;
			case '>':
				if (pre_stack.top() == '[' || pre_stack.top() == '(' || pre_stack.top() == '{')
				{
					throw graphException("Invalid syntax");
				}
				else
				{
					pre_stack.pop();
				}
				break;
			default:
				break;
			}
		}
		return (pre_stack.empty());
	}
	return true;
}
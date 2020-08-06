#include "GraphHelper.h"
#include <stack>
#include <set>
#include <cctype>
#include <algorithm>

const std::set<std::string> invalid_names = {"Graph", "operator", "insertVertex",
	"insertEdge", "unite", "GraphException", "what", "FatalGraphException", "vertexNameCheck",
	"splitCommand", "gcalcLoop", "main", "intersect", "diff", "cross", "complement", "quit",
	"reset", "who", "print", "delete", "deleteGraph", "executeCommand", "checkParenthesesBalance",
	"checkGraphParentheses", "checkCommand"}; //TODO : add all functions names at the end

const std::set<std::string> special_chars = {"=", "{", "}", ",", "|", "<", ">", "(", ")", "!", "+", "^", "-", "*"};

bool gcalc::GraphHelper::vertexNameCheck(std::string vertex_name) {
	if (vertex_name.empty()) {
		throw gcalc::FatalGraphException("Fatal error- empty vertex name.");
	}
	if (invalid_names.find(vertex_name) != invalid_names.end()) // function name
	{
		throw gcalc::GraphException("Bad vertex name");
	}
	std::stack<char> pranthesis_stack;
	for(char ch : vertex_name)
	{
		if (!isalnum(ch) && ch != '[' && ch != ']' && ch != ';') {
			throw GraphException("Bad vertex name");
		}
		else
		{
			if (ch == '[') {
				pranthesis_stack.push(ch);
				continue;
			}
			if (ch == ']') {
				if (pranthesis_stack.empty()) {
					throw GraphException("Bad vertex name");
				}
				pranthesis_stack.pop();
				continue;
			}
			if (ch == ';') {
				if (pranthesis_stack.empty())
				{
					throw GraphException("Bad vertex name");
				}
			}
		}
	}
	if (!pranthesis_stack.empty()) {
		throw GraphException("Bad vertex name");
	}
	return true;
}

size_t gcalc::GraphHelper::findNextTokenPos(std::string command) {
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

void gcalc::GraphHelper::clearWhiteSpaces(std::string& command)
{
	clearChar(command, ' ');
	clearChar(command, '\t');
	clearChar(command, '\n');
	clearChar(command, '\v');
	clearChar(command, '\f');
	clearChar(command, '\r');
}

void gcalc::GraphHelper::clearChar(std::string& command, char ch)
{
	size_t left = command.find_first_not_of(ch);
	size_t right = command.find_last_not_of(ch);
	command.erase(right + 1);
	command.erase(0, left);
}

std::vector<std::string> gcalc::GraphHelper::splitCommand(const std::string command)
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

bool gcalc::GraphHelper::checkNoDuplicateCommands(std::vector<std::string> command)
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
		throw gcalc::GraphException("Invalid syntax, only one command per line allowed");
	}

	if (num_of_print > 1 || num_of_delete > 1 || num_of_equal > 1)
	{
		throw gcalc::GraphException("Invalid syntax, only one command per line allowed");
	}

	if ((num_of_print == 1 && (num_of_delete > 0 || num_of_equal > 0)) ||
		(num_of_delete == 1 && (num_of_print > 0 || num_of_equal > 0)) ||
		(num_of_equal == 1 && (num_of_delete > 0 || num_of_print > 0)))
	{
		throw gcalc::GraphException("Invalid syntax, only one command per line allowed");

	}

	return true;
}

bool gcalc::GraphHelper::checkGraphSyntax(std::vector<std::string> command)
{
	if (command.size() < 2)
	{
		throw gcalc::GraphException("Invalid graph syntax, graph definition is too short");
	}
	if (command[0].compare("{") != 0 || command[command.size() - 1].compare("}") != 0)
	{
		throw gcalc::GraphException("Invalid graph syntax, graph definition missing parentheses");
	}
	if (command.size() == 2) // Empty graph
	{
		return true;
	}
	if (std::count(command.begin(), command.end(), "|") > 1)
	{
		throw gcalc::GraphException("Invalid graph syntax, max 1 pipe allowed");
	}
	if (std::count(command.begin(), command.end(), "=") != 0)
	{
		throw gcalc::GraphException("Invalid graph syntax, no equal sign allowed inside definition");
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
				throw gcalc::GraphException("Invalid graph syntax");
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
					throw gcalc::GraphException("Invalid graph syntax");
				}
			}

			if (alt_sign == true)
			{
				switch (sign_type)
				{
				case 0:
					if ((*edge_side_iter).compare("<") != 0) // Should be a sign but it is not, or it is not allowed sign
					{
						throw gcalc::GraphException("Invalid graph syntax");
					}
					sign_type = 1;
					alt_sign = false;
					inside_edge = true;
					break;
				case 1:
					if ((*edge_side_iter).compare(",") != 0) // Should be a sign but it is not, or it is not allowed sign
					{
						throw gcalc::GraphException("Invalid graph syntax");
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
						throw gcalc::GraphException("Invalid graph syntax");
					}
					sign_type = 1;
					alt_sign = true;
					inside_edge = false;
					break;
				default:
					throw gcalc::FatalGraphException("Fatal error while checking graph syntax");
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

std::shared_ptr<gcalc::Graph> gcalc::GraphHelper::commandToGraph(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> split_command)
{
	gcalc::Graph result_graph;

	std::vector<std::string> command = split_command;

	if (command.size() == 0)
	{
		throw gcalc::GraphException("Invalid syntax, empty command is not allowed");
	}
	// TODO: test that, as commandOper is doing the complemention.
	/*
	if (command[0].compare("!") == 0)
	{
		command.erase(command.begin());
		return std::shared_ptr<gcalc::Graph>(new gcalc::Graph(gcalc::complement(*(commandToGraph(symbol_map, command)))));
	}*/

	if (command.size() == 1) // It is a variable name
	{
		if (symbol_map.find(command[0]) == symbol_map.end())
		{
			throw gcalc::GraphException("Undefined variable");
		}
		else
		{	
			return symbol_map.at(command[0]);
		}
	}

	if (command[0].compare("{") != 0 || command[command.size() - 1].compare("}") != 0)
	{
		throw gcalc::GraphException("Invalid syntax");
	}

	if (checkGraphSyntax(command))
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
							throw gcalc::GraphException("Invalid syntax");
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
						throw gcalc::GraphException("Invalid syntax");
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

	return std::shared_ptr<gcalc::Graph>(new Graph(result_graph));
}

bool gcalc::GraphHelper::checkGraphName(std::string graph_name)
{
	if (graph_name.empty())
	{
		throw gcalc::GraphException("Invalid graph name");
	}
	if (!isalpha(graph_name[0]))
	{
		throw gcalc::GraphException("Invalid graph name");
	}
	for (auto ch : graph_name)
	{
		if (!isalnum(ch))
		{
			throw gcalc::GraphException("Invalid graph name");
		}
	}
	if (invalid_names.find(graph_name) != invalid_names.end()) // function name
	{
		throw gcalc::GraphException("Invalid graph name");
	}

	// TODO: add check if it is function name

	return true;
}

std::shared_ptr<gcalc::Graph> gcalc::GraphHelper::evaluateBinaryOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> left_graph, std::vector<std::string> right_graph, std::string oper, std::string real_command)
{
	if (!isBinaryOper(oper))
	{
		throw gcalc::GraphException("Invalid syntax, Unknown operation");
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
		throw gcalc::GraphException("Invalid syntax, binary operation must have 2 args");
	}
	
	if (checkGraphParentheses(l_graph) && checkGraphParentheses(r_graph))
	{

		gcalc::Graph l_g = (*(commandOperation(symbol_map, left_graph, real_command)));
		gcalc::Graph r_g = (*(commandOperation(symbol_map, right_graph, real_command)));

		return evaluateBinaryOperation(symbol_map, std::shared_ptr<gcalc::Graph>(new Graph(l_g)), std::shared_ptr<gcalc::Graph>(new Graph(r_g)), oper);
	}
	else
	{
		throw gcalc::GraphException("Invalid graph syntax");
	}
}

std::shared_ptr<gcalc::Graph> gcalc::GraphHelper::evaluateBinaryOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::shared_ptr<gcalc::Graph> left_graph, std::shared_ptr<gcalc::Graph> right_graph, std::string oper)
{
	gcalc::Graph result_graph;

	switch (oper[0])
	{
	case '+':
		result_graph = gcalc::unite(*left_graph, *right_graph);
		break;
	case '-':
		result_graph = gcalc::diff(*left_graph, *right_graph);
		break;
	case '^':
		result_graph = gcalc::intersect(*left_graph, *right_graph);
		break;
	case '*':
		result_graph = gcalc::cross(*left_graph, *right_graph);
		break;
	default:
		throw gcalc::FatalGraphException("Fatal error while evaluating operation");
		break;
	}

	return std::shared_ptr<gcalc::Graph>(new Graph(result_graph));
}

std::shared_ptr<gcalc::Graph> gcalc::GraphHelper::evaluateBinaryOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> left_graph, std::shared_ptr<gcalc::Graph> right_graph, std::string oper)
{
	if (!isBinaryOper(oper))
	{
		throw gcalc::GraphException("Invalid syntax, Unknown operation");
	}

	std::string l_graph;
	for (auto word : left_graph)
	{
		l_graph.append(word);
	}
	
	if (l_graph.empty())
	{
		throw gcalc::GraphException("Invalid syntax, binary operation must have 2 args");
	}

	if (checkGraphParentheses(l_graph))
	{
		gcalc::Graph l_g = (*(commandToGraph(symbol_map, left_graph)));

		return evaluateBinaryOperation(symbol_map, std::shared_ptr<gcalc::Graph>(new Graph(l_g)), right_graph, oper);
	}
	else
	{
		throw gcalc::GraphException("Invalid graph syntax");
	}
}

std::shared_ptr<gcalc::Graph> gcalc::GraphHelper::evaluateBinaryOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::shared_ptr<gcalc::Graph> left_graph, std::vector<std::string> right_graph, std::string oper)
{
	if (!isBinaryOper(oper))
	{
		throw gcalc::GraphException("Invalid syntax, Unknown operation");
	}

	std::string r_graph;
	for (auto word : right_graph)
	{
		r_graph.append(word);
	}

	if (r_graph.empty())
	{
		throw gcalc::GraphException("Invalid syntax, binary operation must have 2 args");
	}

	if (checkGraphParentheses(r_graph))
	{
		gcalc::Graph r_g = (*(commandToGraph(symbol_map, right_graph)));

		return evaluateBinaryOperation(symbol_map, left_graph, std::shared_ptr<gcalc::Graph>(new Graph(r_g)), oper);
	}
	else
	{
		throw gcalc::GraphException("Invalid graph syntax");
	}
}

bool gcalc::GraphHelper::isBinaryOper(std::string oper)
{
	if (oper.size() != 1)
		return false;
	if (oper.compare("+") == 0 || oper.compare("-") == 0 || oper.compare("^") == 0 || oper.compare("*") == 0)
	{
		return true;
	}
	return false;
}

bool gcalc::GraphHelper::isOpeningSign(std::string oper)
{
	return oper.compare("(") == 0;
}

bool gcalc::GraphHelper::isClosingSign(std::string oper)
{
	return oper.compare(")") == 0;
}

std::shared_ptr<gcalc::Graph> gcalc::GraphHelper::commandOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> command, std::string real_command)
{
	if (command.empty())
	{
		throw gcalc::GraphException("Empty command");
	}

	if (command[0].compare("(") == 0 && command[command.size() - 1].compare(")") == 0) // TODO: NEW TEST
	{
		command.pop_back();
		command.erase(command.begin());
		return gcalc::GraphHelper::commandOperation(symbol_map, command, real_command);
	}

	std::stack<std::string> brackets_stack = {};
	
	for (auto iter = command.rbegin(); iter != command.rend(); iter++)
	{
/*
		if ((*iter).compare("load") == 0)
		{

		}
*/

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
				return gcalc::GraphHelper::evaluateBinaryOperation(symbol_map, left_v, right_v, op, real_command); //TODO: check if slice went well
			}
		}


	}

	if (command[0].compare("!") == 0) // TODO check it out
	{
		command.erase(command.begin());
		//return std::shared_ptr<gcalc::Graph>(new gcalc::Graph(gcalc::complement(*(commandToGraph(symbol_map, command)))));
		return std::shared_ptr<gcalc::Graph>(new gcalc::Graph(gcalc::complement(*(commandOperation(symbol_map, command, real_command)))));
	}

	if (command[0].compare("{") == 0 && command[command.size() - 1].compare("}") == 0)
	{
		return gcalc::GraphHelper::commandToGraph(symbol_map, command);
	}

	if (symbol_map.find(command[0]) == symbol_map.end())
	{
		if (command[0].compare("load") == 0)
		{
			if (command.size() != 4)
			{
				throw GraphException("Invalid load command");
			}
			return loadGraph(symbol_map, command, real_command);
		}
		throw GraphException("Undefined variable");
	}

	return symbol_map.at(command[0]);
}

std::shared_ptr<gcalc::Graph> gcalc::GraphHelper::loadGraph(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> command, std::string real_command)
{
	auto file_path = command[2];

	if (command[1].compare("(") != 0)
	{
		throw gcalc::GraphException("Invalid syntax, missing starting parentheses on load command");
	}
	if (command[1].compare("(") == 0 && command[command.size() - 1].compare(")") != 0)
	{
		throw gcalc::GraphException("Invalid syntax, missing ending parentheses on load command");
	}
	std::vector<std::string> name_check = { file_path };
	gcalc::Graph temp_graph;
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
					size_t vertex_name_len;
					fd.read((char *)&vertex_name_len, sizeof(int));
					char* temp = new char[vertex_name_len + 1];
					fd.read(temp, vertex_name_len);
					temp[vertex_name_len] = '\0';
					std::string vertex_name(temp);
					delete[] temp; // Check if memory leaks
					temp_graph.insertVertex(vertex_name);
				}

				for (size_t i = 0; i < num_of_edges; i++)
				{
					size_t src_vertex_name_len;
					fd.read((char*)&src_vertex_name_len, sizeof(int));
					char* temp = new char[src_vertex_name_len + 1];
					fd.read(temp, src_vertex_name_len);
					temp[src_vertex_name_len] = '\0';

					size_t dest_vertex_name_len;
					fd.read((char*)&dest_vertex_name_len, sizeof(int));
					char* temp_b = new char[dest_vertex_name_len + 1];
					fd.read(temp_b, dest_vertex_name_len);
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
				throw gcalc::GraphException("Unable to open the file: " + file_path);
			}
		}
		catch (std::bad_alloc& e)
		{
			throw gcalc::FatalGraphException("Fatal error- out of memory");
		}
		catch (const std::exception&)
		{
			throw gcalc::GraphException("Error occurred while loading the graph from the file: " + file_path);
		}
	}

	return std::shared_ptr<gcalc::Graph>(new Graph(temp_graph));
}

bool gcalc::GraphHelper::checkGraphParentheses(std::string normal_command)
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
				throw gcalc::GraphException("Invalid syntax");
			}
			pre_stack.pop();
		}

		if (pre_stack.size() > 1)
		{
			throw gcalc::GraphException("Invalid syntax");
		}
	}
	if (!pre_stack.empty())
	{
		throw gcalc::GraphException("Invalid syntax");
	}

	return true;
}

bool gcalc::GraphHelper::checkFileName(std::vector<std::string> filename)
{
	if (filename.empty())
	{
		throw gcalc::GraphException("Invalid file name- empty file name is not allowed");
	}

	std::set<std::string> disallowed_signs = { ",", "{", "}", "[", "]", "(", ")" , "\r", "\f", "\v", "\n", "\t"};

	for (auto word : filename)
	{
		if (disallowed_signs.find(word) != disallowed_signs.end())
		{
			throw gcalc::GraphException("Invalid file name- brackets and commas are disallowed");
		}
	}

	return true;
}

bool gcalc::GraphHelper::checkParenthesesBalance(std::string normal_command)
{
	if (checkGraphParentheses(normal_command))
	{
		std::stack<char> pre_stack = {};

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
					throw gcalc::GraphException("Invalid syntax");
				}
				else
				{
					pre_stack.pop();
				}
				break;
			case ')':
				if (pre_stack.top() == '[' || pre_stack.top() == '{' || pre_stack.top() == '<')
				{
					throw gcalc::GraphException("Invalid syntax");
				}
				else
				{
					pre_stack.pop();
				}
				break;
			case '}':
				if (pre_stack.top() == '[' || pre_stack.top() == '(' || pre_stack.top() == '<')
				{
					throw gcalc::GraphException("Invalid syntax");
				}
				else
				{
					pre_stack.pop();
				}
				break;
			case '>':
				if (pre_stack.top() == '[' || pre_stack.top() == '(' || pre_stack.top() == '{')
				{
					throw gcalc::GraphException("Invalid syntax");
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
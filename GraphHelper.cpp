#include "GraphHelper.h"
#include <stack>
#include <set>
#include <cctype>
#include <algorithm>

const std::set<std::string> invalid_names = {"Graph", "operator", "insertVertex",
	"insertEdge", "unite", "GraphException", "what", "FatalGraphException", "vertexNameCheck",
	"splitCommand", "gcalcLoop", "main", "intersect", "diff", "cross", "complement", "quit",
	"reset", "who", "print", "delete", "deleteGraph", "executeCommand", "checkParenthesesBalance",
	"checkGraphParentheses", "checkCommand"};

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
	command.erase(0, left);
	command.erase(right + 1);
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
	/*int num_of_print = 0;
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

	if (num_of_print > 0 || num_of_delete > 0 || num_of_equal > 0)
	{
		throw gcalc::GraphException("Invalid syntax, only one command per line allowed");
	}

	return true;*/
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
					sign_type = (sign_type + 1) % 3;
					alt_sign = false;
					break;
				case 1:
					if ((*edge_side_iter).compare(",") != 0) // Should be a sign but it is not, or it is not allowed sign
					{
						throw gcalc::GraphException("Invalid graph syntax");
					}
					sign_type = (sign_type + 1) % 3;
					alt_sign = false;
					break;
				case 2:
					if ((*edge_side_iter).compare(">") != 0) // Should be a sign but it is not, or it is not allowed sign
					{
						throw gcalc::GraphException("Invalid graph syntax");
					}
					sign_type = (sign_type + 1) % 3;
					alt_sign = false;
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

std::shared_ptr<gcalc::Graph> gcalc::GraphHelper::commandToGraph(std::vector<std::string> command)
{
	gcalc::Graph result_graph;

	if (command.size() < 2) // Just for safety, check it is the right format again
	{
		throw gcalc::GraphException("Invalid syntax");
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
	return true;
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

bool gcalc::GraphHelper::checkParenthesesBalance(std::string normal_command)
{
	if (checkGraphParentheses(normal_command))
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
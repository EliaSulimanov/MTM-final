#include "GraphHelper.h"
#include <stack>
#include <set>
#include <algorithm>

const std::set<std::string> invalid_names = {"Graph", "operator", "insertVertex",
	"insertEdge", "unite", "GraphException", "what", "FatalGraphException", "vertexNameCheck",
	"splitCommand", "gcalcLoop", "main", "intersect", "diff", "cross", "complement", "quit",
	"reset", "who", "print", "delete", "deleteGraph"};

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

std::vector<std::string> gcalc::GraphHelper::splitCommand(std::string command)
{
	std::istringstream buf(command);
	std::istream_iterator<std::string> beg(buf), end;
	std::vector<std::string> split_command(beg, end);

	return split_command;
}

bool gcalc::GraphHelper::checkCommand(std::vector<std::string> split_command)
{
	std::string normal_command;
	normal_command.append(split_command.begin(), split_command.end());

	if (std::count(normal_command.begin(), normal_command.end(), '=') > 1)
	{
		throw gcalc::GraphException("Invalid syntax");
	}

	if (checkParenthesesBalance(normal_command))
	{
		//TODO
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


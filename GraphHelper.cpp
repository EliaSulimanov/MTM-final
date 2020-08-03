#include "GraphHelper.h"
#include <stack>

bool gcalc::GraphHelper::vertexNameCheck(std::string vertex_name) {
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

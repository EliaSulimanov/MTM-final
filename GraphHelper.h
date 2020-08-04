#ifndef GRAPH_HELPER_H
#define GRAPH_HELPER_H

#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

#include "Graph.h"
#include "GraphException.h"

namespace gcalc {
	class GraphHelper
	{
	private:
		static bool checkGraphParentheses(std::string normal_command);
		static size_t findNextTokenPos(std::string command);
		static void clearWhiteSpaces(std::string& command);
		static void clearChar(std::string& command, char ch);
	public:
		static bool checkParenthesesBalance(std::string normal_command);
		static bool vertexNameCheck(std::string vertex_name);
		static std::vector<std::string> splitCommand(const std::string command);
		static bool checkNoDuplicateCommands(std::vector<std::string> command);
		static bool checkSpecialChars(std::vector<std::string> command);
	};
}

#endif

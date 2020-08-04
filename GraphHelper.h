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
		static bool checkParenthesesBalance(std::string normal_command);
	public:
		static bool vertexNameCheck(std::string vertex_name);
		static std::vector<std::string> splitCommand(std::string command);
		static bool checkCommand(std::vector<std::string> split_command);
	};
}

#endif

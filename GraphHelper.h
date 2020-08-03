#ifndef GRAPH_HELPER_H
#define GRAPH_HELPER_H

#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

#include "GraphException.h"

namespace gcalc {
	class GraphHelper
	{
	public:
		static bool vertexNameCheck(std::string vertex_name);
		static std::vector<std::string> splitCommand(std::string command);
	};
}

#endif

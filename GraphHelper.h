#ifndef GRAPH_HELPER_H
#define GRAPH_HELPER_H

#include <string>
#include <cctype>
#include <iostream>
#include "GraphException.h"

namespace gcalc {
	class GraphHelper
	{
	public:
		bool static vertexNameCheck(std::string vertex_name);
	};
}

#endif

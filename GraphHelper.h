#ifndef GRAPH_HELPER_H
#define GRAPH_HELPER_H

#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <memory>
#include <map>

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
		static bool isBinaryOper(std::string oper);

	public:
		static bool checkParenthesesBalance(std::string normal_command);
		static bool vertexNameCheck(std::string vertex_name);
		static std::vector<std::string> splitCommand(const std::string command);
		static bool checkNoDuplicateCommands(std::vector<std::string> command);
		static bool checkGraphSyntax(std::vector<std::string> command);
		static std::shared_ptr<gcalc::Graph> commandToGraph(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> command);
		static bool checkGraphName(std::string graph_name);
		static std::shared_ptr<gcalc::Graph> evaluateBinaryOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> left_graph, std::vector<std::string> right_graph, std::string oper);
		static std::shared_ptr<gcalc::Graph> evaluateBinaryOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::shared_ptr<gcalc::Graph> left_graph, std::shared_ptr<gcalc::Graph> right_graph, std::string oper);
		static std::shared_ptr<gcalc::Graph> evaluateBinaryOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> left_graph, std::shared_ptr<gcalc::Graph> right_graph, std::string oper);
		
		static std::shared_ptr<gcalc::Graph> commandOperation(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map, std::vector<std::string> command);
	};
}

#endif

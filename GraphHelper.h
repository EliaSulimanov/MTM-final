#ifndef GRAPH_HELPER_H
#define GRAPH_HELPER_H

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <memory>
#include <map>

#include "graph.h"
#include "graphException.h"

class graphHelper
{
private:
	static bool checkgraphParentheses(std::string normal_command);
	static size_t findNextTokenPos(std::string command);

	static void clearChar(std::string& command, char ch);
	static bool isBinaryOper(std::string oper);
	static bool isOpeningSign(std::string oper);
	static bool isClosingSign(std::string oper);

public:
	static bool checkFileName(std::vector<std::string> filename);
	static void clearWhiteSpaces(std::string& command);
	static bool checkParenthesesBalance(std::string normal_command);
	static bool vertexNameCheck(std::string vertex_name);
	static std::vector<std::string> splitCommand(const std::string command);
	static bool checkNoDuplicateCommands(std::vector<std::string> command);
	static bool checkgraphSyntax(std::vector<std::string> command);
	static std::shared_ptr<graph> commandTograph(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> split_command);
	static bool checkgraphName(std::string graph_name);
	static std::shared_ptr<graph> evaluateBinaryOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> left_graph, std::vector<std::string> right_graph, std::string oper, std::string real_command);
	static std::shared_ptr<graph> evaluateBinaryOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::shared_ptr<graph> left_graph, std::shared_ptr<graph> right_graph, std::string oper);
	static std::shared_ptr<graph> evaluateBinaryOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> left_graph, std::shared_ptr<graph> right_graph, std::string oper);
	static std::shared_ptr<graph> evaluateBinaryOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::shared_ptr<graph> left_graph, std::vector<std::string> right_graph, std::string oper);

	static std::shared_ptr<graph> commandOperation(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> command, std::string real_command);
	static std::shared_ptr<graph> loadgraph(std::map<std::string, std::shared_ptr<graph>>& symbol_map, std::vector<std::string> command, std::string real_command);
};

#endif

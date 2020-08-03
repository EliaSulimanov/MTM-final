#include "GraphHelper.h"
#include "Graph.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

void gcalcLoop(std::map<std::string, std::shared_ptr<gcalc::Graph>>& symbol_map) {
	while (true)
	{
		std::string command;

		std::cout << "Gcalc> ";
		std::getline(std::cin, command);
		std::vector<std::string> split_command = gcalc::GraphHelper::splitCommand(command);


	}
}

void vertexNameTest() {
	try {
		std::cout << "Hello" << std::endl;
		gcalc::GraphHelper::vertexNameCheck("Hello");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "He llo" << std::endl;
		gcalc::GraphHelper::vertexNameCheck("He llo");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "#" << std::endl;
		gcalc::GraphHelper::vertexNameCheck("#");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << " " << std::endl;
		gcalc::GraphHelper::vertexNameCheck(" ");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "" << std::endl;
		gcalc::GraphHelper::vertexNameCheck("");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "[x1[x3]]" << std::endl;
		gcalc::GraphHelper::vertexNameCheck("[x1[x3]]");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "[;;;]" << std::endl;
		gcalc::GraphHelper::vertexNameCheck("[;;;]");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	try {
		std::cout << "x1[];y" << std::endl;
		gcalc::GraphHelper::vertexNameCheck("x1[];y");
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}

void graphTest() {
	gcalc::Graph G1("G1");
	gcalc::Graph G2("G2");
}

int main() {
	//map graphs name and pointer to the graph
	//std::map<std::string, std::shared_ptr<gcalc::Graph>> symbol_map;
	//gcalcLoop(symbol_map);
}
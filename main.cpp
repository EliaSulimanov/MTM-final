#include "GraphHelper.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

int main() {
	while (true) 
	{
		std::cout << "Gcalc> ";
		
		std::string command;
		std::cin >> command;

		std::istringstream buf(command);
		std::istream_iterator<std::string> beg(buf), end;

		std::vector<std::string> split_command(beg, end);

		for (auto& s : split_command)
			std::cout << '"' << s << '"' << '\n';

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
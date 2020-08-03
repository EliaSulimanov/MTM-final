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

// TODO: delete.
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

// TODO: delete.
void graphTest() {
	try
	{
		gcalc::Graph G1;
		gcalc::Graph G2;
		gcalc::Graph G3;

		G1.insertVertex("Hello");
		G2.insertVertex("Hello");

		G3 = gcalc::unite(G1, G2);
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;
		gcalc::Graph G2;
		gcalc::Graph G3;

		G1.insertVertex("LALALA");
		G1.insertVertex("hop");
		G1.insertVertex("123[]cc[[s]]");
		G1.insertVertex("123");
		G1.insertEdge("LALALA", "hop");
		G1.insertEdge("LALALA", "123");
		G1.insertEdge("123", "LALALA");
		G1.insertEdge("123[]cc[[s]]", "123");

		G2.insertVertex("2LALALA");
		G2.insertVertex("2hop");
		G2.insertVertex("2123[]cc[[s]]");
		G2.insertVertex("123");
		G2.insertEdge("2LALALA", "2hop");
		G2.insertEdge("2LALALA", "123");
		G2.insertEdge("123", "2LALALA");
		G2.insertEdge("2123[]cc[[s]]", "123");

		G3 = gcalc::unite(G1, G2);
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;

		G1.insertVertex("Hel lo");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;

		G1.insertVertex("Hello");
		G1.insertEdge("Hello", "Hello");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;

		G1.insertVertex("Hello");
		G1.insertEdge("Hello", "H2ello");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;

		G1.insertVertex("Hello");
		G1.insertEdge("Hello", "H ello");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;

		G1.insertVertex("Hello");
		G1.insertEdge("He llo", "H ello");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;

		G1.insertVertex("Hello");
		G1.insertEdge("", "H ello");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;

		G1.insertVertex("Hello");
		G1.insertEdge("", "");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	try
	{
		gcalc::Graph G1;

		G1.insertVertex("Hello");
		G1.insertEdge("$", "#");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;
		gcalc::Graph G2;
		gcalc::Graph G3;

		G1.insertVertex("LALALA");
		G1.insertVertex("hop");
		G1.insertEdge("hop", "LALALA");

		G2.insertVertex("LALALA");
		G2.insertVertex("hop");
		G2.insertEdge("LALALA", "hop");

		G3 = gcalc::unite(G1, G2);
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	try
	{
		gcalc::Graph G1;

		G1.insertVertex("gcalcLoop");
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "Done!";
}

void crossTest()
{
	try
	{
		gcalc::Graph G1;
		G1.insertVertex("a");
		G1.insertVertex("b");
		gcalc::Graph G2;
		G2.insertVertex("C");
		G2.insertVertex("D");

		gcalc::Graph G3 = gcalc::cross(G1, G2);
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

int main() {
	//map graphs name and pointer to the graph
	/*std::map<std::string, std::shared_ptr<gcalc::Graph>> symbol_map;
	gcalcLoop(symbol_map);*/

	crossTest();
}
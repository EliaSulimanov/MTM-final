#ifndef GRAPH_EXCEPTION_H
#define GRAPH_EXCEPTION_H

#include <iostream>
#include <exception>

namespace gcalc 
{
	class GraphException : public std::exception
	{
	private:
		std::string message;
	public:
		GraphException(std::string message) noexcept : message(message) {}
		virtual const char* what() const noexcept override
		{
			return message.c_str();
		}
	};

	class FatalGraphException : public std::exception
	{
	private:
		std::string message;
	public:
		FatalGraphException(std::string message) noexcept : message(message) {}
		virtual const char* what() const noexcept override
		{
			return message.c_str();
		}
	};
}

#endif
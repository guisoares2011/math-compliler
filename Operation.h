#pragma once
#include <string>
class Operation
{
	public:
		int factor = 0;
		virtual double calc(void) = 0;
		virtual ~Operation(void) {};
		virtual std::string debug(void) = 0;
		virtual int getFactor() = 0;
};

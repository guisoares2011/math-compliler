#pragma once

#include "Operator.h"
#include "Operand.h"
#include <string>

#define OP_TYPE_UNKNOWS 1
#define OP_TYPE_DIGITS 2

#define RIGHT_POSITION 1
#define LEFT_POSITION 2

struct DataStruct {
	std::string digits;
	std::string unkows;
	int type = OP_TYPE_DIGITS;
};

class Tokenizer {
	private:
		OperadorBin* compareFactorOperator(OperadorBin* leftOperador, OperadorBin* rightOperador, Operand *op);
	public:
		Tokenizer(void) {}
		virtual ~Tokenizer(void) {};
		Result* parse(std::string s);
};

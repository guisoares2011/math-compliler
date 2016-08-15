#pragma once

#include "Operator.h"
#include "Operand.h"
#include <string>
#include <vector>

#define OPERAND_STATE 1
#define OPERATOR_STATE 2
#define FUNCTION_STATE 3
#define VECTOR_STATE 4

#define OP_TYPE_UNKNOWS 1
#define OP_TYPE_DIGITS 2

#define RIGHT_POSITION 1
#define LEFT_POSITION 2

struct DataStruct {
	std::string digits;
	std::string unknows;
	std::string modifiers; // + -
	int type = OP_TYPE_DIGITS;
};

class Tokenizer {
	private:
		OperadorBin* compareFactorOperator(OperadorBin* leftOperador, OperadorBin* rightOperador, Operand *op);
	public:
		Tokenizer(void) {}
		virtual ~Tokenizer(void) {};
		Result * parse(std::string s);
		OperadorBin* makeOperator(OperadorBin* currentOperation, Operand* op, char operandType);
};

#include "Tokenizer.h"
#include <cstring>
#include <iostream>
#include <locale>
#include <stdexcept>

using namespace std;

Operand* dataToOperand(DataStruct *data) {
	double d = atof(data->digits.c_str());
	data = new DataStruct;
	return new Operand(d);
};

OperadorBin* Tokenizer::compareFactorOperator(OperadorBin* leftOperador, OperadorBin* rightOperador, Operand *op) {
	
	if (rightOperador->getFactor() > leftOperador->getFactor()) {
		rightOperador->setLeft(op);
		leftOperador->setRight(rightOperador);
		//rightOperador->setLeft(leftOperador);
		return leftOperador;
	} else {
		leftOperador->setRight(op);
		rightOperador->setLeft(leftOperador);
		return rightOperador;
	}
};

OperadorBin* Tokenizer::makeOperator(OperadorBin* currentOperation, Operand* op, char operandType) {
	return currentOperation;
};

Result * Tokenizer::parse(std::string s) {

	std::string::size_type i = 0, length = s.size();
	std::string C_OPERATORS_SYMBOLS = "+-^*/ ";
	int state = OPERAND_STATE;
	std::locale loc;
	DataStruct* _operand = new DataStruct;

	OperadorBin* currentOperation = NULL;
	OperadorBin* tmpOperation = NULL;
	int factor = 0;

	do {
		if (state == OPERAND_STATE) {

			//Check next character
			if ((i + 1 <= length)) {
				//Check if the next char is a operator or space
				if (C_OPERATORS_SYMBOLS.find(s[i]) != string::npos && 
					(_operand->unknows.size() > 0 || _operand->digits.size() > 0)) {
					state = OPERATOR_STATE;
				}
			}

			//Digits
			if (std::isdigit(s[i], loc))
			{
				if (_operand->type == OP_TYPE_DIGITS) {
					_operand->digits += s[i];
				}
				else {
					//logic to 2a2b (for example)
				}
			}
			//Chars
			else if (std::isalpha(s[i], loc))
			{
				_operand->unknows += s[i];
				_operand->type = OP_TYPE_UNKNOWS;
			}
		}
		else if (state == OPERATOR_STATE) {
			if (s[i] == ' ') {
				i++;
				continue;
			}
			switch (s[i]) {
				case '+':
					tmpOperation = new Soma(factor);
					break;

				case '-':
					tmpOperation = new Subtracao(factor);
					break;

				case '/':
					tmpOperation = new Divisao(factor);
					break;

				case '*':
					tmpOperation = new Multiplicacao(factor);
					break;

				default:										
					throw std::domain_error("Invalid symbol!");
					break;
			}
			state = OPERAND_STATE;
			//First Operation
			if (currentOperation == NULL) {
				currentOperation = tmpOperation;
				currentOperation->setLeft(dataToOperand(_operand));
			}
			else {
				this->compareFactorOperator(currentOperation, tmpOperation, dataToOperand(_operand));
				currentOperation = tmpOperation;
			}
			_operand = new DataStruct;
		}
		i++;
	} while (i < length);
	

	return {};
}

/*
Result* Tokenizer::parse(std::string s)
{

	char q;
	int factor = 0;
	int currentPosition = LEFT_POSITION;
	Result* r = new Result();
	std::locale loc;
	string tmp = string();
	OperadorBin* currentOperation = NULL;
	OperadorBin* tmpOperation = NULL;
	

	for (std::string::size_type i = 0; i < s.size(); ++i) {
		q = s[i];
		if (std::isdigit(q, loc)) 
		{
			if (_tmp->type == OP_TYPE_DIGITS) {
				_tmp->digits += q;
			} else {
				//Make operation like that a new node
				//2a2b
				// DataStruct(2, a) * DataStruct(2, b)
				if (currentOperation == NULL) {
					currentOperation = new Multiplicacao(factor);
					currentOperation->setLeft(dataToOperand(_tmp));
				}
				else {
					tmpOperation = new Multiplicacao(factor);
					tmpOperation->setLeft(dataToOperand(_tmp));
					currentOperation->setRight(tmpOperation);
					currentOperation = tmpOperation;
				}
				_tmp = new DataStruct;
				_tmp->digits += q;
			}	
		}
		else if (std::isalpha(q, loc))
		{
			_tmp->unkows += q;
			_tmp->type = OP_TYPE_UNKNOWS;
		}
		else if (std::ispunct(q, loc))
		{
			if (q == '(')	   { factor += 10; }
			else if (q == ')') { factor -= 10;}
			else if (q == '.') { tmp += q; }
			else //Operators
			{
				if(q == '+') { tmpOperation = new Soma(factor); }
				else if (q == '-') { tmpOperation = new Subtracao(factor); }
				else if (q == '*') { tmpOperation = new Multiplicacao(factor); }
				else if (q == '/') { tmpOperation = new Divisao(factor); }
				else {
					//Unexpected symbol
					throw std::domain_error("Invalid symbol!");
				}

				if (currentOperation == NULL) {
					currentOperation = tmpOperation;
					currentOperation->setLeft(dataToOperand(_tmp));	 
				}
				else 
				{
					currentOperation = this->compareFactorOperator(currentOperation, tmpOperation, dataToOperand(_tmp));
				}
				_tmp = new DataStruct;
			}
		}
	}
	if (currentOperation) {
		if (factor == 0) {
			if (currentOperation->getRight()->getFactor() > 0) {
				((OperadorBin *) currentOperation->getRight())->setRight(dataToOperand(_tmp));
			}
			else {
				currentOperation->setRight(dataToOperand(_tmp));
			}
		}
	}
	r->setRight(currentOperation);
	return r;
}
*/
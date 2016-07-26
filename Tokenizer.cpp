#include "Tokenizer.h"
#include <cstring>
#include <iostream>
#include <locale>
#include <stdexcept>

using namespace std;

Operand* dataToOperand(DataStruct *data) {
	double d = atof(data->digits.c_str());
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
	DataStruct* _tmp = new DataStruct;

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

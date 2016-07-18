#include "Operator.h"
#include "Tokenizer.h"
#include <iostream>

using namespace std;

int Operator::getFactor()
{
	if (this->operatorType == SUM_OPERATOR)
		return SUM_OPERATOR_PREC;
	else if (this->operatorType == MUL_OPERATOR)
		return MUL_OPERATOR_PREC;
	else if (this->operatorType == LES_OPERATOR)
		return LES_OPERATOR_PREC;
	else if (this->operatorType == DIV_OPERATOR)
		return DIV_OPERATOR_PREC;
	return 0;
}

double Operator::resolve(TreeNode* leftOperand, TreeNode * rightOperand)
{	
	double right = rightOperand->getValue();
	double left = leftOperand->getValue();
	if (this->operatorType == SUM_OPERATOR)
		return right + left;
	else if (this->operatorType == MUL_OPERATOR)
		return right * left;
	else if (this->operatorType == LES_OPERATOR)
		return right - left;
	else if (this->operatorType == DIV_OPERATOR)
		return right / left;
	return 0;
}

#pragma once
#ifndef H_OPERATOR
#define H_OPERATOR


#include <string>
using namespace std;

class TreeNode;

class Operator {

private:
	int operatorType;
public:

	Operator(int operatorType) {
		this->operatorType = operatorType;
	};
	int getType() {
		return this->operatorType;
	}
	int getFactor();
	double resolve(TreeNode* leftOperand, TreeNode* rightOperand);
};

#endif
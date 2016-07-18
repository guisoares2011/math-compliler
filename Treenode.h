#pragma once
#ifndef H_TREENODE
#define H_TREENODE

#include "Tokenizer.h"
#include <string>
using namespace std;

class Operator;
/*
* Class Operand
*
* All element of query will be consider a Operand except for Operator
*
* Eg: (10 + 40) * (10 * 10)
* TreeNode (1#)
	\-->
	OperandLeft 10
	Operator + (type 1)
	OperandRight 40

	* TreeNode (2#)
	\-->
	OperandLeft 10
	Operator * (type 4)
	OperandRight 10

	TreeNode(3#)
	\-->
	OperandLeft TreeNode (#1)
	Operator * (type 4)
	OperandRight TreeNode (#2)
*/
class TreeNode {
private:
	int type;
	int factor = NULL;
	int modifier = SUM_OPERATOR;
	string value;
	TreeNode *leftOperand = NULL;
	TreeNode *rightOperand = NULL;
	Operator *_operator = NULL;

public:

	TreeNode(int currentFactor) {
		this->factor = currentFactor;
		this->value = "";
		this->type = TREENODE_TYPE;
	}

	~TreeNode(void);

	int getType() {
		return this->type;
	};
	void setType(int type) {
		this->type = type;
	};
	void appendChar(char ch);
	void setModifier(char ch) {
		if (ch == '-' && this->modifier == LES_OPERATOR) {
			this->modifier = SUM_OPERATOR;
		}
		else if (ch == '-' && this->modifier == SUM_OPERATOR) {
			this->modifier = LES_OPERATOR;
		}
	};

	double getValue();

	string _debug(int level = 0);

	TreeNode* getLeftOperand() {
		return this->leftOperand;
	};

	TreeNode* getRightOperand() {
		return this->rightOperand;
	};

	Operator* getOperator() {
		return this->_operator;
	};
	
	void setFactor(int factor) {
		this->factor = factor;
	}

	int getFactor() {
		return this->factor;
	}

	void setLeftOperand(TreeNode *leftOperand) {
		this->leftOperand = leftOperand;
	}

	void setRightOperand(TreeNode *rightOperand) {
		this->rightOperand = rightOperand;
	}

	void setOperator(Operator *_operator) {
		this->_operator = _operator;
	}
};

#endif // !H_TREENODE

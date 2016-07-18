#include "Treenode.h"

TreeNode::~TreeNode(void)
{
	this->factor = NULL;
	this->type = NULL;
	this->leftOperand = NULL;
	this->rightOperand = NULL;
	this->_operator = NULL;
}

void TreeNode::appendChar(char ch)
{
	this->value += ch;
}


double TreeNode::getValue()
{
	//TODO Implements getValue to return the correct value always
	//diacording with the type
	double value = 0.0;
	switch (this->type) {
	case NUMERIC_TYPE:
		value = atof(this->value.c_str());
		break;
	case TREENODE_TYPE:
		if (this->_operator) {
			value = this->_operator->resolve(this->getLeftOperand(), this->getRightOperand());
		}
		break;
	}
	return value;
}

string __ident(int i) {
	string a = string();
	for (int _i = 0; _i < i; _i++)
		a += "\t";
	return a;
}

string TreeNode::_debug(int level)
{
	//Tr(Lf=10, Op=+, Rg=Tr(Lf=20, Op=*, Rg=20))
	/*
		Debug ::: 
		Tr(
			Lf=Tr(
				Lf=Tr(Lf=2, Op=1, Rg=1), 
				Op=4, 
				Rg=Tr(Lf=2, Op=1, Rg=2)
			), 
			Op=NULL, 
			Rg = NULL
		)
	*/
	if (this->getType() == TREENODE_TYPE) {
		string a = string("Tr(\n");
		a += __ident(level + 1) + "Lf=" + ((this->leftOperand) ? this->leftOperand->_debug(level + 1) : "NULL") + ", \n";
		a += __ident(level + 1) + "Op=" + ((this->_operator) ? std::to_string(this->_operator->getType()) : "NULL") + ", \n";
		a += __ident(level + 1) + "Rg=" + ((this->rightOperand) ? this->rightOperand->_debug(level + 1) : "NULL") + "\n";
		a += __ident(level) + ")";
		return a;
	} else {
		return this->value;
	}
	
}


#include "Operator.h"
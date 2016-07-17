#ifndef H_TOKENIZER
 
#define H_TOKENIZER

#include <string>
using namespace std;
//Chars

//Type of operand
#define NUMERIC_TYPE 1
#define UNKNOWN_TYPE 2 // (eg: 10a, 19ab)
#define TREENODE_TYPE 3
#define PUNCT_TYPE 4
#define SPACE_TYPE 5

// Type of Operators
#define SUM_OPERATOR 1
#define DIV_OPERATOR 2
#define LES_OPERATOR 3
#define MUL_OPERATOR 4

// Operator's factor
// 
// This will be used in BinaryTree to 
// make decisions
//
#define SUM_OPERATOR_PREC 1
#define DIV_OPERATOR_PREC 2
#define LES_OPERATOR_PREC 1
#define MUL_OPERATOR_PREC 2


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
 * 
*/
class Operator {

private:
	int factor;
	int operatorType;
public:

	Operator(int operatorType, int factor) {
		this->operatorType = operatorType;
		this->factor = factor;
	};

	void* resolve(TreeNode *leftOperand, TreeNode *rightOperand) {
		return "";
	}
};


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

	TreeNode() {
		this->factor = 0;
		this->value = "";
		this->type = TREENODE_TYPE;
		//I don't know
	}

	~TreeNode(void) {
		this->factor = NULL;
		this->type = NULL;
		this->leftOperand = NULL;
		this->rightOperand = NULL;
		this->_operator = NULL;
	}

	void setType(int type) {
		this->type = type;
	};

	void appendChar(char ch) {
		this->value += ch;
	};

	void setModifier(char ch) {
		if (ch == '-' && this->modifier == LES_OPERATOR) {
			this->modifier = SUM_OPERATOR;
		}
		else if (ch == '-' && this->modifier == SUM_OPERATOR) {
			this->modifier = LES_OPERATOR;
		}
	};

	void* getValue() {
		//TODO Implements getValue to return the correct value always
		//diacording with the type
		switch (this->type) {
			case NUMERIC_TYPE:
				cout << atof((this->modifier == LES_OPERATOR ? '-' + this->value : this->value).c_str()) << endl;
				break;
			case TREENODE_TYPE:
				if (this->_operator) {
					cout << this->_operator->resolve(this->getLeftOperand(), this->getRightOperand()) << endl;
				}
				break;
		}
		
	};

	TreeNode* getLeftOperand() {
		return this->leftOperand;
	};

	TreeNode* getRightOperand() {
		return this->rightOperand;
	};

	Operator* getOperator() {
		return this->_operator;
	};

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

/* *
* Class Tokenizer
*
* Tokenize the math query
*/
class Tokenizer
{
private:
	TreeNode* token;
public:
	Tokenizer(string query);
	~Tokenizer(void);
	TreeNode* parseExpression(string query);
	TreeNode* getToken() {
		return this->token;
	}
};



#endif // !H_TOKENIZER

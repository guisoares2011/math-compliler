#include "Tokenizer.h"
#include <cstring>
#include <iostream>
#include <locale>
#include <stdexcept>

using namespace std;

Tokenizer::Tokenizer(string query)
{
	this->token = this->parseExpression(query);
}

Tokenizer::~Tokenizer(void)
{
	//this->token = NULL;
}

TreeNode* Tokenizer::parseExpression(string query)
{
	int i = 0;
	int currentFactor = 0;
	int operatorType = 0;
	int lastCharType = NULL;
	char lastChar = NULL;
	
	std::locale loc;
	
	
	TreeNode *mainNode = new TreeNode();
	TreeNode *node = new TreeNode();
	
	TreeNode* currentOperand = new TreeNode();
	currentOperand->setType(NUMERIC_TYPE);

	node->setLeftOperand(currentOperand);
	

	for (std::string::size_type i = 0; i < query.size(); ++i) {
		//cout << query[i] << '\n' <<endl;
		if (query[i] == ' ') 
		{
			//TODO Implements check in case like that
			//10 10 (raise a Exception: Missing a operator between operators)
			lastCharType = NULL;
			continue;
		} 
		else if (std::isalpha(query[i], loc)) //unknows or functions
		{
			//todo make the logic of unknow
			lastCharType = UNKNOWN_TYPE;
			currentOperand->appendChar(query[i]);
			cout << "unknows" << endl;
		}
		else if (std::isdigit(query[i], loc)) //digits
		{
			lastCharType = NUMERIC_TYPE;
			currentOperand->appendChar(query[i]);
			cout << "digit" << endl;
		}
		else if (std::ispunct(query[i], loc)) 
		{
			cout << "punct" << endl;
			
			if (query[i] == '+')
				operatorType = SUM_OPERATOR;
			else if (query[i] == '/')
				operatorType = DIV_OPERATOR;
			else if (query[i] == '-')
				operatorType = LES_OPERATOR;
			else if (query[i] == '*') {
				operatorType = MUL_OPERATOR;
			}
			else {
				//Unexpected symbol
				throw std::domain_error("Invalid symbol!");
			}

			if (node->getLeftOperand() != NULL && 
				lastCharType == PUNCT_TYPE && 
				node->getRightOperand() == NULL) {
				
				//Operator to change the value
				//allows onlu SUM OPERATOR e LES OPERATOR
				if(operatorType != SUM_OPERATOR && operatorType != LES_OPERATOR)
					throw std::domain_error("Invalid operand modifer!");
				else {
					currentOperand->appendChar(query[i]);
				}

			} else if(!node->getOperator()) {
				
				Operator *op = new Operator(operatorType, currentFactor);
				node->setOperator(op);
				currentOperand = new TreeNode();
				currentOperand->setType(NUMERIC_TYPE);
				node->setRightOperand(currentOperand);

			} else if (node->getRightOperand()) {

				if (lastCharType == PUNCT_TYPE) {
					currentOperand->setModifier(query[i]);
				}
				else {
					//todo make a new node three
					//When a+-a-10
					//a <- left operand
					//+ <- operator
					//- <- right operand
					//a <- right operand
					//- <- New tree and operator 
					//10 <- right operator
				}
			}

			lastCharType = PUNCT_TYPE;
		}
		lastChar = query[i];
	}

	if (currentFactor > 0) {

	}
	return node;
}



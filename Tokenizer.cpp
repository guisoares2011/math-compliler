#include "Tokenizer.h"
#include "Operator.h"
#include "Treenode.h"

#include <cstring>
#include <iostream>
#include <locale>
#include <stdexcept>

using namespace std;

Tokenizer::Tokenizer(string query)
{
	this->setToken(this->parseExpression(query));
}

void Tokenizer::setToken(TreeNode *token)
{
	this->token = token;
}

Tokenizer::~Tokenizer(void)
{
	this->token = NULL;
}

TreeNode* Tokenizer::parseExpression(string query)
{
	int i = 0;
	int currentFactor = 0;
	int operatorType = 0;
	int lastCharType = NULL;
	char lastChar = NULL;
	
	std::locale loc;
	
	
	int test = 0;
	TreeNode *node = new TreeNode(currentFactor);
	TreeNode *mainNode = node;
	TreeNode *tmpNode;
	TreeNode* currentOperand = new TreeNode(currentFactor);
	currentOperand->setType(NUMERIC_TYPE);
	node->setLeftOperand(currentOperand);
	

	for (std::string::size_type i = 0; i < query.size(); ++i) {
		//cout << query[i] << '\n' <<endl;
		if (query[i] == ' ') 
		{
			//TODO Implements check in case like that
			//10 10 (raise a Exception: Missing a operator between operators)
			lastCharType = NULL;
			//cout << "empty space" << endl;
			continue;
		} 
		else if (std::isalpha(query[i], loc)) //unknows or functions
		{
			//todo make the logic of unknow
			lastCharType = UNKNOWN_TYPE;
			currentOperand->appendChar(query[i]);
			//cout << "unknows" << query[i] << endl;
		}
		else if (std::isdigit(query[i], loc)) //digits
		{
			lastCharType = NUMERIC_TYPE;
			currentOperand->appendChar(query[i]);
			//cout << "digit" << query[i] << endl;
		}
		else if (std::ispunct(query[i], loc)) 
		{
			//cout << "punct" << query[i]  << endl;
			
			if (query[i] == '+')
				operatorType = SUM_OPERATOR;
			else if (query[i] == '/')
				operatorType = DIV_OPERATOR;
			else if (query[i] == '-')
				operatorType = LES_OPERATOR;
			else if (query[i] == '*') {
				operatorType = MUL_OPERATOR;
			} else if (query[i] == '(') {
				currentFactor += 10;
				lastCharType = PARHL_TYPE;
				continue;
			} else if (query[i] == ')') {
				currentFactor -= 10;
				lastCharType = PARHR_TYPE;

				//Fucking bulshit
				if (currentFactor == 0) {
				
					if (node->getType() == TREENODE_TYPE) {
						mainNode->setRightOperand(node);
						node = mainNode;
						//tmpNode = new TreeNode(currentFactor);
						//tmpNode->setLeftOperand(node);
						//mainNode = tmpNode;
						//node = tmpNode;
					}
				}
				continue;
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
					//cout << "modifier::>>" << endl;
					currentOperand->appendChar(query[i]);
				}

			} else if(!node->getOperator()) {
				

				node->setOperator(new Operator(operatorType));
				currentOperand = new TreeNode(currentFactor);
				currentOperand->setType(NUMERIC_TYPE);
				node->setRightOperand(currentOperand);

			} else if (node->getRightOperand()) {

				if (lastCharType == PUNCT_TYPE) {
					//cout << "modifier::>>" << endl;
					currentOperand->setModifier(query[i]);
				} else {
					//cout << "op::>>" << endl;
					//todo make a new node three
					//When a+-a-10
					//a <- left operand
					//+ <- operator
					//- <- right operand
					//a <- right operand
					//- <- New tree and operator 
					//10 <- right operator
					
					//When Open ( and there is a symbol 
					if (currentFactor > currentOperand->getFactor()) {

						/*
						  When the current factor is more than currentOperand's factor
						  we need to organize the tree afterwards the code below:

						  A tmpnode treeNode will be created

						  The current operand (right operand) will be the left operand of tmpnode
						  and the tmpnode will be the right operand of current node;

						  Ex:

						   10 + (20 * 20)

						   Tr(Lf=10, Op=+, Rg=20)
						   //When read the char '*'
						   Tr(Lf=10, Op=+, Rg=Tr(Lf=20, Op=*, Rg=20))
						*/
						currentOperand->setFactor(currentFactor);
						tmpNode = new TreeNode(currentFactor);
						tmpNode->setLeftOperand(currentOperand);
						tmpNode->setOperator(new Operator(operatorType));
						currentOperand = new TreeNode(currentFactor);
						currentOperand->setType(NUMERIC_TYPE);
						tmpNode->setRightOperand(currentOperand);

						node->setRightOperand(tmpNode);
						node = tmpNode;
					} else {
						//Appeding char to right operand
						tmpNode = new TreeNode(currentFactor);
						tmpNode->setLeftOperand(node);
						tmpNode->setOperator(new Operator(operatorType));
						currentOperand = new TreeNode(currentFactor);
						currentOperand->setType(NUMERIC_TYPE);
						tmpNode->setRightOperand(currentOperand);
						node = tmpNode;
						if (currentFactor == 0)
							mainNode = node;
					}
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


#include <string>
#include <iostream>
#include "Tokenizer.h"
using namespace std;

int main() {
	Tokenizer* tokenizer = new Tokenizer("(2 + 1) * (2 + 2)");
	TreeNode *token = tokenizer->getToken();
	cout << "Debug ::: " << token->_debug() << endl;
	//cout << token->getValue() << endl;
    //cout << token->getRightOperand()->getValue() << endl;
	//Operand *op = token.getLeftOperand();
	//token.getLeftOperand().getValue();
	//string a = string("dfdsfs");
	//cout << a.length() << endl;
	cout << "Result" << token->getValue() << endl;
	system("pause");
	return 0;
}
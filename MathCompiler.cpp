#include <string>
#include <iostream>
#include "Tokenizer.h"
using namespace std;

int main() {
	Tokenizer* tokenizer = new Tokenizer("10+20");
	TreeNode *token = tokenizer->getToken();
	cout << token->getValue() << endl;
    cout << token->getRightOperand()->getValue() << endl;
	//Operand *op = token.getLeftOperand();
	//token.getLeftOperand().getValue();
	//string a = string("dfdsfs");
	//cout << a.length() << endl;
	
	system("pause");
	return 0;
}
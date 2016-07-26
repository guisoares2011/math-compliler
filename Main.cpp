#include "Tokenizer.h"
#include <iostream>

using namespace std;

int main(void){
	Tokenizer* token = new Tokenizer();
	Result* r = token->parse("(3 * 2) * 2 + (1 + 6)");
	r->calc();
	cout << r->debug() << endl;
	cout << r->calc() << endl;
	system("pause");
	return 0;
}
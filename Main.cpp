#include "Tokenizer.h"
#include <iostream>

using namespace std;

int main(void){
	Tokenizer* token = new Tokenizer();
	Result* r = token->parse("1 + 2 + 3");
	// 6 * 2 -> 12 -> 19
	//r->calc();
	//cout << ((3 * 2) * 2 + (1 + 6)) * 15 / (2 + 1) << endl;
	//cout << r->debug() << endl;
	//cout << r->calc() << endl;
	system("pause");
	return 0;
}
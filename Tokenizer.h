#ifndef H_TOKENIZER
#define H_TOKENIZER

#include <string>
using namespace std;
//Chars

//Type of operand
#define NUMERIC_TYPE 1
#define UNKNOWN_TYPE 2 // (eg: 10a, 19ab)
#define TREENODE_TYPE 3
#define PUNCT_TYPE 4 // .+-/*%^
#define SPACE_TYPE 5 // ' '
#define PARHL_TYPE 6 // (
#define PARHR_TYPE 7 // )

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

#include "Treenode.h"
#include "Operator.h"

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
	void setToken(TreeNode* token);
	TreeNode* getToken() {
		return this->token;
	}
};



#endif // !H_TOKENIZER

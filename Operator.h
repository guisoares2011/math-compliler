#pragma once
#include "Operation.h"

class OperadorBin : public Operation
{
	protected:
		Operation* left;
		Operation* right;
		int operatorFactor = 0;
		char symbol;
	public:
	
		OperadorBin(int __factor) : symbol('#'), left(0), right(0) {
			this->factor = __factor;
		}
		virtual ~OperadorBin(void) {}
		int getFactor() { return factor + operatorFactor; }
		char getSymbol() { return symbol; };
		void setLeft(Operation* __x) { this->left = __x; }
		void setRight(Operation* __x) { this->right = __x; }

		Operation* getLeft(void) { return this->left; }
		Operation* getRight(void) { return this->right;}

		std::string debug(void) {
			return "( " + ((left) ? this->left->debug() : "null") + this->getSymbol() + ((right) ? this->right->debug() : "null") + ")";
		}

};

class Result : public OperadorBin {
public:
	Result(int f = 0) : OperadorBin(f) { symbol = '='; }
	virtual ~Result(void) {}
	double calc(void) { return this->right->calc(); }
};

class Soma : public OperadorBin
{
public:
	Soma(int f = 0) : OperadorBin(f) { symbol = '+'; }
	virtual ~Soma(void) {}
	double calc(void) { return this->left->calc() + this->right->calc(); }
};

class Subtracao : public OperadorBin
{
public:
	Subtracao(int f = 0) : OperadorBin(f) { symbol = '-'; }
	virtual ~Subtracao(void) {}
	double calc(void) { return this->left->calc() - this->right->calc(); }
};

class Multiplicacao : public OperadorBin
{
public:
	Multiplicacao(int f = 0) : OperadorBin(f) { symbol = '*'; }
	virtual ~Multiplicacao(void) {}
	double calc(void) { return this->left->calc() * this->right->calc(); }
};

class Divisao : public OperadorBin
{
public:
	Divisao(int f = 0) : OperadorBin(f) { symbol = '/'; }
	virtual ~Divisao(void) {}
	double calc(void) { return this->left->calc() / this->right->calc(); }
};

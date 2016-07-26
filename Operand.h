#pragma once
#include "Operation.h"
#include <string>

class Operand : public Operation {
	
	private:
		double valor;

	public:
		Operand(double __x) : valor(__x) {}
		virtual ~Operand(void) {}
		double calc(void) { return valor; }
		int getFactor() { return factor; }
		std::string debug(void) {
			return std::to_string(valor);
		}
};
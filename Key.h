#ifndef KEY_H_
#define KEY_H_

#include "BigInt.h"
#include <iostream>

class Key
{
	private:
		BigInt modulus;
		BigInt exponent;
	public:
		Key(const BigInt &modulus, const BigInt &exponent) :
			modulus(modulus), exponent(exponent)
		{}
		const BigInt &GetModulus() const
		{
			return modulus;
		}
		const BigInt &GetExponent() const
		{
			return exponent;
		}
		friend std::ostream &operator<<(std::ostream &cout, const Key &key);
};

#endif /*KEY_H_*/

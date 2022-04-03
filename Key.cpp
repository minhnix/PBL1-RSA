#include "Key.h"

std::ostream &operator<<(std::ostream &cout, const Key &key)
{
	return std::cout 
	<< "Modulus: " << key.GetModulus() << std::endl 
	<< "Exponent: " << key.GetExponent();
}

#include "KeyPair.h"

std::ostream &operator <<(std::ostream &cout, const KeyPair &k)
{
	return std::cout 
	<< "Private key:" << std::endl << k.GetPrivateKey() << std::endl
	<< "Public key:" << std::endl << k.GetPublicKey();
}

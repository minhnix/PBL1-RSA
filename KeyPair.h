#ifndef KEYPAIR_H_
#define KEYPAIR_H_

#include "Key.h"
#include <iostream>

class KeyPair
{
	private:
		const Key privateKey;
		const Key publicKey;
	public:
		KeyPair(Key privateKey, Key publicKey): 
			privateKey(privateKey), publicKey(publicKey)
		{}
		const Key &GetPrivateKey() const
		{
			return privateKey;
		}
		const Key &GetPublicKey() const
		{
			return publicKey;
		}
		friend std::ostream &operator <<(std::ostream &cout, const KeyPair &k);
};

#endif /*KEYPAIR_H_*/

#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>	//ostream, istream
#include <cmath>	//sqrt()
#include <string>	//ToString(), BigInt(std::string)

class BigInt
{
	private:
		/* An array of digits stored right to left,
		* i.e. int 345 = unsigned char {[5], [4], [3]} */
		unsigned char *digits;
		// The total length of the allocated memory
		unsigned long int length;
		// Number of digits
		unsigned long int digitCount;
		// Sign
		bool positive;
		/* Multiplication factor for the length property
		 * when creating or copying objects. */
		static const double FACTOR;
		/* Transforms the number from unsigned long int to unsigned char[]
		 * and pads the result with zeroes. Returns the number of digits. */
		static unsigned long int int2uchar(	unsigned long int number, 
											unsigned char *digits, 
											unsigned long int padding);
		/* Converts ASCII digits to equivalent unsigned char numeric values. */
		static void char2uchar(	unsigned char *array, 
								unsigned long int length);
		/* Check if all ASCII values are digits '0' to '9'. */
		static bool allCharsAreDigits(	const char *array, 
										unsigned long int length);
		/* Compares two BigInt. If the last two arguments are 
		 * omitted, the comparison is sign-insensitive (comparison by 
		 * absolute value). Returns 0 if a == b, 1 if a > b, 2 if a < b. */ 
		static int compareNumbers(	unsigned char *a, unsigned long int na,
		                            unsigned char *b, unsigned long int nb, 
		                            bool aPositive = true, 
		                            bool bPositive = true);
		/* Multiplies two unsigned char[] using the Divide and Conquer 
		 * a.k.a. Karatsuba algorithm .*/
		static void karatsubaMultiply(	unsigned char *a, unsigned char *b,
										unsigned long int n, 
										unsigned char *buffer);
		/* Multiplies two unsigned char[] the long way. */
		static void longMultiply(	unsigned char *a, unsigned long int na,
									unsigned char *b, unsigned long int nb,
									unsigned char *result);
		/* Simple addition, used by the multiply function.
		 * Returns the remaining carry. */
		static unsigned char quickAdd(	unsigned char *a, unsigned char *b, 
										unsigned long int n);
		/* Simple subtraction, used by the multiply function. */
		static void quickSub(	unsigned char *a, unsigned char *b, 
								unsigned char *end, unsigned long int n);
		/* Divides two BigInt numbers. */
		static void divide(	const BigInt &dividend, const BigInt &divisor,
							BigInt &quotient, BigInt &remainder);
		/* Returns the value of the specified unsigned char[] as long int. */
		static unsigned long int toInt(unsigned char *digits, int n);
		/* Saves the sum of two unsigned char* shorter and longer into result. 
		 * It must be nShorter <= nLonger. If doFill == true, it fills the 
		 * remaining free places with zeroes (used in KaratsubaMultiply()). 
		 * Returns true if there was an overflow at the end (meaning that
		 * the result.digitCount was longer.digitCount + 1. */
		static bool add(unsigned char *shorter, unsigned long int nShorter, 
					unsigned char *longer, unsigned long int nLonger, 
					unsigned char *result, int nResult, 
					bool doFill = true);
		/* Shifts the digits n places left. */
		BigInt &shiftLeft(unsigned long int n);
		/* Shifts the digits n places right. */
		BigInt &shiftRight(unsigned long int n);
		/* Expands the digits* to n. */
		void expandTo(unsigned long int n);
	public:
		BigInt();
		BigInt(const char *charNum);
		BigInt(unsigned long int intNum);
		BigInt(const std::string &str);
		BigInt(const BigInt &number);
		BigInt &operator =(const BigInt &rightNumber);
		~BigInt();
		operator std::string() const;
		friend std::ostream &operator <<(	std::ostream &cout, 
											const BigInt &number);
		friend std::istream &operator >>(	std::istream &cin, 
											BigInt &number);
		friend bool operator <(const BigInt &a, const BigInt &b);
		friend bool operator <=(const BigInt &a, const BigInt &b);
		friend bool operator >(const BigInt &a, const BigInt &b);
		friend bool operator >=(const BigInt &a, const BigInt &b);
		friend bool operator ==(const BigInt &a, const BigInt &b);
		friend bool operator !=(const BigInt &a, const BigInt &b);
		friend BigInt operator + (const BigInt &a, const BigInt &b);
		BigInt &operator+();
		BigInt &operator++();
		BigInt operator++(int);
		BigInt &operator+=(const BigInt &number);
		BigInt operator-() const;
		friend BigInt operator-(const BigInt &a, const BigInt &b);
		BigInt &operator--();
		BigInt operator--(int);
		BigInt &operator-=(const BigInt &number);
		friend BigInt operator*(const BigInt &a, const BigInt &b);
		BigInt &operator*=(const BigInt &number);
		friend BigInt operator/(const BigInt &a, const BigInt &b);
		BigInt &operator/=(const BigInt &number);
		friend BigInt operator%(const BigInt &a, const BigInt &b);
		BigInt &operator%=(const BigInt &number);
		/* Returns *this to the power of n 
		 * using the fast Square and Multiply algorithm. */
		BigInt GetPower(unsigned long int n) const;
		/* *this = *this to the power of n. */
		void SetPower(unsigned long int n);
		/* Returns *this to the power of n 
		 * using the fast Square and Multiply algorithm. */
		BigInt GetPower(BigInt n) const;
		/* *this = *this to the power of n. */
		void SetPower(BigInt n);
		/* Returns (*this to the power of b) mod n. */
		BigInt GetPowerMod(const BigInt &b, const BigInt &n) const;
		/* *this = (*this to the power of b) mod n. */
		void SetPowerMod(const BigInt &b, const BigInt &n);
		/* Returns the 'index'th digit (zero-based, right-to-left). */
		unsigned char GetDigit(unsigned long int index) const;
		/* Sets the value of 'index'th digit 
		 * (zero-based, right-to-left) to 'value'. */
		void SetDigit(unsigned long int index, unsigned char value);
		/* Returns the number of digits. */
		unsigned long int Length() const;
		/* Returns true if *this is positive, otherwise false. */
		bool IsPositive() const;
		/* Returns true if *this is odd, otherwise false. */
		bool IsOdd() const;
		/* Returns the value of BigInt as std::string. */
		std::string ToString(bool forceSign = false) const;
		/* Returns a value indicating whether *this equals 0. */
		bool EqualsZero() const;
		/* Returns the absolute value. */
		BigInt Abs() const;
};

inline BigInt::~BigInt()
{
	delete[] digits;
}

inline BigInt &BigInt::operator+()
{
	return *this;
}

/* Returns the number of digits. */
inline unsigned long int BigInt::Length() const
{
	return digitCount;
}

/* Returns true if *this is positive, otherwise false. */
inline bool BigInt::IsPositive() const
{
	return positive;
}

/* Returns true if *this is odd, otherwise false. */
inline bool BigInt::IsOdd() const
{
	return digits[0] & 1;
}

/* Returns a value indicating whether *this equals 0. */
inline bool BigInt::EqualsZero() const
{
	return digitCount == 1 && digits[0] == 0;
}
		
// A BigInt number with the value of 0. 
static const BigInt BigIntZero;
// A BigInt number with the value of 1. 
static const BigInt BigIntOne(1L);


#endif /*BIGINT_H_*/

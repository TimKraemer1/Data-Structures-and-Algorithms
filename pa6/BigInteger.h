//Tim Kraemer
//cruzID: tikraeme
//pa6

#pragma once

#include <iostream>
#include <string>

#include "List.h"

#ifndef BIG_INTEGER_H_INCLUDE_
#define BIG_INTEGER_H_INCLUDE_


class BigInteger {

	private:
		int signum;
		List digits;

	public:

		BigInteger();
		BigInteger(std::string s);
		BigInteger(const BigInteger& N);
		

		//Access functions
		int sign() const;
		int compare(const BigInteger& N) const;

		//Manipulation procedures
		
		void makeZero();
		void negate();

		//BigInteger Arithmetic operations
		BigInteger add(const BigInteger& N) const;
		BigInteger sub(const BigInteger& N) const;
		BigInteger mult(const BigInteger& N) const;
		
		//Other functions
		std::string to_string();

		//Overriden Operators 
		friend std::ostream& operator<<( std::ostream& stream, BigInteger N);
		friend bool operator==(const BigInteger& A, const BigInteger& B);
		friend bool operator<(const BigInteger& A, const BigInteger& B);
		friend bool operator<=( const BigInteger& A, const BigInteger& B);
	    friend bool operator>( const BigInteger& A, const BigInteger& B );
		friend bool operator>=( const BigInteger& A, const BigInteger& B );
		friend BigInteger operator+( const BigInteger& A, const BigInteger& B );
		friend BigInteger operator+=( BigInteger& A, const BigInteger& B );
		friend BigInteger operator-( const BigInteger& A, const BigInteger& B );
		friend BigInteger operator-=( BigInteger& A, const BigInteger& B );
		friend BigInteger operator*( const BigInteger& A, const BigInteger& B );
		friend BigInteger operator*=( BigInteger& A, const BigInteger& B );
};

#endif

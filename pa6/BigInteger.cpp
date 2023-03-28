//Tim Kraemer
//CruzID: tikraeme
//pa6

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cstdlib>

#include "BigInteger.h"
#include "List.h"

int power = 9;
long base = 1000000000;

BigInteger::BigInteger() {
	signum = 0;
	List digits;
}

BigInteger::BigInteger(std::string s) {
	signum = 1;
	
	if(s.size() < 1) {
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	std::string s1;
	if(s[0] == '+' || s[0] == '-') {
		if(s[0] == '-') {
			signum = -1;
		}
		s1 = s.substr(1, s.length() - 1);
	}
	else {
		s1 = s;
	}

	s1.erase(0, std::min(s1.find_first_not_of('0'), s1.size()-1));

	long node;
	std::string container = "";
	for(int i = (int)s1.length()-1; i >= 0; i--) {
		if(!(std::isdigit(s1[i]))){
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
		container = s1[i] + container;
		if((int)container.length() == power) {
			node = std::stol(container);
			digits.insertAfter(node);
			container = "";
		}
	}
	if(container.length() > 0 && (int)container.length() < power) {
		node = std::stol(container);
		digits.insertBefore(node);
	}
}

BigInteger::BigInteger(const BigInteger& N) {
	signum = N.signum;
	digits = N.digits;
}

int BigInteger::sign() const {
	return signum;
}

void BigInteger::makeZero() {
	digits.clear();
	signum = 0;
}

void BigInteger::negate() {
	if(signum == 0) {
		return;
	}
	signum *= -1;
}

//Helper functions--------------------------------------------------
//correct implementation of floor
long floor(long x, int b) {
	if(x < 0) {
		if(x % b == 0) {
			return x/b;
		}
		else {
			return x/b - 1;
		}
	}
	else {
		return x/b;
	}
}

//correct implementation of modulo
long modulo(long x, int b) {
	return x - b * floor(x, b);
}

void negateList(List& L) {
	L.moveFront();
	while(L.position() < L.length()) {
		long curr = L.peekNext();
		L.setAfter(-1*curr);
		L.moveNext();
	}
}

void sumList(List& S, List A, List B, int sgn) {
	A.moveBack();
	B.moveBack();
	S.clear();
	long sum;
	long a;
	long b;
	while(A.position() != 0 || B.position() != 0) {
		S.moveFront();
		if(A.position() != 0 && B.position() == 0) {
			S.insertBefore(A.peekPrev());
			A.movePrev();
		}
		else if(A.position() == 0 && B.position() != 0) {
			S.insertBefore(sgn * B.peekPrev());
			B.movePrev();
		}
		else {
			a = A.peekPrev();
			b = B.peekPrev();
			sum = a + (sgn*b);
			S.insertBefore(sum);
			B.movePrev();
			A.movePrev();
		}
	}
}

int normalizeList(List& L) {
	if(L.length() == 0) {
		return 0;
	}
	L.moveBack();
	//non-normalized digit in BigInt
	long digit;
	//carry over to next left digit in BigInt
	long carryover = 0;
	while(L.position() > 0) {
		
		digit = L.peekPrev();
		L.setBefore(digit + carryover);
		digit = L.peekPrev();
		
		carryover = floor(digit, base);
		L.setBefore(modulo(digit, base));
		
		if(L.position() == 1 && carryover < 0 && carryover > -1*base) {
			L.movePrev();
			L.insertBefore(carryover);
			break;
		}
		else if(L.position() == 1 && (carryover > 0 || carryover < -1*base)) {
			L.movePrev();
			L.insertBefore(carryover);
		}

		L.movePrev();
	}

	//negative sign normalization
	if(L.front() < 0) {
		carryover = 0;
		negateList(L);
		L.moveBack();
		while(L.position() > 0) {
			digit = L.peekPrev();
			L.setBefore(digit + carryover);
			digit = L.peekPrev();
			if(digit < 0) {
				L.setBefore(digit + base);
				carryover = -1;
			}
			L.movePrev();
		}
	}

	L.moveFront();
	while(L.peekNext() == 0) {
		L.eraseAfter();
		if(L.length() == 0) {
			break;
		}
	}

	if(carryover == -1) {
		return -1;
	}
	else if (L.length() == 0){
		return 0;
	}
	else {
		return 1;
	}
}

void shiftList(List& L, int p) {
	L.moveBack();
	for(int i = 0; i < p; i++) {
		L.insertBefore(0);
	}
}

void scalarMultList(List& L, ListElement M) {
	L.moveFront();
	while(L.position() < L.length()) {
		long curr = L.peekNext();
		L.setAfter(M*curr);
		L.moveNext();
	}
}
//----------------------------------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger sum;
	List sum_digits;
	List a = this->digits;
	List b = N.digits;
	
	if(this->signum == -1) {
		negateList(a);
	}
	if(N.signum == -1) {
		negateList(b);
	}

	sumList(sum_digits, a, b, 1);
	int sign = normalizeList(sum_digits);
	sum.digits = sum_digits;
	sum.signum = sign;
	return sum;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
	
	BigInteger diff;
	List diff_digits;
	List a = this->digits;
	List b = N.digits;
	
	if(this->signum == -1) {
		negateList(a);
	}
	if(N.signum == -1) {
		negateList(b);
	}

	sumList(diff_digits, a, b, -1);
	int sign = normalizeList(diff_digits);
	diff.digits = diff_digits;
	diff.signum = sign;
	return diff;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger prod;
	List a = this->digits;
	List b = N.digits;
	if(this->signum == -1) {
		negateList(a);
	}
	if(N.signum == -1) {
		negateList(b);
	}
	List master_mult;
	List temp;
	int shift = 0;

	for(a.moveBack(); a.position() > 0; a.movePrev()) {
		temp = b;
		scalarMultList(temp, a.peekPrev());
		shiftList(temp, shift);
		sumList(master_mult, master_mult, temp, 1);
		prod.signum = normalizeList(master_mult);
		temp.clear();
		shift++;
		if(prod.signum == -1) {
			negateList(master_mult);
		}
	}
	normalizeList(master_mult);
	prod.digits = master_mult;
	return prod;
}

std::string BigInteger::to_string() {
	std::string S = "";
	
	if(digits.length() == 0) {
		S += "0";
		return S;
	}
	digits.moveFront();
	std::string digit;
	while(digits.position() < digits.length()) {
		digit = std::to_string(digits.peekNext());
		if((int)digit.length() < power) {
			for(int i = 0; i < power - (int)digit.length(); i++) {
				S += "0";
			}
			S += digit;
		}
		else {
			S += digit;
		}
		digits.moveNext();
	}
	S.erase(0, std::min(S.find_first_not_of('0'), S.size()-1));
	if(signum == -1) {
		S = "-" + S;
	}
	return S;
}


int BigInteger::compare(const BigInteger& N) const {
	List a = this->digits;
	List b = N.digits;
	if(a.length() > b.length()) {
		return 1;
	}
	else if(a.length() < b.length()) {
		return -1;
	}
	else {
		if(this->signum == -1) {
			negateList(a);
		}
		if(N.signum == -1) {
			negateList(b);
		}
		a.moveFront();
		b.moveFront();
		while(a.position() < a.length()) {
			if(a.peekNext() > b.peekNext()) {
				return 1;
			}
			else if(a.peekNext() < b.peekNext()) {
				return -1;
			}
			a.moveNext();
			b.moveNext();
		}
		return 0;
	}
}


std::ostream& operator<<(std::ostream& stream, BigInteger N) {
	return stream << N.BigInteger::to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
	if(A.BigInteger::compare(B) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<(const BigInteger& A, const BigInteger& B) {
	if(A.BigInteger::compare(B) == -1) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
	int comparison = A.BigInteger::compare(B);
	if(comparison == 0 || comparison == -1) {
		return true;
	}
	else {
		return false;
	}
}

bool operator>(const BigInteger& A, const BigInteger& B) {
	if(A.BigInteger::compare(B) == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool operator >=(const BigInteger& A, const BigInteger& B) {
	int comparison = A.BigInteger::compare(B);
	if(comparison == 1 || comparison == 1) {
		return true;
	}
	else {
		return false;
	}
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
	BigInteger sum;
	sum = A.add(B);
	return sum;
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
	A = A.add(B);
	return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
	BigInteger diff;
	diff = A.sub(B);
	return diff;
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
	A = A.sub(B);
	return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
	BigInteger prod;
	prod = A.mult(B);
	return prod;
}

BigInteger operator *=(BigInteger& A, const BigInteger& B) {
	A = A.mult(B);
 	return A;
}

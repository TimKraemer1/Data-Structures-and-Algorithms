//Tim Kraemer
//CruzID: tikraeme
//pa6

#include <iostream>
#include <string>

#include "BigInteger.h"

using namespace std;

int main(void) {
	BigInteger A, B, C, D;

	A = BigInteger("111122223333");
	B = BigInteger("-111122223333");
	C = BigInteger("50");

	cout << "B: " << B << "\n";
	cout << "A: " << A << "\n\n";
	cout << A << "+" << B << " = " << A+B << "\n\n";

	cout << A << " - " << B << " = " << A-B << "\n\n";
	cout << A << " * " << B << " = " << A * B << "\n\n";

	cout << "A sign: " << A.sign() << "\n";
	cout << "B sign: " << B.sign() << "\n\n";

	cout << "Comparison: " << A.compare(B) << "\n\n";

	cout << "to_string() Test: " << A.to_string() << "\n\n";

	A*=B;
	cout << "A*=B = " << A << "\n\n";
	
	B+=C;
	cout << "B+=C = " << B << "\n\n";

	B-=C;
	cout << "B-=C = " << B << "\n\n";
}

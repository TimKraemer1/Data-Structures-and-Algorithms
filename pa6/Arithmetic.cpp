//Tim Kraemer
//CruzID: tikraeme
//pa6

#include <iostream>
#include <string>
#include <fstream>

#include "BigInteger.h"
#include "List.h"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 3) {
		cout << "Error: Expected 3 arguements, got " << argc << " instead\n";
		return -1;
	}

	ifstream i_file (argv[1]);
	ofstream o_file (argv[2]);
	
	string a;
	string b;
	string temp;
	if(i_file.is_open() && o_file.is_open()) {
		getline(i_file, a);
		getline(i_file, temp);
		getline(i_file, b);
	}
	i_file.close();

	BigInteger A(a);
	BigInteger B(b);
	
	o_file << A << "\n\n";
	
	o_file << B << "\n\n";
	
	BigInteger sum = A+B;
	o_file << sum << "\n\n";

	BigInteger diff1 = A-B;
	o_file << diff1 << "\n\n";

	BigInteger diff2 = A-A;
	o_file << diff2 << "\n\n";

	BigInteger three("3");
	BigInteger two("2");
	BigInteger prod1 = (three*A) - (two*B);
	o_file << prod1 << "\n\n";

	BigInteger prod2 = A*B;
	o_file << prod2 << "\n\n";
	
	BigInteger prod3 = A*A;
	o_file << prod3 << "\n\n";

	BigInteger prod4 = B*B;
	o_file << prod4 << "\n\n";

	BigInteger nine("9");
	BigInteger sixt("16");
	BigInteger prod5 = (nine*A*A*A*A) + (sixt*B*B*B*B*B);
	o_file << prod5 << "\n\n";
	
	o_file.close();
}

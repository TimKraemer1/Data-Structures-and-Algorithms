//Tim Kraemer
//CruzID: tikraeme
//pa8

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 3) {
		cout << "Error: Expected 3 arguements, got " << argc << " instead\n";
		return -1;
	}
	ifstream i_file (argv[1]);
	ofstream o_file (argv[2]);
	
	Dictionary a;
	int line = 1;
	string temp;
	if(i_file.is_open() && o_file.is_open()) {
		while(getline(i_file, temp)) {
			a.setValue(temp, line);
			line++;
		}
	}
	else {
		cout << "Error: Could not open file\n";
		return -1;
	}
	i_file.close();
	
	o_file << a;
	o_file << endl;
	o_file << a.pre_string();

	o_file.close();
}

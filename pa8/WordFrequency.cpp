//Tim Kraemer
//CruzID: tikraeme
//pa8

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdexcept>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
	size_t begin, end, len;
	ifstream in;
	ofstream out;
	string line;
	string tokenBuffer;
	string token;
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

	if(argc != 3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}

	in.open(argv[1]);
	if(!in.is_open()) {
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}

	out.open(argv[2]);
	if(!out.is_open() ) {
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
	}
	
	Dictionary dict;

	while(getline(in, line)) {
		len = line.length();

		tokenBuffer = "";

		begin = min(line.find_first_not_of(delim, 0), len);
		end = min(line.find_first_of(delim, begin), len);
		token = line.substr(begin, end-begin);
		transform(token.begin(), token.end(), token.begin(), ::tolower);

		while(token != "") {
			if(dict.contains(token)) {
				dict.getValue(token)++;
			}
			else {
				dict.setValue(token, 1);
			}

			begin = min(line.find_first_not_of(delim, end+1), len);
			end = min(line.find_first_of(delim, begin), len);
			token = line.substr(begin, end-begin);
			transform(token.begin(), token.end(), token.begin(), ::tolower);
		}
	}

	out << dict;

	in.close();
	out.close();
}

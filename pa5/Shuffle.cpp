//Tim Kraemer
//CruzID: tikraeme
//pa5

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

using namespace std;

void shuffle(List& D) {
	List a;
	List b;

	int half_len = D.length() / 2;
	D.moveFront();
	for(int i = 0; i < half_len; i++) {
		a.insertBefore(D.peekNext());
		D.moveNext();
	}
	while(D.position() < D.length()) {
		b.insertBefore(D.peekNext());
		D.moveNext();
	}
	D.clear();
	a.moveFront();
	b.moveFront();
	for(int i = 0; i < half_len+1; i++) {
		if(b.position() != b.length()) {
			D.insertBefore(b.peekNext());
			b.moveNext();
		}
		if(a.position() != a.length()) {
			D.insertBefore(a.peekNext());
			a.moveNext();
		}
	}
}

int main(int argc, char* argv[]) {
	//if(argc != 2) {
	//	cout << "Error: Expected 2 arguements, got " << argc << " instead\n";
	//	return -1;
	//}
	cout << "deck size\tshuffle count\n------------------------------\n";
	
	int shuffle_count;

	List a;
	for(int i = 1; i <= atoi(argv[1]); i++) {
		shuffle_count = 0;
		a.moveBack();
		a.insertBefore(i);
		List b = a;
		cout << " " << i << "\t\t";
		shuffle(a);
		shuffle_count++;
		while(!(b.equals(a))) {
			shuffle(a);
			shuffle_count++;
		}
		cout << shuffle_count;
		cout << "\n";
	}
}

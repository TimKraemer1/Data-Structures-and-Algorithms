//Tim Kraemer
//CruzID: tikraeme
//pa5

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

using namespace std;

int main() {
	List A;
	for(int i = 0; i < 10; i++) {
		A.insertAfter(i);
	}
	A.moveFront();
	
	cout << "Front: " << A.front() << "\n";
	cout << "Back: " << A.back() << "\n";

	cout << A.to_string();

	cout << A.position() << "\n";
	
	A.moveBack();

	A.movePrev();
	A.movePrev();

	A.insertBefore(50);
	cout << A.to_string();
	A.moveBack();
	
	cout << "Cursor position: " << A.position() << "\n";
	cout << "Peek Previous: " << A.peekPrev();
	cout << "\n";
	
	A.movePrev();
	A.movePrev();
	A.movePrev();

	A.eraseAfter();
	A.eraseBefore();

	cout << A.to_string();
	A.moveBack();

	cout << "Cursor position: " << A.position() << "\n";
	cout << A.peekPrev() << "\n";

	A.insertBefore(10);
	A.insertAfter(11);

	cout << A.to_string();

	A.clear();

	cout<< "Length: " << A.length();
	cout << "\n\n";

	A.insertBefore(1);
	A.insertBefore(2);
	A.insertBefore(1);
	A.insertBefore(3);
	A.insertBefore(2);
	A.insertBefore(5);

	A.movePrev();
	A.movePrev();
	A.movePrev();

	cout << A.to_string();
	cout << "Cursor Position: " << A.position() << "\n";
	
	A.cleanup();
	cout << "After cleanup(): \n";
	cout << A.to_string();
	cout << "Cursor Position: " << A.position() << "\n";
	
	cout << "Finding Position 5: " << A.findNext(5) << "\n";
	cout << "Finding Position 2: " << A.findPrev(2) << "\n";
	cout << "\n";

	A.clear();
	List B;
	A.insertBefore(1);
	A.insertBefore(2);
	A.insertBefore(3);
	B.insertBefore(4);
	B.insertBefore(5);
	B.insertBefore(6);
	
	List C = A.concat(B);
	cout << A.to_string();
	cout << B.to_string();
	cout << C.to_string();

	A.clear();

	A.insertBefore(1);
	A.insertBefore(2);
	A.insertBefore(2);
	A.insertBefore(1);
	A.insertBefore(2);
	A.insertBefore(3);
	A.insertBefore(1);
	A.findPrev(3);
	A.movePrev();
	cout << A.to_string();
	cout << A.position() << "\n";
	A.cleanup();
	cout << A.to_string();
	cout << A.position() << endl;

	cout << "A == B is " << (A==B?"true":"false") << "\n";
	cout << B;
}	

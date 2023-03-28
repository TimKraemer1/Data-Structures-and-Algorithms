//Tim Kraemer
//CruzID: tikraeme
//pa7

#include <iostream>
#include <string>

#include "Dictionary.h"

using namespace std;

int main(void) {
	Dictionary A;
	A.setValue("d", 1);
	A.setValue("b", 5);
	A.setValue("a", 10);
	A.setValue("c", 15);
	A.setValue("f", 20);
	A.setValue("e", 25);
	A.setValue("g", 30);

	cout << "A printing: \n" << A;

	cout << "A preOrder printing: \n" << A.pre_string();
	cout << "A inOrder printing: \n" << A.to_string();

	Dictionary B = A;

	cout << "A size(): " << A.size() << endl << endl;

	cout << "A contains \"a\": " << A.contains("a") << endl << endl;

	cout << "A value of \"c\": " << A.getValue("c") << endl << endl;

	A.begin();
	cout << "Is current defined: " << A.hasCurrent() << endl << endl;

	cout << "Current Key: "  << A.currentKey() << endl << endl;

	cout << "Current Value: " << A.currentVal() << endl << endl;

	A.end();
	cout << "Current Key: " << A.currentKey() << endl << endl;
	cout << "Current Value: " << A.currentVal() << endl << endl;

	A.begin();
	A.next();
	A.next();
	cout << "Current Key: " << A.currentKey() << endl << endl;
	cout << "Current Value: " << A.currentVal() << endl << endl;

	A.prev();
	cout << "Current Key: " << A.currentKey() << endl << endl;
	cout << "Current Value: " << A.currentVal() << endl << endl;

	cout << "Are A and B equal: " << A.equals(B) << endl << endl;

	A.setValue("e", 7);
	A.setValue("z", 9);

	cout << "After changing values in A:\n" << A << endl << endl;

	cout << "Are A and B equal: " << A.equals(B) << endl << endl;


}

//Tim Kraemer
//CruzID: tikraeme
//pa6

#include <string>
#include <iostream>
#include <stdexcept>
#include "List.h"

//Private Constructor 

//Node Constructor
List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}

//Class Constructors and Destructors

//Creates new List in the empty state
List::List() {
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L) {
	//make this an empty List
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;

	//load elements of L into this List
	Node* N = L.frontDummy->next;
	while(N->next != nullptr) {
		this->insertBefore(N->data);
		N = N->next;
	}
}

List::~List() {
	clear();
	delete(frontDummy);
	delete(backDummy);
}

//Returns length of list
int List::length() const {
	return num_elements;
}

ListElement List::front() const {
	if(num_elements < 1) {
		throw std::length_error("List: front(): empty List");
	}
	return (frontDummy->next)->data;
}

//Returns back element of List
ListElement List::back() const {
	if(num_elements < 1) {
		throw std::length_error("List: back(): empty List");
	}
	return (backDummy->prev)->data;
}

//Returns curr cursor element
int List::position() const {
	return pos_cursor;	
}

//Returns element after cursor
ListElement List::peekNext() const {
	if(pos_cursor >= num_elements) {
		throw std::length_error("List: peekNext(): empty List");
	}
	return afterCursor->data;
}

//Returns element before cursor
ListElement List::peekPrev() const {
	if(pos_cursor <= 0) {
		throw std::length_error("List: peekPrev(): empty List");
	}
	return beforeCursor->data;
}

//Sets List to empty list
void List::clear() {
	moveFront();
	while(length() > 0) {
		eraseAfter();
	}
}

//Moves cursor to front of List
void List::moveFront() {
	pos_cursor = 0;
	afterCursor = frontDummy->next;
	beforeCursor = frontDummy;
}

//Moves cursor to back of list
void List::moveBack() {
	pos_cursor = length();
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

//Moves cursor to next element
ListElement List::moveNext() {
	if(pos_cursor > length()) {
		throw std::out_of_range("List: moveNext(): cursor position invalid");
	}
	Node* a = afterCursor;
	Node* b = afterCursor->next;
	pos_cursor++;
	beforeCursor = a;
	afterCursor = b;
	return beforeCursor->data;
}

//Move cursor to previous element
ListElement List::movePrev() {
	if(pos_cursor <= 0) {
		throw std::out_of_range("List: movePrev(): cursor position invalid");
	}
	Node* a = beforeCursor->prev;
	Node* b = beforeCursor;
	pos_cursor--;
	beforeCursor = a;
	afterCursor = b;
	return afterCursor->data;
}

void List::insertBefore(ListElement x) {
	Node* newNode = new Node(x);
	Node* bef = beforeCursor;
	Node* aft = afterCursor;
	bef->next = newNode;
	newNode->prev = bef;
	aft->prev = newNode;
	newNode->next = aft;
	beforeCursor = newNode;
	num_elements++;
	pos_cursor++;
}

void List::insertAfter(ListElement x) {
	Node* newNode = new Node(x);
	Node* bef = beforeCursor;
	Node* aft = afterCursor;
	aft->prev = newNode;
	newNode->next = aft;
	bef->next = newNode;
	newNode->prev = bef;
	afterCursor = newNode;
	num_elements++;
}

void List::setAfter(ListElement x) {
	if(pos_cursor > length()) {
		throw std::out_of_range("List: setAfter(): cursor position invalid");
	}
	(afterCursor)->data = x;
}

void List::setBefore(ListElement x) {
	if(pos_cursor < 0) {
		throw std::out_of_range("List: setBefore(): cursor position invalid");
	}
	(beforeCursor)->data = x;
}

void List::eraseAfter() {
	if(pos_cursor >= length()) {
		throw std::out_of_range("List: eraseAfter(): cursor position invalid");
	}
	Node* a = afterCursor;
	beforeCursor->next = a->next;
	(a->next)->prev = beforeCursor;
	afterCursor = a->next;
	delete(a);
	num_elements--;
}

void List::eraseBefore() {
	if(pos_cursor <= 0) {
		throw std::out_of_range("List: eraseBefore(): cursor position invalid");
	}
	Node* a = beforeCursor;
	(a->prev)->next = afterCursor;
	afterCursor->prev = (a->prev);
	beforeCursor = a->prev;
	delete(a);	
	num_elements--;
	pos_cursor--;
}

int List::findNext(ListElement x) {
	while(pos_cursor < length()) {
		this->moveNext();
		if(beforeCursor->data == x) {
			return pos_cursor;
		}
	}
	return -1;
}

int List::findPrev(ListElement x) {
	while(pos_cursor > 0) {
		this->movePrev();
		if(afterCursor->data == x) {
			return pos_cursor;
		}
	}
	return -1;
}

void List::cleanup() {
	Node* N;
	Node* M;
	bool deleted;
	int Mposition;
	int Nposition = 0;
	for(N = frontDummy->next; N->next != nullptr; N = N->next) {
		M = N->next;
		Nposition++;
		deleted = false;
		Mposition = Nposition;
		while(M->next != nullptr) {
			if(!deleted) {
				Mposition++;
			}	
			deleted = false;
			if(N->data == M->data) {
				deleted = true;
				if(M == beforeCursor) {
					beforeCursor = M->prev;
				}
				else if(M == afterCursor) {
					afterCursor = M->next;
				}
				if(Mposition <= position()) {
					pos_cursor--;
				}
				Node* temp = M;
				M = M->next;
				Node* a = temp->prev;
				Node* b = temp->next;
				a->next = b;
				b->prev = a;
				delete(temp);
				num_elements--;
			}
			if(!deleted) {
				M = M->next;
			}
		}
	}
}

List List::concat(const List& L) const {
	List newList;
	Node* M = this->frontDummy->next;
	Node* N = L.frontDummy->next;
	while(M->next != nullptr) {
		newList.insertBefore(M->data);
		M = M->next;
	}
	while(N->next != nullptr) {
		newList.insertBefore(N->data);
		N = N->next;
	}
	newList.pos_cursor = 0;
	newList.beforeCursor = newList.frontDummy;
	newList.afterCursor = newList.frontDummy->next;
	return newList;
}

std::string List::to_string() const {
	Node* temp = frontDummy->next;
	std::string S = "(";
	while(temp->next != nullptr) {
		S += std::to_string(temp->data);
		temp = temp->next;
		if(temp->next != nullptr) {
			S += ", ";
		}
	}
	S += ")\n";
	return S;
}


bool List::equals(const List& R) const {
	bool eqs = false;
	Node* M = nullptr;
	Node* N = nullptr;

	eqs = (this->num_elements == R.num_elements);
	N = (this->frontDummy)->next;
	M = (R.frontDummy)->next;
	while(eqs && N->next != nullptr) {
		eqs = N->data == M->data;
		N = N->next;
		M = M->next;
	}
	return eqs;
}

std::ostream& operator<<( std::ostream& stream, const List& L) {
	return stream << L.List::to_string();
}

bool operator==(const List& A, const List& B) {
	return A.List::equals(B);
}

List& List::operator=(const List& L) {
	if(this != &L) {
		List temp = L;

		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	}

	return *this;
}

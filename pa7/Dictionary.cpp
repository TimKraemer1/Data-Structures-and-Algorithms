//Tim Kraemer
//CruzID: tikraeme
//pa7

#include <iostream>
#include <string>
#include <stdexcept>

#include "Dictionary.h"

//Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

Dictionary::Dictionary() {
	nil = new Node("nil", 0);
	nil->right = nil;
	nil->left = nil;
	nil->parent = nil;
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
	nil = new Node("nil", 0);
	root = nil;
	current = nil;
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
	clear();
	delete(this->nil);
}

int Dictionary::size() const{
	return num_pairs;
}

bool Dictionary::contains(keyType k) const {
	if(search(this->root, k) == nil) {
		return false;
	}
	else {
		return true;
	}
}

valType& Dictionary::getValue(keyType k) const {
	if(!contains(k)) {
		throw std::logic_error("Dictionary: getValue(): key does not exist");
	}
	Node* temp = search(this->root, k);
	return temp->val;
}

bool Dictionary::hasCurrent() const {
	return current != nil;
}

keyType Dictionary::currentKey() const {
	if( hasCurrent() == false) {
		throw std::logic_error("Dictionary: currentKey: current undefined");
	}
	return this->current->key;
}

valType& Dictionary::currentVal() const{
	if(hasCurrent() == false) {
		throw std::logic_error("Dictionary:: currentVal: current undefined");
	}
	return this->current->val;
}

void Dictionary::clear() {
	postOrderDelete(this->root);
	root = nil;
	current = nil;
	num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
	Node* y = nil;
	Node* x = this->root;
	while(x != nil) {
		y = x;
		if(k < x->key) {
			x = x->left;
		}
		else if( k > x->key) {
			x = x->right;
		}
		else {
			x->key = k;
			x->val = v;
			return;
		}
	}
	Node* z = new Node(k, v);
	z->parent = y;
	z->left = nil;
	z->right = nil;
	if(y == nil) {
		this->root = z;
	}
	else if(z->key < y->key) {
		y->left = z;
	}
	else {
		y->right = z;
	}
	num_pairs++;
}

void Dictionary::remove(keyType k) {
	if(!contains(k)) {
		throw std::logic_error("Dictionary: remove: key does not exist");
	}
	Node* z = search(this->root, k);
	if(z == current) {
		current = nil;
	}
	if(z->left == nil) {
		transplant(z, z->right);
	}
	else if(z->right == nil) {
		transplant(z, z->left);
	}
	else {
		Node* y = findMin(z->right);
		if(y->parent != z) {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	num_pairs--;
	delete(z);
}

void Dictionary::begin() {
	if(this->num_pairs > 0) {
		Node* z = findMin(this->root);
		this->current = z;
	}	
}

void Dictionary::end() {
	if(this->num_pairs > 0) {
		Node* z = findMax(this->root);
		this->current = z;
	}
}

void Dictionary::next() {
	if(!hasCurrent()) {
		throw std::logic_error("Dictionary: next: current undefined");
	}
	Node* z = findNext(this->current);
	if(z == nil) {
		this->current = nil;
		return;
	}
	else {
		this->current = z;
		return;
	}
}

void Dictionary::prev() {
	if(!hasCurrent()) {
		throw std::logic_error("Dictionary: prev: current undefined");
	}
	Node* z = findPrev(this->current);
	if(z == nil) {
		this->current = nil;
		return;
	}
	else { 
		this->current = z;
		return;
	}
}

std::string Dictionary::to_string() const {
	std::string S = "";
	inOrderString(S, this->root);
	return S;
}

std::string Dictionary::pre_string() const {
	std::string S = "";
	preOrderString(S, this->root);
	return S;
}

bool Dictionary::equals(const Dictionary& D) const {
	std::string s1 = "";
	std::string s2 = "";

	s1 = to_string();
	s2 = D.to_string();

	int res = s1.compare(s2);
	if(!res) {
		return true;
	}
	else {
		return false;
	}
}

//Helper Functions
void Dictionary::transplant(Node* u, Node* v) {
	if(u->parent == nil) {
		this->root = v;
	}
	else if(u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	if(v != nil) {
		v->parent = u->parent;
	}
}
void Dictionary::inOrderString(std::string& s, Node* R) const {
	if(R != this->nil) {
		inOrderString(s, R->left);
		s += R->key;
		s += " : ";
		s += std::to_string(R->val);
		s += "\n";
		inOrderString(s, R->right);
	}
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
	if(R != nil) {
		s += R->key;
		s += "\n";
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
	if(R == N) {
		return;
	}
	setValue(R->key, R->val);
	preOrderCopy(R->left, N);
	preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node* R) {
	if(R == nil) {
		return;
	}

	postOrderDelete(R->left);
	postOrderDelete(R->right);

	delete(R);
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	if(R == nil || R->key == k) {
		return R;
	}
	else if(k < R->key) {
		Node* temp = Dictionary::search(R->left, k);
		return temp;
	}
	else {
		Node* temp = Dictionary::search(R->right, k);
		return temp;
	}
}

Dictionary::Node* Dictionary::findMin(Node* R) {
	while(R->left != nil) {
		R = R->left;
	}
	return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
	while(R->right != nil) {
		R = R->right;
	}
	return R;
}

Dictionary::Node* Dictionary::findNext(Node* R) {
	if(R->right != nil) {
		return findMin(R->right);
	}
	Node* x = R->parent;
	while(R != nil && R == x->right) {
		R = x;
		x = x->parent;
	}
	return x;
}

Dictionary::Node* Dictionary::findPrev(Node* R) {
	if(R->left != nil) {
		return findMax(R->left);
	}
	Node* x = R->parent;
	while(R != nil && R == x->left) {
		R = x;
		x = x->parent;
	}
	return x;
}

std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
	return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
	return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ) {
	if(this != &D) {
		Dictionary temp = D;

		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.root);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this;
}

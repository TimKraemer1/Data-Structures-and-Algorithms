//Tim Kraemer
//CruzID: tikraeme
//pa8

#include <iostream>
#include <string>
#include <stdexcept>

#include "Dictionary.h"

enum color {RED, BLACK};

//Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = BLACK;
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
		else if(k > x->key) {
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
	z->color = RED;
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
	RB_InsertFixUp(z);
}	

void Dictionary::remove(keyType k) {
	if(!contains(k)) {
		throw std::logic_error("Dictionary: remove: key does not exist");
	}
	Node* z = search(root, k);
	if(z == current) {
		current = nil;
	}
	RB_Delete(z);
	delete(z);
	z = nullptr;
	num_pairs--;
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

void Dictionary::LeftRotate(Node* N) {
	Node* y = N->right;
	
	N->right = y->left;
	if(y->left != nil) {
		y->left->parent = N;
	}

	y->parent = N->parent;
	if(N->parent == nil) {
		root = y;
	}
	else if(N == N->parent->left) {
		N->parent->left = y;
	}
	else {
		N->parent->right = y;
	}

	y->left = N;
	N->parent = y;
}

void Dictionary::RightRotate(Node* N) {
	Node* y = N->left;

	N->left = y->right;
	if(y->right != nil) {
		y->right->parent = N;
	}

	y->parent = N->parent;
	if(N->parent == nil) {
		root = y;
	}
	else if(N == N->parent->right) {
		N->parent->right = y;
	}
	else {
		N->parent->left = y;
	}

	y->right = N;
	N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N) {
	Node* y;
	while(N->parent->color == RED){
		if(N->parent == N->parent->parent->left){
			y = N->parent->parent->right;
			if(y->color == RED){
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			}
			else { 
				if(N == N->parent->right){
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				RightRotate(N->parent->parent);
			}
		}
		else { 
			y = N->parent->parent->left;
			if(y->color == RED){
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			}
			else{ 
				if(N == N->parent->left){
					N = N->parent;
					RightRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				LeftRotate(N->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
	if(u->parent == nil){
		root = v;
	}
	else if(u == u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void Dictionary::RB_Delete(Node* N) {
	Node* y = N;
	Node* x;
	int y_color = y->color;
	if(N->left == nil){
		x = N->right;
		RB_Transplant(N, N->right);
	}
	else if(N->right == nil){
		x = N->left;
		RB_Transplant(N, N->left);
	}
	else {
		y = findMin(N->right);
		y_color = y->color;
		x = y->right;
		if(y->parent == N){
			x->parent = y;
		}
		else{
			RB_Transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y;
		}
		RB_Transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
		y->color = N->color;
	}
	if(y_color== BLACK){
		RB_DeleteFixUp(x);
	}
}

void Dictionary::RB_DeleteFixUp(Node* N) {
	Node* w;
	while(N != root && (N->color == BLACK)){
		if(N == N->parent->left){
			w = N->parent->right;
			if(w->color == RED){
				w->color = BLACK;
				N->parent->color = RED;
				LeftRotate(N->parent);
				w = N->parent->right;
			}
			if((w->left->color == BLACK) && (w->right->color == BLACK)){
				w->color = RED;
				N = N->parent;
			}
			else {
				if(w->right->color == BLACK){
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = N->parent->right;
				}
				w->color = N->parent->color;
				N->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(N->parent);
				N = root;
			}
		}
		else{
			w = N->parent->left;
			if(w->color == RED){
				w->color = BLACK;
				N->parent->color = RED;
				RightRotate(N->parent);
				w = N->parent->left;
			}
			if((w->right->color == BLACK) && (w->left->color == BLACK)){
				w->color = RED;
				N = N->parent;
			}
			else {
				if(w->left->color == BLACK){
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = N->parent->left;
				}
				w->color = N->parent->color;
				N->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(N->parent);
				N = root;
			}
		}
	}
	N->color = BLACK;
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

//Tim Kraemer
//CruzID: tikraeme
//pa5

#include<iostream>
#include<string>

#ifndef List_H_INCLUDE_
#define LIST_H_INCLUDE_

typedef int ListElement;

class List{
	private:
		//private Node struct
		struct Node{
			ListElement data;
			Node* next;
			Node* prev;
			//Node Constructor
			Node(ListElement x);
		};
		//List fields
		Node* frontDummy;
		Node* backDummy;
		Node* beforeCursor;
		Node* afterCursor;
		int pos_cursor;
		int num_elements;
	
	public:
		List();
		List(const List& L);
		~List();
		int length() const;
		ListElement front() const;
		ListElement back() const;
		ListElement position() const;
		ListElement peekNext() const;
		ListElement peekPrev() const;

		void clear();
		void moveFront();
		void moveBack();
		ListElement moveNext();
		ListElement movePrev();
		void insertAfter(ListElement x);
		void insertBefore(ListElement x);
		void setAfter(ListElement x);
		void setBefore(ListElement x);
		void eraseAfter();
		void eraseBefore();
		
		int findNext(ListElement x);
		int findPrev(ListElement x);
		void cleanup();
		List concat(const List& L) const;
		std::string to_string() const;
		bool equals(const List& R) const;

		friend std::ostream& operator<<( std::ostream& stream, const List& L);
		friend bool operator==(const List& A, const List& B);
		List& operator=(const List& L);
};

#endif

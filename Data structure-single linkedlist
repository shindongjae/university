#include <iostream>
#include <string>
using namespace std;

typedef string Elem;

class StringNode {
private:
	Elem elem;
	StringNode* next;

	friend class StringLinkedList;//b에서 a사용가능.
};

class StringLinkedList {
private:
	StringNode* head;
	StringNode* tail;
public:
	StringLinkedList();
	~StringLinkedList();
	bool empty() const;
	Elem front() const;
	void addFront(const Elem& e);
	void removeFront();
	void addBack(const Elem& e);
	void removeBack();
};

StringLinkedList::StringLinkedList() :head(nullptr),tail(nullptr) {}
StringLinkedList::~StringLinkedList() { while (!empty())removeFront(); }

bool StringLinkedList::empty() const 
{ return head == nullptr; }

Elem StringLinkedList::front() const
{ return head->elem;}


void StringLinkedList::addFront(const Elem& e) {
	StringNode* v = new StringNode;
	if (empty()) {
		tail = v;
	}
	v->elem = e;
	v->next = head;
	head = v;
}

void StringLinkedList::removeFront() {
	if (empty())
		return;
	StringNode* old = head;
	head = old->next;
	delete old;
	if (empty())
		tail = nullptr;
}

void StringLinkedList::addBack(const Elem& e) {
	StringNode* v = new StringNode;
	v->elem = e;
	v->next = nullptr;
	if (empty())
		head = tail = v;
	else {
		tail->next = v;
		tail = v;
	}	
}

void StringLinkedList::removeBack() {
	if (empty()) return;
	StringNode* current = head;
	if (current == tail) {
		head = tail = nullptr;
		delete current;
	}
	else {
		while (current->next != tail) {
			current = current->next;
		}
		tail = current;
		delete tail->next;
		tail->next = nullptr;
	}
}

int main() {}

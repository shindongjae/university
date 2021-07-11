#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node(int i) { data = i;next = nullptr; }
	friend class Slinkedlist;
};

class SlinkedList {
public:
	Node* head;
	
	SlinkedList() { head = nullptr; }
	void addFront(int X) {
		Node* tmp = new Node(X);
		if (head == nullptr)
			head = tmp;
		else
		{
			tmp->next = head;
			head = tmp;
		}
	}

	void removeFront() {
		if (head == nullptr)
			cout << -1 << endl;
		else if (head->next == nullptr) {
			cout << head->data<<endl;
			head=nullptr;
		}
		else
		{
			Node* tmp = head;
			cout << tmp->data << endl;
			head = head->next;
			delete tmp;
		}
	}

	void front() {
		if (head == nullptr)
			cout << -1 << endl;
		else
			cout << head->data << endl;
	}

	void empty() {
		if (head == nullptr)
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}

	void showList() {
		if (head == nullptr) {
			cout << -1 << endl;
		}
		else
		{
			Node* tmp = head;
			while (tmp != nullptr) {
				cout << tmp->data << ' ';
				tmp = tmp->next;
			}
			cout << endl;
		}
	}
	
	void addBack(int X) {
		Node* tmp = new Node(X);
		if (head == nullptr)
			head = tmp;
		else
		{
			Node* x = head;
			while (x->next != nullptr) {
				x = x->next;
			}
			x->next = tmp;
		}
	}
	
};

int main() {
	int N;
	cin >> N;
	string str;
	SlinkedList slist;
	while (N--) {
		cin >> str;
		if (str == "showList") {
			slist.showList();
		}
		if (str == "empty") {
			slist.empty();
		}
		if (str == "addFront")
		{
			int n;
			cin >> n;
			slist.addFront(n);
		}
		if (str == "addBack") {
			int n;
			cin >> n;
			slist.addBack(n);
		}
		if (str == "removeFront") {
			slist.removeFront();
		}
		if (str == "front") {
			slist.front();
		}
	}
}

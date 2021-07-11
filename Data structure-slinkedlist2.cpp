#include <iostream>

using namespace std;

class Node {
public:
	int data;
	Node* next;

	Node(int e) {
		this->data = e;
		this->next = nullptr;
	}
};

class SLinkedList {
public:
	Node* head;
	Node* tail;

	SLinkedList() {
		head = nullptr;
		tail = nullptr;
	}


	void showList() {
		Node* tmp = head;

	
		cout << tmp->data << ' ';
		do {
			tmp = tmp->next;
			cout << tmp->data << ' ';
		} while (tmp != tail);
		cout << endl;
	}

	void addBack(int X) {
		Node* tmp = tail;
		Node* node = new Node(X);
		if (head == nullptr) {
			head = node;
			tail = node;
			tail->next = head;
			return;
		}
		tmp->next = node;
		tail = node;
		tail->next = head;
	}

	void Delete(int X) {
		Node* tmp = head;
		for (int i = 0;i < X - 1;i++)
		{
			tmp = tmp->next;
		}
		if (X == 0) {
			head = head->next;
			tail->next = head;
		}

		else if (tmp->next == head) {
			Node* tmptmp = tmp->next;
			tmp->next = tmp->next->next;
			delete tmptmp;
			head = tmp->next;
		}

		else if (tmp->next == tail) {
			Node* tmptmp = tmp->next;
			tmp->next = tmp->next->next;
			delete tmptmp;
			tail = tmp;
		}
		else
		{
			Node* tmptmp = tmp->next;
			tmp->next = tmp->next->next;
			delete tmptmp;
		}
	}
	bool empty() {
		return head == nullptr;
	}
};

int main() {

	int n, t;
	string str;


	cin >> n;
	while (n--) {
		SLinkedList list;
		for (int i = 0;i < 10;i++) {
			cin >> t;
			list.addBack(t);
		}
		for (int j = 0;j < 3;j++) {
			cin >> str;
			if (str == "Delete")
			{
				cin >> t;
				list.Delete(t);
			}
		}
		list.showList();
		list.head = nullptr;
		list.tail = nullptr;
	}
}

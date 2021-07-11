#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
	int data;
	Node* par;
	Node* lchi;
	Node* rchi;

	Node(int x) {
		data = x;
		par = nullptr;
		lchi = nullptr;
		rchi = nullptr;
	}
};

class BST {
public:
	Node* root;
	int height;

	BST() {
		root = nullptr;
		height = 0;
	}

	~BST() { this->treeDestructor(this->root);}

	void treeDestructor(Node* root) {
		if (root == nullptr)
			return;
		if (root->lchi != nullptr)
			this->treeDestructor(root->lchi);
		if (root->rchi != nullptr)
			this->treeDestructor(root->rchi);
		delete(root);
	}

	void insertNode(int data) {
		if (root == nullptr)
			root = new Node(data);
		else {
			Node* tmp = root;
			while (1) {
				if (tmp->lchi != nullptr && tmp->rchi != nullptr) {
					if (data < tmp->data)
						tmp = tmp->lchi;
					else if (data > tmp->data)
						tmp = tmp->rchi;
				}
				else if (tmp->lchi == nullptr && tmp->rchi == nullptr) {
					if (data < tmp->data) {
						tmp->lchi = new Node(data);
						tmp->lchi->par = tmp;
						break;
					}
					else if (data > tmp->data) {
						tmp->rchi = new Node(data);
						tmp->rchi->par = tmp;
						break;
					}
				}
				else if (tmp->lchi == nullptr) {
					if (data < tmp->data) {
						tmp->lchi = new Node(data);
						tmp->lchi->par = tmp;
						break;
					}
					else if (data > tmp->data)
						tmp = tmp->rchi;
				}
				else if (tmp->rchi == nullptr) {
					if (data < tmp->data)
						tmp = tmp->lchi;
					else if (data > tmp->data) {
						tmp->rchi = new Node(data);
						tmp->rchi->par = tmp;
						break;
					}
				}
			}
		}
	}

	void search(int data) {
		int depth = 0;
		Node* tmp = root;
		while (1) {
			if (data < tmp->data)
			{	
				if (tmp->lchi == nullptr) {
					cout << 0 << endl;
					return;
				}
				tmp = tmp->lchi;
				depth++;
			}
			else if (data > tmp->data) {
				if (tmp->rchi == nullptr) {
					cout << 0 << endl;
					return;
				}
				tmp = tmp->rchi;
				depth++;
			}
			if (tmp->data == data) {
				int child = 0;
				if (tmp->lchi != nullptr)
					child++;
				if (tmp->rchi != nullptr)
					child++;
				cout << child << ' '<< depth<<endl;
				return;
			}
		}
	}

	void setheight(Node *node,int h) {
		if (node->lchi != nullptr) {
			setheight(node->lchi, h + 1);
		}
		if (node->rchi != nullptr) {
			setheight(node->rchi, h + 1);
		}
		if (node->lchi == nullptr && node->rchi == nullptr) {
			if (h > height)
				height = h;
			return;
		}
	}
};

int main() {
	int T;
	cin >> T;
	while (T--) {
		BST* bst = new BST;
		int N, t;
		cin >> N;
		for (int i = 0;i < N;i++) {
			cin >> t;
			bst->insertNode(t);
		}
		bst->setheight(bst->root,0);
		cout << bst->height << endl;
		delete bst;
	}
}

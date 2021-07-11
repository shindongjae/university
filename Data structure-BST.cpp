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

	~BST() { this->treeDestructor(this->root); }

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

	Node* search(int data) {
		int depth = 0;
		Node* tmp = root;
		while (1) {
			if (data < tmp->data)
			{
				if (tmp->lchi == nullptr) {
					cout << 0 << endl;
					return nullptr;
				}
				tmp = tmp->lchi;
				depth++;
			}
			else if (data > tmp->data) {
				if (tmp->rchi == nullptr) {
					cout << 0 << endl;
					return nullptr;
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

				return tmp;
			}
		}
	}


	void setheight(Node* node, int h) {
		if (node->lchi != nullptr) {
			node = node->lchi;
			setheight(node, h + 1);
		}
		if (node->rchi != nullptr) {
			node = node->rchi;
			setheight(node, h + 1);
		}
		if (node->lchi == nullptr && node->rchi == nullptr) {
			if (h > height)
				height = h;
			return;
		}
	}

	void preorder(Node* node) {
		cout << node->data << ' ';
		if (node->lchi != nullptr)
			preorder(node->lchi);
		if (node->rchi != nullptr)
			preorder(node->rchi);
	}

};

void Transplant(BST* t, Node* u, Node* v) {
	if (u->par == nullptr)
		t->root = v;
	else if (u == u->par->lchi)
		u->par->lchi = v;
	else
		u->par->rchi = v;
	if (v != nullptr)
		v->par = u->par;
}

void Delete(BST* t, Node* z) {
	if (z->lchi == nullptr)
		Transplant(t, z, z->rchi);
	else if (z->rchi == nullptr)
		Transplant(t, z, z->lchi);
	else {
		Node* y = z->rchi;
		while (y->lchi != nullptr)
			y = y->lchi;
		if (y->par != z) {
			Transplant(t, y, y->rchi);
			y->rchi = z->rchi;
			y->rchi->par = y;
		}
		Transplant(t, z, y);
		y->lchi = z->lchi;
		y->lchi->par = y;
	}
	delete z;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		BST* bst = new BST;
		int N, t, M;
		cin >> N;
		for (int i = 0;i < N;i++) {
			cin >> t;
			bst->insertNode(t);
		}
		cin >> M;
		for (int i = 0;i < M;i++) {
			cin >> t;
			Delete(bst, bst->search(t));
		}

		bst->preorder(bst->root);
		cout << endl;
		delete bst;
	}
}

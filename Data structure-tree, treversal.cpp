#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
	int data;
	Node* par;
	vector<Node*> chi;

	Node() {
		data = NULL;
		par = nullptr;
	}

	Node(int X) {
		data = X;
		par = nullptr;
	}
};


class Tree {
public:
	Node* root;
	vector<Node*> node_list;

	Tree() {
		root = new Node(1);
		node_list.push_back(root);
	}

	void insert(int X, int Y) {
		Node* tmp = nullptr;
		for (int i = 0;i < node_list.size();i++) {
			if (node_list[i]->data == X) {
				tmp = node_list[i];
			}
		}
		if (tmp == nullptr) {
			cout << -1 << endl;
			return;
		}

		Node* x = new Node(Y);
		node_list.push_back(x);
		tmp->chi.push_back(x);
		x->par = tmp;
	}

	void printChild(int X) {
		Node* tmp = nullptr;
		for (int i = 0;i < node_list.size();i++) {
			if (node_list[i]->data == X)
				tmp = node_list[i];
		}
		if (tmp == nullptr) {
			cout << -1 << endl;
			return;
		}
		if (tmp->chi.size() == 0) {
			cout << 0 << endl;
			return;
		}

		for (int j = 0;j < tmp->chi.size();j++)
			cout << tmp->chi[j]->data << ' ';
		cout << endl;
	}


	void printDepth(int X) {
		Node* tmp = nullptr;
		for (int i = 0;i < node_list.size();i++) {
			if (node_list[i]->data == X)
				tmp = node_list[i];
		}
		if (tmp == nullptr) {
			cout << -1 << endl;
			return;
		}

		int depth = 0;
		while (tmp->par != nullptr) {
			depth++;
			tmp = tmp->par;
		}
		cout << depth;
	}

	void printlist() {
		for (int i = 0;i < node_list.size();i++)
			cout << node_list[i]->data << ' ';
		cout << endl;
	}

	void height() {
		int height = 0;
		for (int i = 0;i < node_list.size();i++) {
			int tmp = 0;
			while (node_list[i]->par != nullptr) {
				tmp++;
				node_list[i] = node_list[i]->par;
			}
			if (height < tmp)
				height = tmp;
		}
		cout << height << endl;
	}

	void preorder(Node* node) {
		cout << node->data << ' ';
		for (int i = 0;i < node->chi.size();i++)
			preorder(node->chi[i]);
	}

	void postorder(Node* node) {
		for (int i = 0;i < node->chi.size();i++)
			postorder(node->chi[i]);
		cout << node->data << ' ';
	}
};

int main() {
	int N;
	cin >> N;

	string str;

	while (N--) {
		Tree* t = new Tree();
		int M;
		cin >> M;
		while (M--) {
			int x, y;
			cin >> x >> y;
			t->insert(x, y);
		}
		t->preorder(t->root);
		cout << endl;
		t->postorder(t->root);
		cout << endl;
		t->height();
		delete t;
	}
}

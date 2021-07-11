#include <iostream>
#include <string>

using namespace std;

class arrayStack {
public:
	int* S;
	int capacity;
	int t;

	arrayStack(int capacity) {
		this->capacity = capacity;
		this->S = new int[capacity];
		this->t = -1;
	}

	void empty() {
		if (t == -1)cout << 1<<endl;
		else
			cout << 0 << endl;
	}

	void top() {
		if (t == -1)
			cout << -1 << endl;
		else
			cout << S[t]<<endl;
	}

	void push(int x) {
		if (t == capacity)
			cout << -1;
		else {
			t++;
			S[t] = x;
		}
	}

	void pop() {
		if (t == -1)
			cout << -1<<endl;
		else {
			cout << S[t]<<endl;
			t--;
		}
	}

	void size() {
		cout << t + 1 << endl;
	}
};

int main() {
	arrayStack s(100000);
	int n;
	cin >> n;
	string str;
	while (n--) {
		cin >> str;
		if (str == "empty") {
			s.empty();
		}
		if (str == "top") {
			s.top();
		}
		if (str == "push") {
			int t;
			cin >> t;
			s.push(t);
		}
		if (str == "pop") {
			s.pop();
		}
		if (str == "size") {
			s.size();
		}
	}
}

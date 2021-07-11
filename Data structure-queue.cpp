#include <iostream>
#include <string>

using namespace std;

class arrQueue {
public:
	int* arr;
	int capacity;
	int f;
	int r;

	arrQueue(int size) {
		arr = new int[size + 1];
		capacity = size + 1;
		f = 0;
		r = -1;
	}

	void enqueue(int X) {
		if (r == -1)
		{
			arr[f] = X;
			r = f;
		}
		else if ((r - f + 1 + capacity) % capacity == capacity - 1) {
			cout << "Full" << endl;
		}
		else {
			r = (r + 1) % capacity;
			arr[r] = X;
		}
	}

	void dequeue() {
		if (r == -1) {
			cout << "Empty" << endl;
		}
		else if (f == r) {
			cout << arr[f] << endl;
			r = -1;
		}
		else {
			cout << arr[f] << endl;
			f = (f + 1) % capacity;
		}
	}

	void size() {
		if (r == -1)
			cout << 0 << endl;
		else
			cout << (r - f + 1 + capacity) % capacity << endl;
	}

	void isEmpty() {
		if (r == -1)
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}

	void front() {
		if (r == -1) {
			cout << "Empty" << endl;
		}
		else
			cout << arr[f] << endl;
	}

	void rear() {
		if (r == -1) {
			cout << "Empty" << endl;
		}
		else
			cout << arr[r] << endl;
	}
};


int main() {
	int S;
	cin >> S;

	arrQueue aq(S);

	int N;
	cin >> N;

	string str;
	while (N--) {
		cin >> str;

		if (str == "isEmpty") {
			aq.isEmpty();
		}
		else if (str == "size") {
			aq.size();
		}
		else if (str == "enqueue") {
			int t;
			cin >> t;
			aq.enqueue(t);
		}
		else if (str == "dequeue") {
			aq.dequeue();
		}
		else if (str == "front") {
			aq.front();
		}
		else if (str == "rear") {
			aq.rear();
		}
	}
}

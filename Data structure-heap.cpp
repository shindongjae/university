#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b) {
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}

class Heap {
public:
	vector<int> v;
	int size;

	Heap() {
		v.push_back(-1);
		size = 0;
	}


	void print() {
		if (v.size() == 1)
			cout << -1 << endl;
		else
			for (int i = 1;i <= size;i++)
				cout << v[i] << ' ';
		cout << endl;
	}

	void top() {
		if (size == 0)
			cout << -1 << endl;
		else
			cout << v[1] << endl;
	}
};

class MinHeap : public Heap {
public:
	void insert(int e) {
		size++;
		v.push_back(e);
		int index = size;
		while (index != 1) {
			if (v[index / 2] > v[index]) {
				swap(v[index / 2], v[index]);
			}
			index /= 2;
		}
	}

	bool pop() {
		if (size == 0)
			return false;
		else {
			v[1] = v[size];
			size--;
			v.pop_back();
			int index = 1;
			while (1) {
				int a = 99, b = 99;
				if ((index * 2 <= size) && (v[index] >= v[index * 2]))
					a = v[index * 2];
				if ((index * 2 + 1 <= size) && (v[index] >= v[index * 2 + 1]))
					b = v[index * 2 + 1];

				if ((a != 99) && (b != 99)) {
					if (a <= b) {
						swap(v[index], v[index * 2]);
						index = index * 2;
					}
					else
					{
						swap(v[index], v[index * 2 + 1]);
						index = index * 2 + 1;
					}
				}
				else if (a != 99 && b == 99) {
					swap(v[index], v[index * 2]);
					index *= 2;
				}
				else if (a == 99 && b != 99) {
					swap(v[index], v[index * 2 + 1]);
					index = index * 2 + 1;
				}
				else
					break;
			}
		}
		return true;
	}
};

class MaxHeap :public Heap {
public:
	void insert(int e) {
		size++;
		v.push_back(e);
		int index = size;
		while (index != 1) {
			if (v[index / 2] < v[index]) {
				swap(v[index / 2], v[index]);
			}
			index /= 2;
		}
	}

	bool pop() {
		if (size == 0)
			return false;
		else {
			v[1] = v[size];
			size--;
			v.pop_back();
			int index = 1;
			while (1) {
				int a = 99, b = 99;
				if ((index * 2 <= size) && (v[index] <= v[index * 2]))
					a = v[index * 2];
				if ((index * 2 + 1 <= size) && (v[index] <= v[index * 2 + 1]))
					b = v[index * 2 + 1];

				if ((a != 99) && (b != 99)) {
					if (a >= b) {
						swap(v[index], v[index * 2]);
						index = index * 2;
					}
					else
					{
						swap(v[index], v[index * 2 + 1]);
						index = index * 2 + 1;
					}
				}
				else if (a != 99 && b == 99) {
					swap(v[index], v[index * 2]);
					index *= 2;
				}
				else if (a == 99 && b != 99) {
					swap(v[index], v[index * 2 + 1]);
					index = index * 2 + 1;
				}
				else
					break;
			}
		}
		return true;
	}
};

int main() {
	int T;
	cin >> T;

	int N, p, k;
	string str;
	MinHeap minheap;
	MaxHeap maxheap;

	while (T--) {
		cin >> N >> p;
		while (N--) {
			cin >> k;
			minheap.insert(k);
			maxheap.insert(k);
		}
		cout << minheap.v[p] << endl;
		for (int i = 0;i < p - 1;i++) {
			minheap.pop();
		}
		minheap.top();
		
		cout << maxheap.v[p] << endl;
		for (int i = 0;i < p - 1;i++) {

			maxheap.pop();
		}
		maxheap.top();

		while (minheap.pop()) {}
		while (maxheap.pop()) {}
	}
}

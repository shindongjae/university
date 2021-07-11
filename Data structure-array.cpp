#include iostream
#include string

using namespace std;

class Array {
public
	int n;
	int* arr;

	Array(int size) {
		this-n = 0;
		this-arr = new int[size];
		for (int i = 0;i  size;i++) {
			arr[i] = 0;
		}
	}

	void at(int idx) {
		if (arr[idx] == 0)
			cout  0  endl;
		else
			cout  arr[idx]  endl;
	}

	void set(int idx, int X) {
		if (arr[idx] != 0) {
			arr[idx] = X;
		}
		else
			cout  0  endl;
	}

	void add(int idx, int num) {
		if (arr[idx] == 0  n == 0)
			arr[n] = num;
		else
		{
			for (int i = n;i  idx;i--)
				arr[i] = arr[i - 1];
			arr[idx] = num;
		}
		n++;
	}

	void remove(int idx) {
		if (arr[idx] == 0) {
			cout  0;
		}
		else
		{
			cout  arr[idx];
			for (int i = idx;i  n;i++)
				arr[i] = arr[i + 1];
			arr[n] = 0;
			n--;
		}
		cout  endl;
	}

	void printArray() {
		if (arr[0] == 0)
			cout  0;
		else
			for (int i = 0;i  n;i++)
				stdcout  arr[i]  ' ';
		cout  endl;
	}
};

int main() {
	int M;
	Array a(10000);
	cin  M;

	string str;

	while (M--) {
		cin  str;
		if (str == at) {
			int x;
			cin  x;
			a.at(x);
		}

		if (str == set) {
			int x, y;
			cin  x  y;
			a.set(x, y);
		}

		if (str == add) {
			int x, y;
			cin  x  y;
			a.add(x, y);
		}

		if (str == remove) {
			int x;
			cin  x;
			a.remove(x);
		}

		if (str == printArray) {
			a.printArray();
		}
	}
}

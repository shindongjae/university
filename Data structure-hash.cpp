#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAX 353333
#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

class cell {
public:
	int value;
	int status;

	cell() { value = 0; status = NOITEM; }
};

int hashfunc(int idx) {
	return idx % MAX;
}

int hashfunc2(int idx) {
	return (17 - (idx % 17));
}

vector<cell> arr(MAX);

void insert(int val) {
	int hval,hval2;
	hval = hashfunc(val);
	hval2 = hashfunc2(val);
	while (arr[hval].status == ISITEM) {
		hval = hashfunc(hval+hval2);
	}
	arr[hval].value = val;
	arr[hval].status = ISITEM;
}

void probe(int val) {
	int count = 1;	
	int key = hashfunc(val);
	int key2 = hashfunc2(val);
	
	while (arr[key].value != val && arr[key].status == ISITEM) {
		count++;
		key = hashfunc(key+key2);
	}

	if (arr[key].value == val)
		cout << 1 << ' ' << count << endl;
	else
		cout << 0 << ' ' << count << endl;
}


int main() {
	int T;
	cin >> T;

	while (T--) {
		int M,N, t;
		cin >> N;
		for (int i = 0;i < N;i++) {
			cin >> t;
			insert(t);
		}

		cin >> M;
		for (int i = 0;i < M;i++) {
			cin >> t;
			probe(t);
		}

		for (int i = 0;i < MAX;i++) {
			arr[i].status = NOITEM;
			arr[i].value = 0;
		}
	}
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class graph {
public:
	int** arr;
	int N;

	graph(int x) {
		N = x;

		arr = new int* [N + 1];
		for (int i = 0;i < N + 1;i++)
			arr[i] = new int[N + 1];

		for (int i = 0;i < N + 1;i++)
			for (int j = 0;j < N + 1;j++)
				arr[i][j] = 0;
	}

	void addvertex(int n,int i) {
		arr[0][i] = n;
		arr[i][0] = n;
	}

	int find(int x) {
		for (int i = 1;i <= N;i++) {
			if (arr[0][i] == x)
				return i;
		}
		return -1;
	}

	int isadjacent(int x, int y) {
		int a = find(x);
		int b = find(y);

		if (a == -1 || b == -1)
			return -1;
		else if (arr[a][b] == 1)
			return 1;
		return 0;
	}

};

int main() {
	int N, M,l,a,b,K;
	int tmpa, tmpb;
	cin >> N>>M>>K;
	int count = 0;
	graph g(N);
	

	for (int i = 1;i <= N;i++) {
		cin >> l;
		g.addvertex(l, i);
	}
		
	
	while(M--) {
		cin >> a >> b;
		tmpa = g.find(a); 
		tmpb = g.find(b);

		if (tmpa == -1 || tmpb == -1) {
			cout << -1 << endl;
		}
		else if (g.arr[tmpa][tmpb] == 1) {
			cout << -1 << endl;
		}
		else {
			g.arr[tmpa][tmpb] = 1;
			g.arr[tmpb][tmpa] = 1;
			count++;
		}
	}

	cout << N << ' ' << count << endl;

	while (K--) {
		cin >> a >> b;
		cout << g.isadjacent(a, b) << endl;
	}
}

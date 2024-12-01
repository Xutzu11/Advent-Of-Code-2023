#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

char mat[1005][1005];
int n, m;
long long tot;
char last[1005][105][105];
int cycles;
bool found;
int tip;

void move(int i, int j, int ki, int kj) {
	if (i+ki < 0 || j+kj < 0 || i+ki >= n || j+kj >= m) return;
	if (mat[i + ki][j + kj] != '.') return;
	mat[i + ki][j + kj] = 'O';
	mat[i][j] = '.';
	move(i + ki, j + kj, ki, kj);
}

void compare() {
	bool dif = 0;
	for (int k = 0; k <= cycles; k++) {
		dif = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (last[k][i][j] != mat[i][j]) dif = 1;
				if (k == cycles) last[k][i][j] = mat[i][j];
			}
		}
		if (dif == 0) {
			found = 1;
			tip = k;
		}
	}
}

void show() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			g << mat[i][j];
		}
		g << '\n';
	}
	g << '\n';
}

int main() {
	while (f.getline(mat[n], 1000)) n++;
	m = strlen(mat[0]);
	found = 0;
	while (!found) {
		compare();
		if (found) break;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (mat[i][j] == 'O') move(i, j, -1, 0);
			}
		}
		for (int j = 0; j < m; j++) {
			for (int i = 0; i < n; i++) {
				if (mat[i][j] == 'O') move(i, j, 0, -1);
			}
		}
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j < m; j++) {
				if (mat[i][j] == 'O') move(i, j, 1, 0);
			}
		}
		for (int j = m - 1; j >= 0; j--) {
			for (int i = 0; i < n; i++) {
				if (mat[i][j] == 'O') move(i, j, 0, 1);
			}
		}
		cycles++;
	}
	int rest = (1000000000-cycles) % (cycles - tip);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			mat[i][j] = last[tip + rest][i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == 'O') tot += n - i;
		}
	}
	g << tot << " " << cycles;
	return 0;
}

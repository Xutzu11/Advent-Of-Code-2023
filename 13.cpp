#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

ifstream f("aoc.in");
ofstream g("aoc.out");

char mat[1005][1005];
int n, m;
long long tot;
int tip, line;
bool ok;

bool check_line(int i1, int i2) {
	if (i1 < 0 || i2 >= n) return 1;
	for (int j = 0; j < m; j++) {
		if (mat[i1][j] != mat[i2][j]) return 0;
	}
	return check_line(i1 - 1, i2 + 1);
}

bool check_column(int j1, int j2) {
	if (j1 < 0 || j2 >= m) return 1;
	for (int i = 0; i < n; i++) {
		if (mat[i][j1] != mat[i][j2]) return 0;
	}
	return check_column(j1 - 1, j2 + 1);
}

bool check_newcolumn(int j1, int j2, int k) {
	if (j1 < 0 || j2 >= m) {
		if (k <= 1) return 1;
		else return 0;
	}
	for (int i = 0; i < n; i++) {
		if (mat[i][j1] != mat[i][j2]) k++;
	}
	return check_newcolumn(j1 - 1, j2 + 1, k);
}

bool check_newline(int i1, int i2, int k) {
	if (i1 < 0 || i2 >= n) {
		if (k <= 1) return 1;
		else return 0;
	}
	for (int j = 0; j < m; j++) {
		if (mat[i1][j] != mat[i2][j]) k++;
	}
	return check_newline(i1 - 1, i2 + 1, k);
}

int main() {
	while (1) {
		n = 0; m = 0;
		while (1) {
			f.getline(mat[n], 1000);
			if (mat[n][0] == 0) break;
			n++;
		}
		if (n == 0) break;
		m = strlen(mat[0]);
		ok = 0;
		for (int i = 0; i < n - 1 && !ok; i++) {
			if (check_line(i, i + 1)) {
				tip = 1;
				line = i;
				ok = 1;
			}
		}
		for (int j = 0; j < m - 1 && !ok; j++) {
			if (check_column(j, j + 1)) {
				tip = 2;
				line = j;
				ok = 1;
			}
		}
		ok = 0;
		for (int i = 0; i < n - 1 && !ok; i++) {
			if (check_newline(i, i + 1, 0) && (tip != 1 || line != i)) {
				tip = 1;
				line = i;
				ok = 1;
			}
		}
		for (int j = 0; j < m - 1 && !ok; j++) {
			if (check_newcolumn(j, j + 1, 0) && (tip != 2 || line != j)) {
				tip = 2;
				line = j;
				ok = 1;
			}
		}
		if (tip == 2) tot += line + 1;
		else tot += 100 * (line + 1);
	}
	g << tot;
	return 0;
}

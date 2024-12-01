#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

char mat[1005][1005];
int n, m, ctr;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; /// 0 1 2 3
/// 0 = nord, 1 = dreapta, 2 = sud, 3 = st
int mx1[4] = { 0, -1, 0, 1 }, my1[4] = { 1, 0, -1, 0 }, d1[4] = { 1, 0, 3, 2 }; /// for mirror /
int mx2[4] = { 0, 1, 0, -1 }, my2[4] = { -1, 0, 1, 0 }, d2[4] = { 3, 2, 1, 0 }; /// for mirror \

int maxviz;
int viz[1005][1005][5];
struct Beam {
	int x, y, dir;
};
queue < Beam > q;

Beam newbeam(int x, int y, int dir) {
	Beam a;
	a.x = x; a.y = y; a.dir = dir;
	return a;
}

bool valid(int x, int y, int dir) {
	if (x < 0 || y < 0 || x >= n || y >= m) return 0;
	if (viz[x][y][dir]) return 0;
	viz[x][y][dir] = 1;
	return 1;
}

void bfs() {
	while (!q.empty())
	{
		Beam nod = q.front();
		q.pop();
		if (mat[nod.x][nod.y] == '.') {
			if (nod.dir == 0 || nod.dir == 2) {
				viz[nod.x][nod.y][0] = 0;
				viz[nod.x][nod.y][2] = 2;
			}
			else {
				viz[nod.x][nod.y][1] = 1;
				viz[nod.x][nod.y][3] = 3;
			}
			if (valid(nod.x + dx[nod.dir], nod.y + dy[nod.dir], nod.dir)) {
				q.push(newbeam(nod.x + dx[nod.dir], nod.y + dy[nod.dir], nod.dir));
			}
		}
		else if (mat[nod.x][nod.y] == '/') {
			if (nod.dir == 0 || nod.dir == 3) {
				viz[nod.x][nod.y][0] = 0;
				viz[nod.x][nod.y][3] = 3;
			}
			else {
				viz[nod.x][nod.y][1] = 1;
				viz[nod.x][nod.y][2] = 2;
			}
			if (valid(nod.x + mx1[nod.dir], nod.y + my1[nod.dir], d1[nod.dir])) {
				q.push(newbeam(nod.x + mx1[nod.dir], nod.y + my1[nod.dir], d1[nod.dir]));
			}
		}
		else if (mat[nod.x][nod.y] == '\\') {
			if (nod.dir == 0 || nod.dir == 1) {
				viz[nod.x][nod.y][0] = 0;
				viz[nod.x][nod.y][1] = 1;
			}
			else {
				viz[nod.x][nod.y][2] = 2;
				viz[nod.x][nod.y][3] = 3;
			}
			if (valid(nod.x + mx2[nod.dir], nod.y + my2[nod.dir], d2[nod.dir])) {
				q.push(newbeam(nod.x + mx2[nod.dir], nod.y + my2[nod.dir], d2[nod.dir]));
			}
		}
		else if (mat[nod.x][nod.y] == '-') {
			if (nod.dir == 1 || nod.dir == 3) {
				viz[nod.x][nod.y][1] = 3;
				viz[nod.x][nod.y][3] = 3;
				if (valid(nod.x + dx[nod.dir], nod.y + dy[nod.dir], nod.dir)) {
					q.push(newbeam(nod.x + dx[nod.dir], nod.y + dy[nod.dir], nod.dir));
				}
			}
			else {
				viz[nod.x][nod.y][0] = 0;
				viz[nod.x][nod.y][2] = 2;
				if (valid(nod.x + dx[(nod.dir + 1) % 4], nod.y + dy[(nod.dir + 1) % 4], (nod.dir + 1) % 4)) {
					q.push(newbeam(nod.x + dx[(nod.dir + 1) % 4], nod.y + dy[(nod.dir + 1) % 4], (nod.dir + 1) % 4));
				}
				if (valid(nod.x + dx[(nod.dir+3)%4], nod.y + dy[(nod.dir+3)%4], (nod.dir+3)%4)) {
					q.push(newbeam(nod.x + dx[(nod.dir + 3) % 4], nod.y + dy[(nod.dir + 3) % 4], (nod.dir + 3) % 4));
				}
			}
		}
		else {
			if (nod.dir == 1 || nod.dir == 3) {
				viz[nod.x][nod.y][1] = 3;
				viz[nod.x][nod.y][3] = 3;
				if (valid(nod.x + dx[(nod.dir + 1) % 4], nod.y + dy[(nod.dir + 1) % 4], (nod.dir + 1) % 4)) {
					q.push(newbeam(nod.x + dx[(nod.dir + 1) % 4], nod.y + dy[(nod.dir + 1) % 4], (nod.dir + 1) % 4));
				}
				if (valid(nod.x + dx[(nod.dir + 3) % 4], nod.y + dy[(nod.dir + 3) % 4], (nod.dir + 3) % 4)) {
					q.push(newbeam(nod.x + dx[(nod.dir + 3) % 4], nod.y + dy[(nod.dir + 3) % 4], (nod.dir + 3) % 4));
				}
			}
			else {
				viz[nod.x][nod.y][0] = 0;
				viz[nod.x][nod.y][2] = 2;
				if (valid(nod.x + dx[nod.dir], nod.y + dy[nod.dir], nod.dir)) {
					q.push(newbeam(nod.x + dx[nod.dir], nod.y + dy[nod.dir], nod.dir));
				}
			}
		}
	}
}

void reset() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int d = 0; d < 4; d++) {
				viz[i][j][d] = 0;
			}
		}
	}
}

int current_viz() {
	int ctr = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (viz[i][j][0] || viz[i][j][1] || viz[i][j][2] || viz[i][j][3]) {
				ctr++;
			}
		}
	}
	return ctr;
}

int main()
{
	while (f >> mat[n]) {
		n++;
	}
	m = strlen(mat[0]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int d = 0; d < 4; d++) {
				if (i == 0 || j == 0 || i == n - 1 || j == n - 1) {
					reset();
					q.push(newbeam(i, j, d));
					viz[i][j][d] = 1;
					viz[i][j][(d + 2) % 4] = 1;
					bfs();
					maxviz = max(maxviz, current_viz());
				}
			}
		}
	}
	g << maxviz;
	return 0;
}

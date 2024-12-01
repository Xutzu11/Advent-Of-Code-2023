#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

char mat[205][205];
bool viz[205][205][4][11];
int dist[205][205][4][11];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };
int opdir[4] = { 2, 3, 0, 1 };
int x, y;
/// dir: 0 - nord, 1 - est, 2 - sud, 3 - vest
/// viz[x][y][dir][cons]
int n, m;

set < pair < int, pair < pair < int, int >, pair < int, int > > > > s;
/// {distance,  { {dir, cons}, {x,y} } }

bool valid(int x, int y, int cons, int newdir, int olddir) {
	if (newdir == opdir[olddir]) return 0;
	if (x < 0 || y < 0 || x >= n || y >= m) return 0;
	if (newdir == olddir) {
		if (cons > 10) return 0;
		if (viz[x][y][newdir][cons] == 1) return 0;
		viz[x][y][newdir][cons] = 1;
		return 1;
	}
	else {
		if (olddir == -1) return 1;
		if (cons < 5) return 0;
		if (viz[x][y][newdir][1] == 1) return 0;
		viz[x][y][newdir][1] = 1;
		return 1;
	}
}

void bfs() {
	while (!s.empty()) {
		int sum = s.begin()->first;
		int dir = s.begin()->second.first.first;
		int cons = s.begin()->second.first.second;
		int x = s.begin()->second.second.first;
		int y = s.begin()->second.second.second;
		s.erase(s.begin());
		for (int p = 0; p < 4; p++) {
			if (valid(x + dx[p], y + dy[p], cons + 1, p, dir)) {
				dist[x + dx[p]][y + dy[p]][p][1 + cons*(p==dir)] = sum + (mat[x + dx[p]][y + dy[p]] - '0');
				s.insert({ sum + (mat[x + dx[p]][y + dy[p]]-'0'), {{p, 1 + cons * (p == dir)}, {x + dx[p], y + dy[p]}}});
			}
		}
	}
}

int main()
{
	while (f >> mat[n]) {
		n++;
	}
	m = strlen(mat[0]);
	s.insert({ 0, { {-1, 0},{0, 0} } });
	viz[0][0][1][1] = 1;
	bfs();
	int tot = 2000000000;
	for (int i = 0; i < 4; i++) {
		for (int j = 4; j <= 10; j++) {
			if (viz[n - 1][m - 1][i][j]) {
				if (tot > dist[n - 1][m - 1][i][j]) {
					tot = dist[n - 1][m - 1][i][j];
				}
			}
		}
	}
	g << tot;
	return 0;
}

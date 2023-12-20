#include <iostream>
#include <cstring>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

ifstream f("file.in");
ofstream g("file.out");

char mat[1005][1005];
int maxdist, ctr;
int n, m;
int x, y;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { -1, 0, 1, 0 };
int dist[1005][1005];
set < pair < char, pair < int, int > > > mp;
queue < pair < int, int > > q;
long long area;
long long boundary;
long long result;
vector < pair < long long, long long > > v;

/*
| is a vertical pipe connecting north and south.
- is a horizontal pipe connecting east and west.
L is a 90 - degree bend connecting north and east.
J is a 90 - degree bend connecting north and west.
7 is a 90 - degree bend connecting south and west.
F is a 90 - degree bend connecting south and east.
*/

void start() {
	mp.insert({ '|', {1, 0} }); mp.insert({ '|', {-1, 0} });
	mp.insert({ '-', {0, -1} }); mp.insert({ '-', {0, 1} });
	mp.insert({ 'L', {1, 0} }); mp.insert({ 'L', {0, -1} });
	mp.insert({ 'J', {1, 0} }); mp.insert({ 'J', {0, 1} });
	mp.insert({ '7', {-1, 0} }); mp.insert({ '7', {0, 1} });
	mp.insert({ 'F', {-1, 0} }); mp.insert({ 'F', {0, -1} });
	mp.insert({ 'S', {-1, 0} }); mp.insert({ 'S', {1, 0} }); mp.insert({ 'S', {0, 1} }); mp.insert({ 'S', {0, -1} });
}

bool valid(int x1, int y1, int x2, int y2) {
	if (x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) return 0;
	if (mp.count({ mat[x1][y1], {x1 - x2, y1 - y2} }) == 0) return 0;
	if (mp.count({ mat[x2][y2], {x2 - x1, y2 - y1} }) == 0) return 0;
	if (dist[x2][y2] != 0) return 0;
	return 1;
}

void bfs(int x, int y) {
	q.push({ x, y });
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for (int p = 0; p < 4; p++) {
			if (valid(x, y, x + dx[p], y + dy[p])) {
				dist[x + dx[p]][y + dy[p]] = dist[x][y] + 1;
				q.push({ x + dx[p], y + dy[p] });
			}
		}
	}
}

void dfs(int x, int y) {
	boundary++;
	v.push_back({ x, y });
	dist[x][y] = 1;
	for (int p = 0; p < 4; p++) {
		if (valid(x, y, x + dx[p], y + dy[p])) {
			dfs(x + dx[p], y + dy[p]);
		}
	}
}

void reset_dist() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			dist[i][j] = 0;
		}
	}
}

int main()
{
	start();
	while (f.getline(mat[n], 1000)) {
		n++;
	}
	m = strlen(mat[0]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == 'S') {
				x = i; y = j;
			}
		}
	}
	dist[x][y] = 1;
	bfs(x, y);
	reset_dist();
	dfs(x, y);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			///maxdist = max(maxdist, dist[i][j]);
		}
	}
	/// g << maxdist-1;
	v.push_back(v[0]);
	for (int i = 0; i < v.size() - 1; i++) {
		area += v[i].first * v[i + 1].second - v[i + 1].first * v[i].second;
	}
	result = abs(area / 2) - boundary / 2 + 1;
	g << result << '\n';
	return 0;
}

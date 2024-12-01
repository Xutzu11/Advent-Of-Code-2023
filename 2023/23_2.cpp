#include <fstream>
#include <cstring>
#include <set>
#include <map>
#include <queue>
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

char mat[1005][1005];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };
int n, m, d;
int x, y;
int maxdist;
bool ok;
bool viz[1005][1005];
map < char, int > mp;
queue < pair < int, int > > q;
map < pair < int, int >, int > sq; /// map number to square
map < int , bool > vizg; /// vizited map for nodes in graph
vector < pair < int, int > > v[100005]; /// create graph from significant squares
int neigh[1005][1005]; /// number of neighbours for squares, squares with <= 2 are not significant (except first and last)
int sign[1005][1005], ctr;

bool neighbour(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= m) return 0;
	if (mat[x][y] == '#') return 0;
	return 1; 
}

bool valid(int nx, int ny) {
	if (nx < 0 || ny < 0 || nx >= n || ny >= m) return 0;
	if (neigh[nx][ny]==0) return 0;
	if (viz[nx][ny]) return 0;
	if (mat[nx][ny] == '#') return 0;
	return 1;
}

void dfs_find(int d, int sx, int sy, int x, int y) {
	viz[x][y] = 1;
	if (sign[x][y] && !ok) {  /// when we reach a significant square, we add edge in graph
		ok = 1;
		if (neigh[x][y]) {
			q.push({ x, y });
		}
		v[sq[{x, y}]].push_back({ sq[{sx, sy}], d });
		v[sq[{sx, sy}]].push_back({ sq[{x, y}], d });
	}
	for (int p = 0; p < 4 && !ok; p++) {
		if (valid(x + dx[p], y + dy[p])) {
			neigh[x][y]--;
			neigh[x + dx[p]][y + dy[p]]--;
			dfs_find(d + 1, sx, sy, x + dx[p], y + dy[p]);
		}
	}
	viz[x][y] = 0;
}

void create_graph() {
	/// create the compressed weighted graph
	q.push({ x, y });
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for (int p = 0; p < 4; p++) {
			if (neigh[x][y] && valid(x+dx[p], y+dy[p])) {
				neigh[x][y]--;
				neigh[x + dx[p]][y + dy[p]]--;
				viz[x][y] = 1;
				ok = 0;
				dfs_find(1, x, y, x+dx[p], y+dy[p]);
				viz[x][y] = 0;
			}
		}
	}
}

void dfs_solve(int nod, int d) {
	vizg[nod] = 1;
	if (nod == ctr) maxdist = max(maxdist, d);
	for (auto k : v[nod]) {
		if (vizg[k.first] == 0) {
			dfs_solve(k.first, d + k.second);
		}
	}
	vizg[nod] = 0;
}

int main() 
{
	mp['^'] = 0; mp['>'] = 1; mp['v'] = 2; mp['<'] = 3;
	while (f >> mat[n]) n++;
	m = strlen(mat[0]);
	for (int j = 0; j < m; j++) {
		if (mat[0][j] == '.') {
			x = 0; y = j;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] != '#') {
				for (int p = 0; p < 4; p++) {
					if (neighbour(i + dx[p], j + dy[p])) neigh[i][j]++; // count neighbours of squares
				}
				if (neigh[i][j] >= 3 || i == 0 || i == n - 1) { /// first, last and squares with multiple possible paths will be the nodes in the graph
					sign[i][j] = 1;
					sq[{i, j}] = ++ctr;
				}
			}
		}
	}
	create_graph();
	dfs_solve(1, 0);
	g << maxdist;
	return 0;
}
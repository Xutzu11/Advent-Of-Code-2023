#include <fstream>
#include <cstring>
#include <set>
#include <map>
#include <deque>
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

char mat[1005][1005];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };
int n, m, d;
int x, y;
int maxdist;
bool viz[1005][1005];
map < char, int > mp;

bool valid(int x, int y, int p, int nx, int ny) {
	if (nx < 0 || ny < 0 || nx >= n || ny >= m) return 0;
	if (viz[nx][ny]) return 0;
	if (mat[nx][ny] == '#') return 0;
	if (mat[x][y] != '.' && mp[mat[x][y]] != p) return 0;
	return 1;
}

void dfs(int d, int x, int y) {
	viz[x][y] = 1;
	if (x == n - 1) maxdist = max(maxdist, d);
	for (int p = 0; p < 4; p++) {
		if (valid(x, y, p, x + dx[p], y + dy[p])) {
			dfs(d + 1, x + dx[p], y + dy[p]);
		}
	}
	viz[x][y] = 0;
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
	dfs(0, x, y);
	g << maxdist;
	return 0;
}

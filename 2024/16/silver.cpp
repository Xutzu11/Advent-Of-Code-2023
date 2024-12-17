#include <iostream>
#include <vector>
#include <set>
#include <string>
#define inf 1000000000
using namespace std;

vector<string> mat;
string s;
int n, m;
int sx, sy, ex, ey, x, y;
vector<vector<vector<int>>> mindist;
set<pair<pair<int, int>, pair<int, int>>> pos;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool valid(int x, int y, int dist, int dir) {
    if (x < 0 || y < 0 || x >= n || y >= m) {
        return 0;
    }
    if (mat[x][y] == '#') {
        return 0;
    }
    if (mindist[x][y][dir] <= dist) {
        return 0;
    }
    return 1;
} 

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        mat.push_back(s);
    }
    n = mat.size(); m = mat[0].size();
    for (int i=0;i<n;i++) {
        mindist.emplace_back();
        for (int j=0;j<m;j++) {
            mindist[i].push_back(vector<int>{inf, inf, inf, inf});
            if (mat[i][j] == 'S') {
                sx = i;
                sy = j;
            }
            if (mat[i][j] == 'E') {
                ex = i;
                ey = j;
            }
        }
    }
    pos.insert({{0, 1}, {sx, sy}});
    mindist[sx][sy][1] = 0;
    while (!pos.empty()) {
        int dist = pos.begin()->first.first;
        int dir = pos.begin()->first.second;
        int x = pos.begin()->second.first;
        int y = pos.begin()->second.second;
        pos.erase(pos.begin());
        for (int p=0;p<4;p++) {
            if ((p+2)%4 == dir) continue;
            if (valid(x+dx[p], y+dy[p], dist+1+1000*(p!=dir), p)) {
                mindist[x+dx[p]][y+dy[p]][p] = dist+1+1000*(p!=dir);
                pos.insert({{dist+1+1000*(p!=dir), p}, {x+dx[p], y+dy[p]}});
            }
        }
    }
    int minfin = inf;
    for (int p=0;p<4;p++) {
        minfin = min(minfin, mindist[ex][ey][p]);
    }
    cout << minfin;
    return 0;
}
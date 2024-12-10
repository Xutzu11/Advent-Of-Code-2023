#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

vector<string> grid;
string s;
int n, m;
int tot = 0;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool valid(int li, int lj, int i, int j, vector<vector<bool>> &viz) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return false;
    }
    if (grid[i][j] - grid[li][lj] != 1) {
        return false;
    }
    if (viz[i][j]) {
        return false;
    }
    return true;
}

int score(int x, int y) {
    vector<vector<bool>> viz;
    queue<pair<int,int>> q;
    int res = 0;
    for (int i=0;i<n;i++) {
        viz.emplace_back();
        for (int j=0;j<m;j++) {
            viz[i].push_back(false);
        }
    }
    viz[x][y] = true;
    q.push({x, y});
    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        if (grid[x][y] == '9') {
            res++;
        }
        for (int p=0;p<4;p++) {
            if (valid(x, y, x+dx[p], y+dy[p], viz)) {
                q.push({x+dx[p], y+dy[p]});
                viz[x+dx[p]][y+dy[p]] = true;
            }
        }
    }
    return res;
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        grid.push_back(s);
    }
    n = grid.size(); m = grid[0].size();
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (grid[i][j] == '0') {
                tot += score(i, j);
            }
        }
    }
    cout << tot;
    return 0;
}
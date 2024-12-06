#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

vector<string> v;
string s;
int a, b, p = 0;
queue<tuple<int,int,int>> q;
int n, m, tot = 0, step;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
vector<vector<vector<int>>> viz;

bool valid(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m)
        return 0;
    return 1;
}

bool check_for_cycle() {
    int x = a, y = b;
    p = 0;
    while (true) {
        if (viz[x][y][p] == step) 
            return 1;
        viz[x][y][p] = step;
        int nx = x+dx[p], ny = y+dy[p];
        if (valid(nx, ny)) {
            if (v[nx][ny]=='#') {
                p = (p+1) % 4;
            } 
            else {
                x = nx; y = ny;
            }
        }
        else break;
    }
    return 0;
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        v.push_back(s);
    }
    n = v.size(), m = v[0].size();
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (v[i][j] == '^') {
                a = i; b = j;
                v[i][j] = '.';
            }
        }
    }
    viz.clear();
    for (int i=0;i<n;i++) {
        viz.emplace_back();
        for (int j=0;j<m;j++) {
            viz[i].push_back({0, 0, 0, 0});
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (v[i][j] == '.') {
                step++;
                v[i][j] = '#';
                tot += check_for_cycle();
                v[i][j] = '.';
            }
        }
    }
    cout << tot;
    return 0;
}
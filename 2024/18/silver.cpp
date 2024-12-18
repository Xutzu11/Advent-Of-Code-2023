#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

vector<string> mat;
int n = 71, m = 71;
int x, y;
string s;
queue<pair<int,pair<int,int>>> q;
vector<vector<bool>> viz;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int b = 0, kb = 1024;

bool valid(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= m) {
        return false;
    }
    if (mat[x][y] == '#') {
        return false;
    } 
    if (viz[x][y]) {
        return false;
    }
    return true;
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    for (int i=0;i<n;i++) {
        s = "";
        viz.emplace_back();
        for (int j=0;j<m;j++) {
            s.push_back('.');
            viz[i].push_back(false);
        }
        mat.push_back(s);
    }
    while (cin >> s) {
        int i = 0;
        x = y = 0;
        while (isdigit(s[i])) {
            y = y*10 + s[i] - '0';
            i++;
        }
        i++;
        while (isdigit(s[i])) {
            x = x*10 + s[i] - '0';
            i++;
        }
        mat[x][y] = '#';
        b++;
        if (b == kb) break;
    }
    q.push({0, {0, 0}});
    viz[0][0] = true;
    while (!q.empty()) {
        int dist = q.front().first;
        x = q.front().second.first;
        y = q.front().second.second;
        if (x == n-1 && y == m-1) {
            cout << dist;
        }
        q.pop();
        for (int p=0;p<4;p++) {
            if (valid(x+dx[p], y+dy[p])) {
                q.push({dist+1, {x+dx[p], y+dy[p]}});
                viz[x+dx[p]][y+dy[p]] = true;
            }
        }
    }
    return 0;
}
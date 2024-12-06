#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

vector<string> v;
string s;
int x, y, p = 0;
queue<tuple<int,int,int>> q;
int n, m, tot;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool valid(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m)
        return 0;
    return 1;
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
                x = i; y = j;
            }
        }
    }
    tot = 1;
    while (true) {
        int nx = x+dx[p], ny = y+dy[p];
        if (valid(nx, ny)) {
            if (v[nx][ny]=='#') {
                p = (p+1) % 4;
            } 
            else {
                if (v[x][y] != 'X') {
                    v[x][y] = 'X';
                    tot++;
                }
                x = nx; y = ny;
            }
        }
        else break;
    }
    cout << tot;
    return 0;
}
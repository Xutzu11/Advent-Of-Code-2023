#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

vector<string> mat;
string s;
string moves;
int n, m, x, y;
map<char, pair<int,int>> d;
map<char, char> inv;
int res;
bool isvalid(int i, int j) {
    return (mat[i][j] == '@' || mat[i][j] == 'O');
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    d['^'] = {-1, 0}; inv['^'] = 'v';
    d['>'] = {0, 1}; inv['>'] = '<';
    d['v'] = {1, 0}; inv['v'] = '^';
    d['<'] = {0, -1}; inv['<'] = '>';
    while (getline(cin, s)) {
        if (s.empty()) break;
        mat.push_back(s);
    }
    while (getline(cin, s)) {
        moves += s;
    }
    n = mat.size(); m = mat[0].size();
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (mat[i][j] == '@') {
                x = i; y = j;
            }
        }
    }
    for (auto c:moves) {
        int cx = x, cy = y;
        while (isvalid(cx, cy)) {
            cx += d[c].first;
            cy += d[c].second;
        }
        if (mat[cx][cy] == '.') {
            char cinv = inv[c];
            while (cx != x || cy != y) {
                mat[cx][cy] = mat[cx+d[cinv].first][cy+d[cinv].second];
                cx += d[cinv].first;
                cy += d[cinv].second;
            }
            mat[cx][cy] = '.';
            x += d[c].first;
            y += d[c].second;
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (mat[i][j] == 'O') {
                res += 100 * i + j;
            }
        }
    }
    cout << res;
    return 0;
}
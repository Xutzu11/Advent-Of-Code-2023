#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <string>
#include <map>
using namespace std;

vector<string> mat;
string s, new_s;
string moves;
int n, m, x, y;
map<char, pair<int,int>> d;
map<char, char> inv;
int res;
int sr, er;
vector<set<int>> pushers;

bool valid_h(int i, int j) {
    return (mat[i][j] == '@' || mat[i][j] == '[' || mat[i][j] == ']');
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
        new_s = "";
        for (char &c:s) {
            if (c == '@') new_s += "@.";
            if (c == 'O') new_s += "[]";
            if (c == '.') new_s += "..";
            if (c == '#') new_s += "##";
        }
        mat.push_back(new_s);
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
        if (c == '<' || c == '>') {
            while (valid_h(cx, cy)) {
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
            else continue;
        }
        else {
            sr = er = cy;
            set<int> cln, next_cln;
            cln.insert(sr);
            bool is_box, is_wall;
            int next_sr, next_er;
            pushers.clear();
            while (true) {
                is_box = false, is_wall = false;
                for (auto k: cln) {
                    if (mat[cx][k] == '#') {
                        is_wall = true;
                    }
                    if (mat[cx][k] == '@') {
                        is_box = true;
                        next_cln.insert(k);
                    }
                    if (mat[cx][k] == '[') {
                        is_box = true;
                        next_cln.insert(k);
                        next_cln.insert(k+1);
                    }
                    if (mat[cx][k] == ']') {
                        is_box = true;
                        next_cln.insert(k);
                        next_cln.insert(k-1);
                    }
                }
                if (is_box && !is_wall) {
                    pushers.push_back(next_cln);
                    cx += d[c].first;
                    cln = next_cln;
                    next_cln.clear();
                }
                else break;
            }
            if (is_wall) {
                continue;
            }
            char cinv = inv[c];
            while (!pushers.empty()) {
                set<int> cln = pushers.back();
                pushers.pop_back();
                for (auto k:cln) {
                    mat[cx][k] = mat[cx+d[cinv].first][k];
                    mat[cx+d[cinv].first][k] = '.';
                }
                cx += d[cinv].first;
            }
            x += d[c].first;
        }
        
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (mat[i][j] == '[') {
                res += 100 * i + j;
            }
        }
    }
    cout << res;
    return 0;
}
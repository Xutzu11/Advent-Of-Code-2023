#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> v;
vector<vector<bool>> viz;
string s;
int sides, area, n, m;
char c;
long long res;
int di[4] = {-1, 0, 1, 0}, dj[4] = {0, 1, 0, -1};

int valid(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return 0;
    }
    if (v[i][j] != c) {
        return 0;
    }
    if (viz[i][j]) {
        return 1;
    }
    return 2;
}

void fill(int i, int j) {
    area++;
    viz[i][j] = true;
    for (int p=0;p<4;p++) {
        int is_valid = valid(i+di[p], j+dj[p]);
        if (is_valid == 0 && (valid(i+di[(p+1)%4], j+dj[(p+1)%4]) == 0 || valid(i+di[p]+di[(p+1)%4], j+dj[p]+dj[(p+1)%4]) > 0)) {
            sides++;
        }
        else if (is_valid == 2) {
            fill(i+di[p], j+dj[p]);
        }
    }
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        v.push_back(s);
        viz.push_back(vector<bool>(s.size()));
    }
    n = v.size(), m = v[0].size();
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (!viz[i][j]) {
                sides = area = 0;
                c = v[i][j];
                fill(i, j);
                res += sides * area;
            }
        }
    }
    cout << res;
    return 0;
}
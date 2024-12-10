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
vector<vector<int>> dp;

bool valid(char c, int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return false;
    }
    if (grid[i][j] != c-1) {
        return false;
    }
    return true;
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        grid.push_back(s);
    }
    n = grid.size(); m = grid[0].size();
    for (int i=0;i<n;i++) {
        dp.emplace_back();
        for (int j=0;j<m;j++) {
            dp[i].push_back(0);
            if (grid[i][j] == '0') {
                dp[i][j] = 1;
            }
        }
    }
    for (int c='1';c<='9';c++) {
        for (int i=0;i<n;i++) {
            for (int j=0;j<m;j++) {
                if (grid[i][j] == c) {
                    for (int p=0;p<4;p++) {
                        if (valid(c, i+dx[p], j+dy[p])) {
                            dp[i][j] += dp[i+dx[p]][j+dy[p]];
                        }
                    }
                    if (c == '9') {
                        tot += dp[i][j];
                    }
                }
            }
        }
    }
    cout << tot;
    return 0;
}
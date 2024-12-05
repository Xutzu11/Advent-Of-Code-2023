#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m, sum;
string s;
string word = "XMAS";
vector < string > v;
int dx[10] = {-1, -1, -1, 0, 1, 1, 1, 0}, dy[10] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool valid(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m)
        return 0;
    return 1;
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        v.push_back(s);
    }
    n = v.size(); m = v[0].size();
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            for (int p=0;p<8;p++) {
                bool found = true;
                for (int k=0;k<4;k++) {
                    int x = i + dx[p] * k;
                    int y = j + dy[p] * k;
                    if (valid(x, y) && v[x][y] == word[k])
                        continue;
                    found = false;
                }
                sum += found;
            }
        }
    }
    cout << sum;
    return 0;
}
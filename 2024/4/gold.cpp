#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m, sum;
string s;
vector < string > v;

bool valid(int i, int j, int c) {
    if (i < 0 || j < 0 || i >= n || j >= m)
        return 0;
    if (v[i][j] != c)
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
            if (valid(i, j, 'A')) {
                char c1d1 = 0, c2d1 = 0, c1d2 = 0, c2d2 = 0;  
                if (valid(i-1, j-1, 'M') || valid(i-1, j-1, 'S')) {
                    c1d1 = v[i-1][j-1];
                }
                if (valid(i-1, j+1, 'M') || valid(i-1, j+1, 'S')) {
                    c1d2 = v[i-1][j+1];
                }
                if (valid(i+1, j+1, 'M') || valid(i+1, j+1, 'S')) {
                    c2d1 = v[i+1][j+1];
                }
                if (valid(i+1, j-1, 'M') || valid(i+1, j-1, 'S')) {
                    c2d2 = v[i+1][j-1];
                }
                if (c1d1 && c1d2 && c2d1 && c2d2 && c1d1 != c2d1 && c1d2 != c2d2) {
                    sum++;
                }
            }
        }
    }
    cout << sum;
    return 0;
}
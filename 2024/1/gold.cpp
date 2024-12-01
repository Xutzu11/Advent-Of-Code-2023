#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    long long x, y, tot = 0;
    vector < long long > vx;
    map < long long, int > my;
    while (cin >> x >> y) {
        vx.push_back(x);
        my[y]++;
    }
    for (auto x:vx) {
        tot += x * my[x];
    }
    cout << tot;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    long long x, y, tot = 0;
    vector < long long > vx, vy;
    while (cin >> x >> y) {
        vx.push_back(x);
        vy.push_back(y);
    }
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    for (int i=0; i<vx.size(); i++) {
        tot += abs(vx[i] - vy[i]);
    }
    cout << tot;
    return 0;
}
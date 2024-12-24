#include <iostream>
#include <vector>
#define mod 16777216
using namespace std;

long long sn;
int steps = 2000;
long long res = 0;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> sn) {
        for (int i=1;i<=steps;i++) {
            sn = (sn ^ (sn * 64)) % mod;
            sn = (sn ^ (sn / 32)) % mod;
            sn = (sn ^ (sn * 2048)) % mod;
        }
        res += sn;
    }
    cout << res;
    return 0;
}
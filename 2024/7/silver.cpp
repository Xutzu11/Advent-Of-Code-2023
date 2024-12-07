#include <iostream>
#include <string>
#include <vector>
using namespace std;

string s;
vector<long long> v;
long long rez, x;
bool first;
long long tot = 0;

bool bkt(int k, long long sum) {
    if (k == v.size() && sum == rez)
        return 1;
    if (k == v.size() || sum > rez)
        return 0;
    return bkt(k+1, sum+v[k]) || bkt(k+1, sum*v[k]);
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (getline(cin, s)) {
        rez = x = 0;
        s += " ";
        v.clear();
        first = true;
        for (char c:s) {
            if (c == ' ' && first) {
                first = false;
            }
            else if (c == ' ') {
                v.push_back(x);
                x = 0;
            }
            else if (c == ':') {
                continue;
            }
            else if (first) {
                rez = rez*10 + c-'0';
            }
            else {
                x = x*10 + c-'0';
            }
        }
        tot += bkt(1, v[0]) * rez;
    }
    cout << tot;
    return 0;
}
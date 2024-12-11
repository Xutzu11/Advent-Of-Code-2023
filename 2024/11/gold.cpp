#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

long long x;
long long res = 0;

int n_cif(long long x) {
    int n = 0;
    while (x) {
        n++;
        x /= 10;
    }
    return n;
}

pair<long long, long long>divide_x(long long x) {
    string nr = to_string(x);
    return {stoll(nr.substr(0, nr.size()/2)), stoll(nr.substr(nr.size()/2, nr.size()/2))};
}

unordered_map<long long, long long> after_blink, before_blink;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    int blinks = 75;
    while (cin >> x) {
        before_blink[x]++;
    }
    while (blinks) {
        after_blink.clear();
        for (auto p:before_blink) {
            if (p.first == 0) {
                after_blink[1] += p.second;
            }
            else if (n_cif(p.first)%2==0) {
                pair<long long, long long>split = divide_x(p.first);
                after_blink[split.first] += p.second;
                after_blink[split.second] += p.second;
            }
            else {
                after_blink[p.first * 2024] += p.second;
            }
        }
        before_blink = after_blink;
        blinks--;
    }
    for (auto p:before_blink) {
        res += p.second;
    }
    cout << res;
    return 0;
}
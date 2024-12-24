#include <iostream>
#include <map>
#include <vector>
#define mod 16777216
using namespace std;

long long last_sn, sn;
int steps = 2000;
pair<long long, tuple<int,int,int,int>> res = {0, {}};
map<tuple<int,int,int,int>, long long> bananas, local_bananas;
tuple<int,int,int,int> last_seq;
vector<int> v;
int seq_length = 4;

void next_sn() {
    sn = (sn ^ (sn * 64)) % mod;
    sn = (sn ^ (sn / 32)) % mod;
    sn = (sn ^ (sn * 2048)) % mod;
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> sn) {
        v.clear(); local_bananas.clear();
        for (int i=1;i<seq_length;i++) {
            last_sn = sn;
            next_sn();
            v.push_back(sn%10 - last_sn%10);
        }
        last_seq = {0, v[0], v[1], v[2]};
        for (int i=seq_length; i<=steps;i++) {
            last_sn = sn;
            next_sn();
            last_seq = {get<1>(last_seq), get<2>(last_seq), get<3>(last_seq), sn%10-last_sn%10};
            if (local_bananas.find(last_seq) == local_bananas.end()) {
                local_bananas[last_seq] = max(local_bananas[last_seq], sn%10);
            }
        }
        for (auto &bn:local_bananas) {
            bananas[bn.first] += bn.second;
        }
    }
    for (auto &bn:bananas) {
        res = max(res, {bn.second, bn.first});
    }
    cout << res.first;
    return 0;
}
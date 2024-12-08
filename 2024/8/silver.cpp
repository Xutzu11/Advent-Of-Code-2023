#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<char,vector<pair<int,int>>> antennas; 
vector<string> v;
string s;
int n, m, res = 0;

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
            if (v[i][j] != '.') {
                antennas[v[i][j]].push_back({i, j});
            }
        }
    }
    for (auto &k: antennas) {
        for (int i=0;i<k.second.size();i++) {
            for (int j=i+1;j<k.second.size();j++) {
                int ni, nj;
                ni = k.second[i].first+(k.second[i].first-k.second[j].first);
                nj = k.second[i].second+(k.second[i].second-k.second[j].second);
                if (valid(ni, nj)) {
                    v[ni][nj] = '#';
                }
                ni = k.second[j].first+(k.second[j].first-k.second[i].first);
                nj = k.second[j].second+(k.second[j].second-k.second[i].second);
                if (valid(ni, nj)) {
                    v[ni][nj] = '#';
                }
            }
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            res += (v[i][j] == '#');
        }
    }
    cout << res;
    return 0;
}
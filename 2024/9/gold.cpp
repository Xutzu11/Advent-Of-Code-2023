#include <iostream>
#include <vector>
#include <string>
using namespace std;

long long n, p, res = 0;
string s;
vector<pair<int,int>> disk, spaces;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    cin >> s;
    for (int i=0;i<s.size();i++) {
        n += s[i]-'0';
    }
    vector<int> v(n, -1);
    for (int i=0;i<s.size();i++) {
        if (i%2==0) {
            for (int j=p;j<p+s[i]-'0';j++) {
                v[j] = i/2;
            }
            disk.push_back({p, p+s[i]-'0'});
        }
        else {
            spaces.push_back({p, p+s[i]-'0'});
        }
        p += s[i]-'0';
    }
    for (int i=disk.size()-1;i>=0;i--) {
        for (int j=0;j<spaces.size();j++) {
            if (spaces[j].second-spaces[j].first >= disk[i].second-disk[i].first && spaces[j].first < disk[i].first) {
                for (int k=spaces[j].first;k<spaces[j].first+disk[i].second-disk[i].first; k++) {
                    v[k] = v[disk[i].first];
                }
                for (int k=disk[i].first;k<disk[i].second;k++) {
                    v[k] = -1;
                }
                spaces[j].first += disk[i].second-disk[i].first;
                break;
            }
        }
    }
    for (int i=0;i<n;i++) {
        res += (v[i] == -1) ? 0 : i*v[i];
    }
    cout << res;
    return 0;
}
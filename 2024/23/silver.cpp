#include <iostream>
#include <set>
using namespace std;

string s1, s2;
string s;
set<pair<string,string>> edges; 
set<pair<string,pair<string,string>>> res;
set<string> comps, comps_with_t;

string middle(string s1, string s2, string s3) {
    if ((s2 <= s1 && s1 <= s3) || (s3 <= s1 && s1 <= s2)) 
        return s1;
    if ((s1 <= s2 && s2 <= s3) || (s3 <= s2 && s2 <= s1)) 
        return s2;
    return s3;
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        s1 = s[0]; s1 += s[1];
        s2 = s[3]; s2 += s[4];
        edges.insert({min(s1,s2), max(s1,s2)});
        comps.insert(s1);
        if (*s1.begin() == 't') {
            comps_with_t.insert(s1);
        }
        comps.insert(s2);
        if (*s2.begin() == 't') {
            comps_with_t.insert(s2);
        }
    }
    for (auto &ct:comps_with_t) {
        for (auto &c1:comps) {
            for (auto &c2:comps) {
                if (edges.count({min(c1, c2), max(c1, c2)}) && edges.count({min(c1, ct), max(c1, ct)}) && 
                    edges.count({min(c2, ct), max(c2, ct)})) {
                    res.insert({min(ct, min(c1, c2)), {middle(ct, c1, c2), max(ct, max(c1, c2))}});
                }
            }
        }
    }
    cout << res.size();
    return 0;
}
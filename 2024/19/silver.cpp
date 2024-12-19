#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

string s;
set<string> towels;
string towel;
vector<bool> dp;
int res = 0;
int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    getline(cin, s);
    int i = 0;
    while (i < s.size()) {
        towel = "";
        while (isalpha(s[i])) {
            towel += s[i];
            i++;
        }
        towels.insert(towel);
        i += 2;
    }
    getline(cin, s);

    while (cin >> towel) {
        dp.clear();
        for (int i=0;i<towel.size();i++) {
            dp.push_back(false);
        }
        for (int i=0;i<towel.size();i++) {
            for (int j=i;j>=0 && !dp[i];j--) {
                if (towels.count(towel.substr(j, i-j+1)) && (j == 0 || dp[j-1])) {
                    dp[i] = true;
                } 
            }
        }
        res += dp[towel.size() - 1];
    }
    cout << res;
    return 0;
}
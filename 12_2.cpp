#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

ifstream f("aoc.in");
ofstream g("aoc.out");
string s, nrs;
int n, nn, nr;
long long tot;
int v[1005];
long long dp[105][105][105];
int ctr;

void dynamic() {
    if (s[0] == '.') dp[0][1][0] = 1;
    else if (s[0] == '#') dp[0][1][1] = 1;
    else {
        dp[0][1][0] = 1;
        dp[0][1][1] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= ctr+1; j++) {
            for (int k = 0; k <= v[j]; k++) {
                if (s[i] == '.') {
                    if (k != 0) dp[i][j][k] = 0;
                    else dp[i][j][k] = dp[i - 1][j - 1][v[j - 1]] + dp[i - 1][j][k];
                }
                else if (s[i] == '#') {
                    if (k == 0) dp[i][j][k] = 0;
                    else dp[i][j][k] = dp[i - 1][j][k-1];
                }
                else {
                    if (k == 0) dp[i][j][k] = dp[i - 1][j - 1][v[j - 1]] + dp[i - 1][j][k];
                    else dp[i][j][k] = dp[i - 1][j][k - 1];
                }
            }
        }
    }
    tot += dp[n - 1][ctr + 1][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= ctr + 1; j++) {
            for (int k = 0; k <= v[j]; k++) {
                dp[i][j][k] = 0;
            }
        }
    }
}

int main()
{
    while (f >> s) {
        f >> nrs;
        s = s + "?" + s + "?" + s + "?" + s + "?" + s + ".";
        nrs = nrs + "," + nrs + "," + nrs + "," + nrs + "," + nrs;
        nn = nrs.size();
        n = s.size();
        ctr = 0;
        int i = 0;
        while (i < nn) {
            if (isdigit(nrs[i])) {
                nr = 0;
                while (i < nn && isdigit(nrs[i])) {
                    nr = nr * 10 + (nrs[i] - '0');
                    i++;
                }
                v[++ctr] = nr;
            }
            i++;
        }
        dynamic();
    }
    g << tot;
    return 0;
}

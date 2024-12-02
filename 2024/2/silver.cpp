#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    char s[10005];
    char *p;
    vector < int > v;
    int x, res = 0;
    long long tot_abs, tot_norm;
    while (!cin.eof()) {
        v.clear();
        cin.getline(s, 10005);
        p = strtok(s, " ");
        while (p != NULL) {
            v.push_back(atoi(p));
            p = strtok(NULL, " ");
        }
        tot_abs = tot_norm = 0;
        bool ok = true;
        for (int i=1;i<v.size();i++) {
            int dif = v[i]-v[i-1];
            tot_abs += abs(dif);
            tot_norm += dif;
            if (abs(dif) < 1 || abs(dif) > 3)
                ok = false;
        }
        ok = ok && (abs(tot_norm) == tot_abs);
        res += ok;
    }
    cout << res;
    return 0;
}
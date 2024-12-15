#include <iostream>
#include <string>
#define inf 2000000005
using namespace std;

int xa, ya, xb, yb, x, y, max_pushes = 100, mincost;
long long res;
string s;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (getline(cin, s)) {
        xa = ya = xb = yb = x = y = 0;
        
        int i = string("Button A: X+").size();
        while (isdigit(s[i])) {
            xa = xa*10 + s[i]-'0';
            i++;
        }
        i += string(", Y+").size();
        while (isdigit(s[i])) {
            ya = ya*10 + s[i]-'0';
            i++;
        }

        getline(cin, s);
        i = string("Button B: X+").size();
        while (isdigit(s[i])) {
            xb = xb*10 + s[i]-'0';
            i++;
        }
        i += string(", Y+").size();
        while (isdigit(s[i])) {
            yb = yb*10 + s[i]-'0';
            i++;
        }

        getline(cin, s);
        i = string("Prize: X=").size();
        while (isdigit(s[i])) {
            x = x*10 + s[i]-'0';
            i++;
        }
        i += string(", Y=").size();
        while (isdigit(s[i])) {
            y = y*10 + s[i]-'0';
            i++;
        }

        getline(cin, s);

        mincost = inf;
        for (int p=0;p<=max_pushes;p++) {
            if (p*xa <= x && p*ya <= y) {
                if ((x-p*xa)%xb == 0 && (y-p*ya)%yb == 0 && (x-p*xa)/xb == (y-p*ya)/yb) {
                    mincost = min(mincost, 3*p + (x-p*xa)/xb);
                }
            }
        }
        res += (mincost == inf ? 0 : mincost);
    }
    cout << res;
    return 0;
}
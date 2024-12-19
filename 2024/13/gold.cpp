#include <iostream>
#include <string>
#include <map>
#include <assert.h>
#define inf 2000000005
#define offset 10000000000000
using namespace std;

long long xa, ya, xb, yb, x, y, mincost;
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
        x += offset;
        y += offset;

        long long delta = xa * yb - xb * ya; 
        long long delta_x = x * yb - xb * y; 
        long long delta_y = xa * y - x * ya;
        if (delta != 0) {
            if (delta_x % delta != 0 || delta_y % delta != 0) {
                continue;
            }
            else {
                res += 3 * (delta_x / delta) + (delta_y / delta);
            }
        }
        else {
            assert(false); // hopefully not
        }
    }
    cout << res;
    return 0;
}
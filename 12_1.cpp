#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

ifstream f("aoc.in");
ofstream g("aoc.out");

char s[1005], nrs[1005];
int n, nn, nr;
int tot;
int v[1005];
int ctr;

bool solutie() {
    int i = 0, j = 1, secv = 0;
    while (i < n && j <= ctr) {
        if (s[i] == '#') {
            secv = 0;
            while (i < n && s[i] == '#') {
                secv++;
                i++;
            }
            if (secv != v[j]) return 0;
            j++;
        }
        i++;
    }
    while (i < n && s[i] == '.') i++;
    if (j <= ctr || i < n) return 0;
    return 1;
}

bool valid(int k) {
    int i = 0, j = 1, secv = 0;
    while (i <= k && j <= ctr) {
        if (s[i] == '#') {
            secv = 0;
            while (i <= k && s[i] == '#') {
                secv++;
                i++;
            }
            if (secv > v[j]) return 0;
            if (secv <= v[j] && i > k) return 1;
            if (secv < v[j]) return 0;
            j++;
        }
        i++;
    }
    return 1;
}

void bkt(int k) {
    if (k == n) {
        if (solutie())
            tot++;
    }
    else if (s[k] == '#' || s[k] == '.') bkt(k + 1);
    else {
        s[k] = '#';
        if (valid(k)) bkt(k + 1);
        s[k] = '.';
        if (valid(k)) bkt(k + 1);
        s[k] = '?';
    }
}

int main()
{
    while (f >> s) {
        f >> nrs;
        nn = strlen(nrs);
        n = strlen(s);
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
        bkt(0);
        //g << tot << '\n';
    }
    g << tot << '\n';
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

string s;
vector<pair<int, int>> pos;
vector<pair<int, int>> v;
int px, py, vx, vy;
int n = 101, m = 103, seconds = 100;
bool neg;
int quad, res;

map<pair<int,int>, int> mat;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (getline(cin, s)) {
        px = py = vx = vy = 0;
        int i = 2;
        neg = (s[i] == '-');
        i += neg;
        while (isdigit(s[i])) {
            px = px*10 + s[i]-'0';
            i++;
        }
        if (neg) px *= -1;

        i++;
        neg = (s[i] == '-');
        i += neg;
        while (isdigit(s[i])) {
            py = py*10 + s[i]-'0';
            i++;
        }
        if (neg) py *= -1;

        i+=3;
        neg = (s[i] == '-');
        i += neg;
        while (isdigit(s[i])) {
            vx = vx*10 + s[i]-'0';
            i++;
        }
        if (neg) vx *= -1;

        i++;
        neg = (s[i] == '-');
        i += neg;
        while (isdigit(s[i])) {
            vy = vy*10 + s[i]-'0';
            i++;
        }
        if (neg) vy *= -1;

        pos.push_back({px, py});
        v.push_back({vx, vy});
    }
    for (int i=1;i<=seconds;i++) {
        for (int j=0;j<pos.size();j++) {
            pos[j].first = (pos[j].first + v[j].first + 2*n) % n;
            pos[j].second = (pos[j].second + v[j].second + 2*m) % m;
        }
    }
    for (int j=0;j<pos.size();j++) {
        mat[pos[j]]++;
    }
    
    res = 1;
    for (int w=0;w<4;w++) {
        quad = 0;
        for (int i=(w%2 ? 0 : (n+1)/2);i<(w%2 ? n/2 : n);i++) {
            for (int j=(w/2 ? 0 : (m+1)/2);j<(w/2 ? m/2 : m);j++) {
                quad += mat[{i, j}];
            }
        }
        res *= quad;
    }
    cout << res;
    return 0;
}
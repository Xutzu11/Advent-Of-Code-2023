#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

string s;
vector<pair<int, int>> pos;
vector<pair<int, int>> v;
int px, py, vx, vy;
int n = 101, m = 103;
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
    for (int i=1;;i++) {
        mat.clear();
        for (int j=0;j<pos.size();j++) {
            pos[j].first = (pos[j].first + v[j].first + 2*n) % n;
            pos[j].second = (pos[j].second + v[j].second + 2*m) % m;
            mat[pos[j]]++;
        }
        if (mat.size() == pos.size()) {
            cout << i << '\n';
            // the tree
            for (int a=0;a<n;a++) {
                for (int b=0;b<m;b++) {
                    cout << (mat[{a,b}] ? '.' : 'X');
                }
                cout << '\n';
            }
            break;
        }
    }
    return 0;
}
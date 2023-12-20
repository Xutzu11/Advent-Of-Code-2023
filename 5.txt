#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

ifstream f("aoc.in");
ofstream g("aoc.out");

char s[100005];
long long minn = 5000000000000;
long long n, nr;
int ctr, poz;
long long nr1, nr2;
bool pz;
long long mapping;
bool found;
int dims[10005];
struct Maping{
    long long source, destination, offset;
}v[20][10005];
queue < pair < long long , long long > > q1, q2;
vector < long long > v1, v2;

int main()
{
    f.getline(s, 100005);
    int i = 0;
    n = strlen(s);
    pz = 0;
    while (i<n) {
        if (isdigit(s[i])) {
            nr = 0;
            while (isdigit(s[i]) && i<n) {
                nr = nr*10 + (s[i]-'0');
                i++;
            }
            if (pz==0) {
                nr1 = nr;
            }
            else {
                nr2 = nr1+nr-1;
                q1.push({nr1, nr2});
            }
            pz = !pz;
            v1.push_back(nr);
        }
        i++;
    }
    f.getline(s, 100005);
    while (f.getline(s, 100005)) {
        ctr++;
        while (f.getline(s, 100005) && s[0]!=0) {
            n = strlen(s);
            i = 0;
            poz = 0;
            dims[ctr]++;
            while (i<n) {
                if (isdigit(s[i])) {
                    nr = 0;
                    while (isdigit(s[i]) && i<n) {
                        nr = nr*10 + (s[i]-'0');
                        i++;
                    }
                    if (poz==0) {
                        v[ctr][dims[ctr]].destination = nr;
                        poz++;
                    }
                    else if (poz==1) {
                        v[ctr][dims[ctr]].source = nr;
                        poz++;
                    }
                    else {
                        v[ctr][dims[ctr]].offset = nr;
                    }
                }
                i++;
            }
        }
    }
    for (int k=1;k<=ctr;k++) {
        ///for (auto el:v1) g << el << " ";
        while (!q1.empty()) {
            nr1 = q1.front().first;
            nr2 = q1.front().second;
            q1.pop();
            found = 0;
            for (int j=1;j<=dims[k] && !found;j++) {
                found = 1;
                if (v[k][j].source<=nr1 && v[k][j].source+v[k][j].offset>nr2) {
                    q2.push({nr1-v[k][j].source+v[k][j].destination, nr2-v[k][j].source+v[k][j].destination});
                }
                else if (v[k][j].source<=nr1 && nr1<=v[k][j].source+v[k][j].offset-1) {
                    q2.push({nr1-v[k][j].source+v[k][j].destination, v[k][j].destination+v[k][j].offset-1});
                    q1.push({v[k][j].source+v[k][j].offset,nr2});
                }
                else if (v[k][j].source<=nr2 && nr2<=v[k][j].source+v[k][j].offset-1) {
                    q2.push({v[k][j].destination, nr2-v[k][j].source+v[k][j].destination});
                    q1.push({nr1,v[k][j].source-1});
                }
                else if (v[k][j].source>nr1 && nr2>=v[k][j].source+v[k][j].offset) {
                    q2.push({v[k][j].destination, v[k][j].destination+v[k][j].offset-1});
                    q1.push({nr1,v[k][j].source-1});
                    q1.push({v[k][j].source+v[k][j].offset,nr2});
                }
                else found = 0;
            }
            if (!found) {
                q2.push({nr1, nr2});
            }
        }
        while (!q2.empty()) {
            ///g << q2.front().first << " " << q2.front().second << "  ";
            q1.push(q2.front());
            q2.pop();
            ///g << '\n';
        }
        ///g << '\n';
    }
    while (!q1.empty()) {
        minn = min(minn, q1.front().first);
        q1.pop();
    }
    g << minn;
    /**
    g << ctr << '\n';
    for (int i=1;i<=ctr;i++) {
        g << dims[i] << '\n';
        for (int j=1;j<=dims[i];j++) {
            g << v[i][j].first << " " << v[i][j].second << " " << v[i][j].offset << '\n';
        }
        g << '\n';
    }
    **/
    return 0;
}

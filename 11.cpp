#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <fstream>

using namespace std;

ifstream f("file.in");
ofstream g("file.out");

int fl[1005], fc[1005];

char mat[1005][1005];
int n, m;
long long tot;
long long val[1005][1005];
bool viz[1005][1005];
set < pair < long long, pair < int, int > > > s;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool valid(int x, int y) {
    if (x<0 || y<0 || x>=n || y>=m) return 0;
    if (viz[x][y]) return 0;
    return 1;
}

void bfs(int x, int y) {
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            viz[i][j] = 0;
        }
    }
    s.insert({0, {x, y}});
    viz[x][y] = 1;
    long long dst;
    while (!s.empty()) {
        dst = s.begin()->first;
        x = s.begin()->second.first;
        y = s.begin()->second.second;
        if (mat[x][y]=='#') tot += dst;
        s.erase(s.begin());
        for (int p=0;p<4;p++) {
            if (valid(x+dx[p], y+dy[p])) {
                s.insert({dst+val[x+dx[p]][y+dy[p]], {x+dx[p], y+dy[p]}});
                viz[x+dx[p]][y+dy[p]] = 1;
            }
        }
    }
}

int main()
{
    while (f.getline(mat[n], 1000)) {
        n++;
    }
    m = strlen(mat[0]);
    fill(fl, fl+n, 1);
    fill(fc, fc+m, 1);
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (mat[i][j]=='#') {
                fl[i] = 0; fc[j] = 0;
            }
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (fl[i] && fc[j]) val[i][j] = 2000000;
            else if (fl[i] || fc[j]) val[i][j] = 1000000;
            else val[i][j] = 1;
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (mat[i][j]=='#') bfs(i, j);
        }
    }
    g << tot/2;
    return 0;
}

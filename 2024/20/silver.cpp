#include <iostream>
#include <string>
#include <vector>
using namespace std;

int time;
int x, y;
vector<string> mat;
vector<vector<int>> dist;
string s;
int sx, sy, ex, ey;
int n, m, tot_dist;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int saved_time = 100, res;

bool valid(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return false;
    }
    if (mat[i][j] == '#') {
        return false;
    }
    return true;
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        mat.push_back(s);
    }
    n = mat.size(); m = mat[0].size();
    for (int i=0;i<n;i++) {
        dist.emplace_back();
        for (int j=0;j<m;j++) {
            dist[i].push_back(-1);
            if (mat[i][j] == 'S') {
                sx = i; 
                sy = j;
            }
            if (mat[i][j] == 'E') {
                ex = i;
                ey = j;
            }
        }
    }
    x = sx; y = sy;
    dist[sx][sy] = 0;
    tot_dist = 0;
    while (x != ex || y != ey) {
        for (int p=0;p<4;p++) {
            if (mat[x+dx[p]][y+dy[p]] != '#' && dist[x+dx[p]][y+dy[p]] == -1) {
                tot_dist++;
                x += dx[p]; y += dy[p];
                dist[x][y] = tot_dist;
                break;
            }
        }
    }
    x = sx; y = sy;
    while (x != ex || y != ey) {
        for (int p=0;p<4;p++) {
            if (mat[x+dx[p]][y+dy[p]] == '#' && valid(x+2*dx[p], y+2*dy[p]) && dist[x][y] + 2 + saved_time <= dist[x+2*dx[p]][y+2*dy[p]]) {
                res++;
            }
        }
        for (int p=0;p<4;p++) {
            if (dist[x+dx[p]][y+dy[p]] == dist[x][y] + 1) {
                x += dx[p]; y += dy[p];
                break; 
            }
        }
    }
    cout << res;
    return 0;
}
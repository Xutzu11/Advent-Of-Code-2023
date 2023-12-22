#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <assert.h>
using namespace std;

#define u_map unordered_map
#define u_set unordered_set
#define u_multiset unordered_multiset

using ll = long long;
using vvi = vector<vector<int>>;
using vi = vector<int>;
using vvll = vector<vector<long long>>;
using vll = vector<long long>;
using vd = vector<double>;
using vvd = vector<vector<double>>;
using pii = pair<int, int>;
using vpii = vector<pair<int, int>>;

template<typename C> struct rge { C l, r; };
template<typename C> rge<C> range(C i, C j) { return rge<C>{i, j}; }
template<typename C> ostream& operator<<(ostream& os, rge<C>& r) { os << '{'; for (auto it = r.l; it != r.r; it++) os << "," + (it == r.l) << *it; os << '}'; return os; }
template<typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << '{' << p.first << "," << p.second << '}'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream& os, const T_container& v) { os << '{'; string sep; for (const T& x : v) os << sep << x, sep = ","; return os << '}'; }
void dbg_out() { cerr << ']' << endl; }
template<typename A> void dbg_out(A H) { cerr << H; dbg_out(); }
template<typename A, typename B, typename... C> void dbg_out(A H, B G, C... T) { cerr << H << ","; dbg_out(G, T...); }
#ifdef DEBUG
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = [", dbg_out(__VA_ARGS__)
#else
#define debug(...)
#endif

pii DIRS[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

pii operator+(pii x, pii y) {
    return { x.first + y.first, x.second + y.second };
}

const int STEPS = 26501365;
// const int STEPS = 6;
ifstream fin("input.txt");
const int N = 131;

void solve() {
    vector<string> input;
    while (true) {
        string s;
        fin >> s;
        if (!fin) break;
        input.push_back(s);
    }

    int n = input.size();
    int m = input[0].size();
    assert(n == N && m == N);

    vector<vector<char>> g(3 * N, vector<char>(3 * N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int a = 0; a < 3; a++) {
                for (int b = 0; b < 3; b++) {
                    g[i + a * N][j + b * N] = (input[i][j] == 'S' && (a != 1 || b != 1)) ? '.' : input[i][j];
                }
            }
        }
    }

    pii start;
    for (int i = 0; i < 3 * N; i++) {
        for (int j = 0; j < 3 * N; j++) {
            if (g[i][j] == 'S') {
                start = { i, j };
            }
        }
    }

    vvi dist(3 * N, vi(3 * N));

    vector<vector<bool>> vis(3 * N, vector<bool>(3 * N));
    queue<pii> q;
    q.push(start);
    vis[start.first][start.second] = true;

    auto inside = [&](pii p) {
        return 0 <= p.first && p.first < 3 * N && 0 <= p.second && p.second < 3 * N;
        };

    while (!q.empty()) {
        pii u = q.front();
        q.pop();
        for (int j = 0; j < 4; j++) {
            pii d = DIRS[j];
            pii v = u + d;
            if (inside(v) && g[v.first][v.second] != '#' && !vis[v.first][v.second]) {
                vis[v.first][v.second] = true;
                dist[v.first][v.second] = dist[u.first][u.second] + 1;
                q.push(v);
            }
        }
    }

    vll dp(STEPS + 1000);
    for (int i = STEPS; i >= 0; i--) {
        dp[i] = (i % 2 == STEPS % 2) + 2 * dp[i + N] - dp[i + 2 * N];
    }

    debug(dp);


    ll ans = 0;
    for (int i = 0; i < 3 * N; i++) {
        for (int j = 0; j < 3 * N; j++) {
            if (!vis[i][j]) continue;
            int dx = i - start.first;
            int dy = j - start.second;
            if (-N <= dx && dx < N && -N <= dy && dy < N) {
                if (dp[dist[i][j]] > 0) {
                    debug(i, j, dist[i][j], dp[dist[i][j]]);
                }
                ans += dp[dist[i][j]];
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <assert.h>
using namespace std;

ifstream f("file.in");
ofstream g("file.out");

vector < long long > v[100005];
char s[100005];
bool x;
bool ok;
long long nr, el1, el2, tot;
int ctr, n, i, line;
int neg;

int main()
{
	while (f.getline(s, 100000)) {
		n = strlen(s);
		i = 0;
		while (i < n) {
			if (s[i] == '-') neg = 1;
			if (isdigit(s[i])) {
				nr = 0;
				while (i < n && isdigit(s[i])) {
					nr = nr * 10 + (s[i] - '0');
					i++;
				}
				if (neg == 1) nr = -nr;
				v[1].push_back(nr);
				neg = 0;
			}
			i++;
		}
		line = 1;
		ok = 1;
		while (ok) {
			ok = 0;
			x = 0;
			for (i = 1; i < v[line].size(); i++) {
				x = 1;
				nr = v[line][i] - v[line][i - 1];
				v[line + 1].push_back(nr);
				if (nr != 0) ok = 1;
			}
			line++;
		}
		assert(x == 1);
		v[line].push_back(0);
		for (i = line - 1; i >= 1; i--) {
			el1 = v[i + 1][0];
			el2 = v[i][0];
			v[i].insert(v[i].begin(), el2 - el1);
		}
		tot += v[1][0];
		for (i = 1; i <= line; i++) {
			for (auto k : v[i]) g << k << " ";
			g << '\n';
			v[i].clear();
		}
		g << tot << '\n';
	}
	g << tot;
	return 0;
}

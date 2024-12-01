#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <set>
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

map < string, int > value, position;
int tot;
int c;
char s[100005];
int n;
set < pair  < int, string > > boxes[256];
int i;
int ctr;
int tip, nr;
string label;

int main() {
	f >> s;
	n = strlen(s);
	i = 0;
	while (i < n) {
		c = 0;
		ctr++;
		label = "";
		while (s[i] != '=' && s[i]!='-') {
			c += s[i];
			label += s[i];
			c *= 17;
			c %= 256;
			i++;
		}
		if (s[i] == '-') {
			i++;
			if (value[label] != 0) {
				boxes[c].erase({ position[label], label });
				value.erase(label);
				position.erase(label);
			}
		}
		else {
			i++;
			nr = 0;
			while (i < n && s[i] != ',') {
				nr = nr * 10 + (s[i] - '0');
				i++;
			}
			if (value[label] != 0) {
				value[label] = nr;
			}
			else {
				value[label] = nr;
				position[label] = ctr;
				boxes[c].insert({ position[label], label });
			}
		}
		i++;
	}
	for (int i = 0; i < 256; i++) {
		int ps = 1;
		for (auto k : boxes[i]) {
			tot += (i + 1) * ps * value[k.second];
			ps++;
		}
	}
	g << tot;
	return 0;
}

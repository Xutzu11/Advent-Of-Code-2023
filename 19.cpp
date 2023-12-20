#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <assert.h>
using namespace std;

ifstream f("aoc.in");
ofstream g("aoc.out");

int vals[10];
int ctr;
char s[100005];
int i, n;
string mapper, current;
char tip, op;
int nr;
string go;

struct Node {
	int st[5], dr[5];
	string go;
	int pos;
};

Node newnode(int changed, int st, int dr, string next, int pos, Node last) {
	Node x;
	for (int i = 1; i <= 4; i++) {
		x.st[i] = last.st[i];
		x.dr[i] = last.dr[i];
	}
	x.st[changed] = st; x.dr[changed] = dr;
	x.go = next;
	x.pos = pos;
	return x;
}

queue < Node > q;

struct Operation{
	char op;
	int tip, nr;
	string go;
};

map < char, int > ops;
Operation newop(int tip, char op, int nr, string go) {
	Operation a;
	a.tip = tip; a.op = op;
	a.nr = nr; a.go = go;
	return a;
}
map < string, vector < Operation > > mp;
long long tot;

void part1() {
	while (f.getline(s, 100000)) {
		i = 0, n = strlen(s), ctr = 0;
		while (i < n) {
			if (isdigit(s[i])) {
				nr = 0;
				while (i < n && isdigit(s[i])) {
					nr = nr * 10 + (s[i] - '0');
					i++;
				}
				vals[++ctr] = nr;
			}
			i++;
		}
		int ok = 0;
		current = "in";
		while (ok == 0) {
			if (current == "A") {
				ok = 1; break;
			}
			if (current == "R") {
				ok = 2; break;
			}
			for (auto k : mp[current]) {
				if (k.tip == 0)
					current = k.go;
				else if (k.op == '<' && vals[k.tip] < k.nr)
					current = k.go;
				else if (k.op == '>' && vals[k.tip] > k.nr)
					current = k.go;
				else continue;
				break;
			}
		}
		if (ok == 1) {
			tot += vals[1] + vals[2] + vals[3] + vals[4];
		}
	}
	g << tot;
}

void part2() {
	Node first;
	for (int i = 1; i <= 4; i++) {
		first.st[i] = 1; first.dr[i] = 4000;
	}
	first.go = "in";
	first.pos = 0;
	q.push(first);
	while (!q.empty()) {
		Node c = q.front();
		q.pop();
		if (c.go == "A") {
			long long now = 1;
			for (int i = 1; i <= 4; i++) {
				now *= (c.dr[i] - c.st[i] + 1);
			}
			tot += now;
			continue;
		}
		else if (c.go == "R") continue;
		Operation cop = mp[c.go][c.pos];
		if (cop.tip == 0) {
			q.push(newnode(0, 0, 0, cop.go, 0, c));
		}
		else if (cop.op == '<') {
			if (c.dr[cop.tip] < cop.nr) {
				q.push(newnode(0, 0, 0, cop.go, 0, c));
			}
			else if (c.st[cop.tip] >= cop.nr) {
				q.push(newnode(0, 0, 0, c.go, c.pos + 1, c));
			}
			else {
				q.push(newnode(cop.tip, c.st[cop.tip], cop.nr - 1, cop.go, 0, c));
				q.push(newnode(cop.tip, cop.nr, c.dr[cop.tip], c.go, c.pos + 1, c));
			}
		}
		else if (cop.op == '>') {
			if (c.st[cop.tip] > cop.nr) {
				q.push(newnode(0, 0, 0, cop.go, 0, c));
			}
			else if (c.dr[cop.tip] <= cop.nr) {
				q.push(newnode(0, 0, 0, c.go, c.pos + 1, c));
			}
			else {
				q.push(newnode(cop.tip, c.st[cop.tip], cop.nr, c.go, c.pos + 1, c));
				q.push(newnode(cop.tip, cop.nr + 1, c.dr[cop.tip], cop.go, 0, c));
			}
		}
		else assert(false);
	}
	g << tot;
}

int main()
{
	ops['x'] = 1; ops['m'] = 2; ops['a'] = 3; ops['s'] = 4;
	f.getline(s, 100000);
	while (s[0]!=0) {
		i = 0, n = strlen(s);
		mapper = "";
		while (s[i] != '{') {
			mapper += s[i];
			i++;
		}
		i++;
		while (i < n) {
			if (s[i + 1] == '<' || s[i + 1] == '>') {
				tip = s[i]; i++;
				op = s[i]; i++;
				nr = 0;
				while (s[i] != ':') {
					nr = nr * 10 + (s[i] - '0');
					i++;
				}
				i++;
				go = "";
				while (isalpha(s[i])) {
					go += s[i];
					i++;
				}
				mp[mapper].push_back(newop(ops[tip], op, nr, go));
			}
			else {
				go = "";
				while (s[i] != '}') {
					go += s[i];
					i++;
				}
				mp[mapper].push_back(newop(0, '0', 0, go));
			}
			i++;
		}
		f.getline(s, 100000);
	}
	/// part1();
	part2();
}

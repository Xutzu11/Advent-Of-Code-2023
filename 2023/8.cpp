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

map < string, int > mp;

char s[10005];
char steps[10005];
string source, node1, node2;
pair < string, string > nodes[10005];
int ctr;
long long nrstep[1005];
int cstep[1005];
int end[300][1005];
int it;
int totstep;
vector < string > cnode;
bool ok;
string inc;

long long cmmdc(long long a, long long b) {
	long long r = 1;
	while (r) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main()
{
	f >> steps;
	f.get(); f.get();
	while (f.getline(s, 10005)) {
		source = ""; node1 = ""; node2 = "";
		source += s[0]; source += s[1]; source += s[2];
		node1 += s[7]; node1 += s[8]; node1 += s[9];
		node2 += s[12]; node2 += s[13]; node2 += s[14];
		nodes[++ctr] = { node1, node2 };
		mp[source] = ctr;
		if (source[2] == 'A') cnode.push_back(source);
	}
	totstep = strlen(steps);
	for (int i = 0; i < cnode.size(); i++) {
		cstep[i] = 0;
		while (cnode[i][2]!='Z') {
			cstep[i] %= totstep;
			if (steps[cstep[i]] == 'L') {
				cnode[i] = nodes[mp[cnode[i]]].first;
			}
			else {
				cnode[i] = nodes[mp[cnode[i]]].second;
			}
			nrstep[i]++;
			cstep[i]++;
		}
		g << nrstep[i] << " ";
		assert(nrstep[i] % totstep == 0);
		nrstep[i] /= totstep;
	}
	long long cmdc = cmmdc(nrstep[0], nrstep[1]);
	long long cmmmc = nrstep[0] * nrstep[1] / cmdc;
	for (int i = 2; i < cnode.size(); i++) {
		cmdc = cmmdc(cmmmc, nrstep[i]);
		cmmmc = cmmmc * nrstep[i] / cmdc;
	}
	g << cmmmc*totstep;
	return 0;
}

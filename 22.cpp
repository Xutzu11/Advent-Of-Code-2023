#include <fstream>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

char s[1005];
int x, y, z, rez;
int coord[7];
int ctr;
int tot;
map < pair < int, pair < int, int > > , int > occ; // occupancy map for 3d cubes of bricks
set < int > sustains[1500]; // sustains[i] = the bricks sustained by brick i
set < int > is_sustained[1500], copy_is_sustained[1500]; 
set < int > would_fall;
queue < int > q;

struct Brick {
	int x1, y1, z1;
	int x2, y2, z2;
}b[10005];

Brick newbrick() {
	Brick b;
	b.x1 = coord[0]; b.y1 = coord[1]; b.z1 = coord[2];
	b.x2 = coord[3]; b.y2 = coord[4]; b.z2 = coord[5];
	/// mark the cube positions as occupied
	for (int i = b.x1; i <= b.x2; i++) {
		for (int j = b.y1; j <= b.y2; j++) {
			for (int k = b.z1; k <= b.z2; k++) {
				occ[{i, { j, k }}] = ctr;
			}
		}
	}
	return b;
}

bool zsort(Brick a, Brick b) {
	return min(a.z1, a.z2) < min(b.z1, b.z2);
}

void set_occ(int br, int t) {
	for (int i = b[br].x1; i <= b[br].x2; i++) {
		for (int j = b[br].y1; j <= b[br].y2; j++) {
			for (int k = b[br].z1; k <= b[br].z2; k++) {
				occ[{i, { j, k }}] = t;
			}
		}
	}
}

void fall(int x) {
	bool ok = 1;
	Brick br = b[x];
	while (ok) {
		set_occ(x, 0);
		for (int i = br.x1; i <= br.x2; i++) {
			for (int j = br.y1; j <= br.y2; j++) {
				for (int k = br.z1; k <= br.z2; k++) {
					if (k - 1 == 0 || occ[{i, { j, k-1 }}] != 0) ok = 0;
				}
			}
		}
		if (ok) {
			br.z1--; br.z2--;
		}
	}
	b[x] = br;
	set_occ(x, x);
}

int disintegrate(int x) {
	bool ok = 1;
	for (auto k : sustains[x]) {
		if (is_sustained[k].size() == 1) ok = 0;
	}
	return ok;
}

void find_sustaining(int x) {
	Brick br = b[x];
	for (int i = br.x1; i <= br.x2; i++) {
		for (int j = br.y1; j <= br.y2; j++) {
			for (int k = br.z1; k <= br.z2; k++) {
				if (occ[{i, { j, k + 1 }}] != 0 && occ[{i, { j, k + 1 }}] != x) {
					is_sustained[occ[{i, { j, k + 1 }}]].insert(x);
					sustains[x].insert(occ[{i, { j, k + 1 }}]);
				}
			}
		}
	}
}

int simulate_fall(int x) {
	int tot = 0;
	q.push(x);
	while (!q.empty()) {
		tot++;
		int br = q.front();
		q.pop();
		for (auto k : sustains[br]) {
			copy_is_sustained[k].erase(br);
			if (copy_is_sustained[k].empty()) q.push(k);
		}
	}
	return tot-1;
}

int main() 
{
	while (f >> s) {
		int i = 0;
		ctr++;
		for (int p = 0; p < 6; p++) {
			coord[p] = 0;
			while (isdigit(s[i])) {
				coord[p] = coord[p] * 10 + (s[i] - '0');
				i++;
			}
			i++;
		}
		b[ctr] = newbrick();
	}
	sort(b + 1, b + ctr + 1, zsort);
	for (int i = 1; i <= ctr; i++) {
		fall(i);
	}
	for (int i = 1; i <= ctr; i++) {
		find_sustaining(i);
	}
	for (int i = 1; i <= ctr; i++) {
		rez += disintegrate(i);
	}
	g << rez << '\n'; /// part 1

	rez = 0;
	for (int i = 1; i <= ctr; i++) {
		for (int j = 1; j <= ctr; j++) {
			copy_is_sustained[j].clear();
			copy_is_sustained[j].insert(is_sustained[j].begin(), is_sustained[j].end());
		}
		rez += simulate_fall(i);
	}
	g << rez; /// part 2
	return 0;
}
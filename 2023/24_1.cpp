#include <fstream>
#include <cstring>
#define low 200000000000000
#define high 400000000000000
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

int neg;
int rez;
struct Hailstone {
	double px, py, pz;
	double vx, vy, vz;
}v[10005];
int ctr;
double t, u, cx, cy, ax, ay, bx, by, det;
double coord[6];
double x, y, z;
char s[1005];

Hailstone newstone() {
	Hailstone k;
	k.px = coord[0]; k.py = coord[1]; k.pz = coord[2];
	k.vx = coord[3]; k.vy = coord[4]; k.vz = coord[5];
	return k;
}
/// Assumption: there are no null velocities

int main() 
{
	while (f.getline(s, 1000)) {
		int i = 0;
		for (int p = 0; p < 6; p++) {
			neg = 1;
			coord[p] = 0;
			while (isdigit(s[i]) == 0) {
				if (s[i] == '-') neg = -1;
				i++;
			}
			while (isdigit(s[i])) {
				coord[p] = coord[p] * 10 + (s[i] - '0');
				i++;
			}
			coord[p] *= neg;
		}
		v[++ctr] = newstone();
	}
	for (int i = 1; i < ctr; i++) {
		for (int j = i+1; j <= ctr; j++) {
			ax = -v[i].vx, bx = v[j].vx, cx = v[i].px - v[j].px; 
			ay = -v[i].vy, by = v[j].vy, cy = v[i].py - v[j].py;
			det = ax * by - ay * bx;
			if (det == 0) continue;
			t = (cx * by - cy * bx) / det, u = (ax * cy - ay * cx) / det;
			x = v[i].px + t * v[i].vx;
			y = v[i].py + t * v[i].vy;
			if (x >= low && x <= high && y >= low && y <= high && (x - v[i].px) / v[i].vx > 0 && (x - v[j].px) / v[j].vx > 0) {
				rez++;
			}
		}
	}
	g << rez;
	return 0;
}
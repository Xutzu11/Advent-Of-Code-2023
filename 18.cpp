#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
using namespace std;
ifstream f("aoc.in");
ofstream g("aoc.out");

char op;
map < char, pair < long long, long long > > mp;
long long ctr;
int nr;
long long x, y;
vector < pair < long long, long long > > v;
string color;
long long area;

int hex(char x) {
	if ('0' <= x && x <= '9') return (x - '0');
	else return (x - 'a') + 10;
}

char int_to_char(int x) {
	if (x == 0) return 'R';
	if (x == 1) return 'D';
	if (x == 2) return 'L';
	if (x == 3) return 'U';
	return 0;
}

int conv_nr(string color) {
	int p = 1;
	int nr = 0;
	for (int i = 6; i >= 2; i--) {
		nr += hex(color[i]) * p;
		p *= 16;
	}
	return nr;
}

int main()
{
	mp['L'] = { 0, -1 };
	mp['U'] = { -1, 0 };
	mp['D'] = { 1, 0 };
	mp['R'] = { 0, 1 };
	v.push_back({ 0, 0 });
	while (f >> op) {
		f >> nr >> color;
		nr = conv_nr(color);
		op = int_to_char(color[7] - '0');
		x += mp[op].first*nr;
		y += mp[op].second * nr;
		ctr += abs(mp[op].first * nr + mp[op].second * nr);
		v.push_back({ x, y });
	}
	for (int i = 0; i < v.size()-1; i++) {
		area += v[i].first * v[i + 1].second - v[i].second * v[i + 1].first;
	}
	g << ctr/2 + abs(area)/2 + 1;
}

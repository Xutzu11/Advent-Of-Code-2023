#include <fstream> 
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

/// flip-flop modules: %
/// on or off (initially off)
/// high pulse -> nothing
/// low pulse and off -> switch on + send high pulse
/// low pulse and on -> switch off + send low pulse


/// conjunction modules: &
/// remember recent pulses from all modules (initially low)
/// update module
/// if all is high -> send low pulse
/// else -> send high pulse

/// broadcast module -> send the same pulse to everyone
/// at start, low pulse is sent to broadcast

ifstream f("aoc.in");
ofstream g("aoc.out");
char s[100005];
int i, type, n, pulse_type;
string mdl, con, who;
map < string, vector < string > > connect;
map < string, set < string > > inv_connect;
map < string, int > types;
map < string, bool > ff; /// flip-flop modules
map < string, pair < set < string >, set < string > > > conj; /// set for low, set for high
queue < pair < int, string > > q;
long long tot_low, tot_high;
int press;
// low = 0, high = 1
map < string, int > high_sends; /// register when do the modules connected to bq (which is connected to rx) send highs
/// Assumptions:
/// 1. there is a single conjunction module connected to rx - module bq (as seen in input file)
/// 2. there are 4 modules, all conjunction modules, connected to bq (as seen in input file)
/// 3. the modules send high pulses to bq in a perfect cycle - every k presses 
/// this k is different for each module, but it's the same for the certain module (as tested)
/// Solve: Find the lowest common multiple of the cycles
void flipflop(int pulse, string module) {
	if (pulse == 1) return;
	ff[module] = !ff[module];
	for (auto k : connect[module]) {
		if (types[k] == 1) {
			if (ff[module] == 0) {
				conj[k].second.erase(module);
				conj[k].first.insert(module);
			}
			else {
				conj[k].first.erase(module);
				conj[k].second.insert(module);
			}
		}
		// g << module << " -" << ff[module] << "-> " << k << '\n';
		q.push({ ff[module],k });
	}
}

void conjunctions(int pulse, string module) {
	int all = conj[module].first.size();
	for (auto k : connect[module]) {
		if (all == 0) {
			q.push({ 0, k });
			if (types[k] == 1) {
				conj[k].second.erase(module);
				conj[k].first.insert(module);
			}
		}
		else {
			q.push({ 1, k });
			if (k == "bq") {
				high_sends[module] = press;
				inv_connect[k].erase(module);
			}
			if (types[k] == 1) {
				conj[k].first.erase(module);
				conj[k].second.insert(module);
			}
		}
		// g << module << " -" << (all != 0) << "-> " << k << '\n';
	}
}


void broadcast(int pulse, string module) {
	for (auto k : connect[module]) {
		q.push({ pulse, k });
		// g << module << " -" << pulse << "-> " << k << '\n';
	}
}

int main() 
{
	while (f.getline(s, 100000)) {
		i = 1; n = strlen(s);
		mdl = "";
		if (s[0] == '%') type = 0;
		else if (s[0] == '&') type = 1;
		else {
			type = 2;
			mdl = "b";
		}
		while (isalpha(s[i])) {
			mdl += s[i]; 
			i++;
		}
		types[mdl] = type;
		i += 4;
		while (i < n) {
			con = "";
			while (i < n && isalpha(s[i])) {
				con += s[i];
				i++;
			}
			connect[mdl].push_back(con);
			inv_connect[con].insert(mdl);
			i += 2;
		}
	}
	for (auto k : types) {
		if (k.second == 0) {
			ff[k.first] = 0;
		}
		else if (k.second == 1) {
			for (auto low : inv_connect[k.first]) {
				conj[k.first].first.insert(low);
			}
		}
	}
	bool ok = 0;
	while(1) {
		press++;
		/// if (press == 1000) break;
		if (inv_connect["bq"].size() == 0) break; /// we found the cycle for each button needed
		q.push({ 0, "broadcaster" });
		// g << "button -0-> broadcaster\n";
		while (!q.empty()) {
			pulse_type = q.front().first;
			who = q.front().second;
			q.pop();
			/// if (who == "rx" && pulse_type == 0) ok = 1;
			tot_low += (pulse_type == 0);
			tot_high += (pulse_type == 1);
			if (types[who] == 0) {
				flipflop(pulse_type, who);
			}
			else if (types[who] == 1) {
				conjunctions(pulse_type, who);
			}
			else {
				broadcast(pulse_type, who);
			}
		}
		// g << '\n';
	}
	/// g << tot_low*tot_high << '\n'; /// part 1 result
	long long last_cmmmc = 1, cmmdc = 1, cmmmc = 1, r, a, b;
	for (auto x : high_sends) {
		last_cmmmc = cmmmc;
		a = x.second, b = last_cmmmc, r = 1;
		while (r != 0) {
			r = a % b;
			a = b;
			b = r;
		}
		cmmdc = a;
		cmmmc = (x.second * last_cmmmc) / cmmdc;
	}
	g << cmmmc; /// part 2 result
}
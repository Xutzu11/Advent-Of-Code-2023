#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

unordered_set<int> edges[26 * 26 + 1];
map<string, int> code;
map<int, string> rev_code;
string s1, s2;
string s;
int comps = 0;
vector<int> viz;
unordered_set<int> max_clique, starting_possible;
vector<string> final_clique;

void find_clique(unordered_set<int> clique, unordered_set<int> possible, unordered_set<int> visited) {
    if (possible.empty() && visited.empty()) {
        if (clique.size() > max_clique.size()) {
            max_clique.clear();
            max_clique = clique;
        }
        return;
    } 
    while (!possible.empty()) {
        unordered_set<int> next_possible = possible, next_visited = visited, next_clique = clique;
        int k = *possible.begin();
        next_clique.insert(k);
        for (auto &p:possible) {
            if (!edges[k].count(p)) {
                next_possible.erase(p);
            }
        }
        for (auto &p:visited) {
            if (!edges[k].count(p)) {
                next_visited.erase(p);
            }
        }
        find_clique(next_clique, next_possible, next_visited);
        possible.erase(k);
        visited.insert(k);
    }
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    while (cin >> s) {
        s1 = s[0]; s1 += s[1];
        code[s1] = (code[s1] ? code[s1] : (++comps));
        rev_code[code[s1]] = s1;
        s2 = s[3]; s2 += s[4];
        code[s2] = (code[s2] ? code[s2] : (++comps));
        rev_code[code[s2]] = s2;
        edges[code[s1]].insert(code[s2]);
        edges[code[s2]].insert(code[s1]);
    }
    viz = (vector<int>(comps + 1));
    for (int i=1;i<=comps;i++) {
        starting_possible.insert(i);
    }
    find_clique({}, starting_possible, {});
    for (auto p:max_clique) {
        final_clique.push_back(rev_code[p]);
    }
    sort(final_clique.begin(), final_clique.end());
    string conc_clique = "";
    for (auto comp:final_clique) {
        conc_clique += comp + ",";
    }
    conc_clique.pop_back();
    cout << conc_clique;
    return 0;
}
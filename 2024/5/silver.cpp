#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

int sum;
string s;
set < pair < int, int > > rules; 
vector < int > print;

void add_rule() {
    int n = 0, m = 0;
    bool k = true;
    for (auto c:s) {
        if (c == '|') {
            k = false;
        }
        else if (k) {
            n = n*10 + c-'0';
        }
        else {
            m = m*10 + c-'0';
        }
    }
    rules.insert({n, m});
}

void get_pages() {
    s += ",";
    int n = 0;
    print.clear();
    for (auto c:s) {
        if (c == ',') {
            print.push_back(n);
            n = 0;
        }
        else {
            n = n*10 + c-'0';
        }
    }
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    getline(cin, s);
    while (s != "") {
        add_rule();
        getline(cin, s);
    }
    while (getline(cin, s)) {
        get_pages();
        bool correct = true;
        for (int i=1;i<print.size();i++) {
            for (int j=i-1;j>=0;j--) {
                correct &= rules.count({print[i], print[j]}) == 0;
            }
        }
        sum += correct * print[print.size()/2];
    }
    cout << sum;
    return 0;
}
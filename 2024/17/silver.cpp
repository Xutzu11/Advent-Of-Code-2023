#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
using namespace std;

string s;
long long a, b, c;
long long zero = 0, one = 1, two = 2, three = 3;
int k;
vector<int> ops;
map<int, function<void()>>otf;
map<int, long long*> combo;
string res = "";

void read_register(long long &reg) {
    getline(cin, s);
    reg = 0;
    int i = string("Register X: ").size();
    while (isdigit(s[i])) {
        reg = reg*10 + s[i] - '0';
        i++;
    }
}

void adv() {
    a = (a / (1<<(*combo[ops[k+1]])));
}

void bxl() {
    b = (b ^ ops[k+1]);
}

void bst() {
    b = (*combo[ops[k+1]] % 8);
}

void jnz() {
    if (a != 0) {
        k = 2*(ops[k+1]-1);
    }
}

void bxc() {
    b = (b ^ c);
}

void out() {
    res += to_string(*combo[ops[k+1]] % 8)  + ",";
}

void bdv() {
    b = (a / (1<<(*combo[ops[k+1]])));
}

void cdv() {
    c = (a / (1<<(*combo[ops[k+1]])));
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    
    otf[0] = &adv;
    otf[1] = &bxl;
    otf[2] = &bst;
    otf[3] = &jnz;
    otf[4] = &bxc;
    otf[5] = &out;
    otf[6] = &bdv;
    otf[7] = &cdv;
    
    combo[0] = &zero;
    combo[1] = &one;
    combo[2] = &two;
    combo[3] = &three;
    combo[4] = &a;
    combo[5] = &b;
    combo[6] = &c;
    combo[7] = NULL;

    read_register(a);
    read_register(b);
    read_register(c);
    getline(cin, s);

    getline(cin, s);
    int i = string("Program: ").size();
    while (i < s.size()) {
        ops.push_back(s[i]-'0');
        i += 2;
    }
    k = 0;
    while (k < ops.size() - 1) {
        otf[ops[k]]();
        k += 2;
    } 
    res.pop_back();
    cout << res;
    return 0;
}
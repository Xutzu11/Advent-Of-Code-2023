#include <iostream>
#include <string>
using namespace std;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);

    string s;
    long long sum = 0;
    bool enabled = true;
    while (getline(cin ,s)) {
        for (int i=0;i<s.size()-6;i++) {
            if (s.substr(i, 4) == "do()") enabled = true;
            if (s.substr(i, 7) == "don't()") enabled = false;
            if (enabled && s.substr(i, 4) == "mul(") {
                int j = i + 4;
                bool ok1 = false, ok2 = false;
                long long n1 = 0, n2 = 0;
                while (isdigit(s[j]) && j<s.size()) {
                    ok1 = true;
                    n1 = n1*10 + (s[j]-'0');
                    j++; 
                }
                if (j>=s.size() || s[j] != ',') ok1 = false;
                j++;
                while (isdigit(s[j]) && j<s.size()) {
                    ok2 = true;
                    n2 = n2*10 + (s[j]-'0');
                    j++;
                }
                if (j>=s.size() || s[j] != ')') ok2 = false;
                if (ok1 && ok2) sum += n1*n2;
            }
        }
    }
    cout << sum;
    return 0;
}
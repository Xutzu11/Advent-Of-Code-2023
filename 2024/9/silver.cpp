#include <iostream>
#include <vector>
#include <string>
using namespace std;

long long n, p, res = 0;
string s;

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
    cin >> s;
    for (int i=0;i<s.size();i++) {
        n += s[i]-'0';
    }
    vector<int> v(n, -1);
    for (int i=0;i<s.size();i++) {
        if (i%2==0) {
            for (int j=p;j<p+s[i]-'0';j++) {
                v[j] = i/2;
            }
        }
        p += s[i]-'0';
    }
    int i = 0, j = n - 1;
    while (i < j) {
        if (v[j] == -1) {
            j--;
        }
        else {
            while (i < j && v[i] != -1) {
                i++;
            }
            swap(v[i], v[j]);
            j--;
            i++;
        }
    }
    for (int i=0;i<n;i++) {
        res += (v[i] == -1) ? 0 : i*v[i];
    }
    cout << res;
    return 0;
}
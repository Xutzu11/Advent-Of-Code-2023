#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> ops = {2,4,1,2,7,5,1,3,4,3,5,5,0,3,3,0};
long long a, min_a;

void bkt(int p) {
    for (int i = 0; i < 8; i++) {
        a += i;
        if (a == 0) continue;
        long long b, c;
        b = a % 8;
        b = b ^ 2;
        c = a / (1<<b);
        b = b ^ 3;
        b = b ^ c;
        if (b % 8 == ops[p]) {
            if (p == 0) {
                min_a = min(min_a, a);
            }
            else {
                a *= 8;
                bkt(p-1);
                a /= 8;
            }
        }
        a -= i;
    }
}

int main() {
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);

    min_a = LLONG_MAX;
    a = 0;
    bkt(ops.size() - 1);
    cout << min_a;
    return 0;
}

/*
Let's analyze the program:
2,4 (b = a % 8)
1,2 (b = b ^ 2)
7,5 (c = a / (1<<b))
1,3 (b = b ^ 3)
4,3 (b = b ^ c)
5,5 (output b % 8)
0,3 (a = a / (1<<3))
3,0 (if a != 0 => jump to start --- else exit)

We can see that b and c are computed independently of their initial value (they only depend on a).
We can also deduce that the program iterates 3 bits of a at a time.
So, for n numbers to be printed, the number should have 3*n bits.
We can backtrack through numbers and add 3 bits at each step.
*/
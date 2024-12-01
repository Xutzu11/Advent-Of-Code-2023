#include <iostream>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("file.in");
ofstream g("file.out");

map < char, int > card;
set < pair < int, char > > s1,s2;
map < char, int > mp1, mp2;

pair < string, int > v[10005];
string s;
int nr, n, ctr1, ctr2, maxap1, maxap2;
long long tot;
char ch1, ch2;
set < pair < int, char > > :: reverse_iterator it1, it2;

bool cmp(pair< string, int > a, pair < string, int  > b) {
    mp1.clear();
    mp2.clear();
    s1.clear();
    s2.clear();
    ctr1 = ctr2 = 0;
    maxap1 = maxap2 = 0;
    ch1 = ch2 = 0;
    for (auto k:a.first) {
        if (k=='J') ctr1++;
        else {
            mp1[k]++;
            if (mp1[k]>maxap1 || (mp1[k]==maxap1 && card[k]>card[ch1])) {
                maxap1 = mp1[k]; ch1 = k;
            }
        }
    }
    if (ctr1==5) mp1['A']=5;
    else mp1[ch1] += ctr1;
    for (auto k:b.first) {
        if (k=='J') ctr2++;
        else {
            mp2[k]++;
            if (mp2[k]>maxap2 || (mp2[k]==maxap2 && card[k]>card[ch2])) {
                maxap2 = mp2[k]; ch2 = k;
            }
        }
    }
    if (ctr2==5) mp2['A']=5;
    else mp2[ch2] += ctr2;
    for (auto k:mp1) {
        s1.insert({k.second, card[k.first]});
    }
    for (auto k:mp2) {
        s2.insert({k.second, card[k.first]});
    }
    it1 = s1.rbegin(); it2 = s2.rbegin();
    while (it1!=s1.rend() && it2!=s2.rend()) {
        if (it1->first>it2->first) return 0;
        else if (it1->first<it2->first) return 1;
        ///else if (it1->second>it2->second) return 0;
        ///else if (it1->second<it2->second) return 1;
        else {++it1; ++it2;}
    }
    for (int i=0;i<5;i++) {
        if (card[a.first[i]]>card[b.first[i]]) return 0;
        if (card[a.first[i]]<card[b.first[i]]) return 1;
    }
    return 1;
}

int main()
{
    card['2']=1; card['3']=2; card['4']=3; card['5']=4;
    card['6']=5; card['7']=6; card['8']=7; card['9']=8;
    card['T']=9; card['J']=0; card['Q']=11; card['K']=12;
    card['A'] = 13;
    while (f >> s) {
        f >> nr;
        v[++n] = {s, nr};
    }
    for (int i=1;i<n;i++) {
        for (int j=i+1;j<=n;j++) {
            if (cmp(v[i], v[j])==0) swap(v[i], v[j]);
        }
    }
    for (long long i=1;i<=n;i++) {
        g << v[i].first << " " << v[i].second << "\n";
        tot += i*v[i].second;
    }
    g << tot;
    return 0;
}

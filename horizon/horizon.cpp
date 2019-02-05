#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <assert.h>
#include <limits>
#include <cstdio>
using namespace std;

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif
#define inf 0x7fffffff


typedef char        		b8;
typedef int         		b32;
typedef long long   		b64;
typedef unsigned char 	 	ub8;
typedef unsigned int    	ub32;
typedef unsigned long long 	ub64;

struct building {
    long long f,s,h,i;
};

building bds[40010];
pair<long long,long long> pts[80010];
long long N, k;

bool cmp2(pair<int,int> a, pair<int,int> b) {
    return a.first != b.first ? a.first<b.first : bds[a.second].h<bds[b.second].h;
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i<N; i++) {
        cin >> bds[i].f >> bds[i].s >> bds[i].h;
        bds[i].i = i;
        pts[k].first = bds[i].f;
        pts[k].second = bds[i].i;
        k++;
        pts[k].first = bds[i].s;
        pts[k].second = bds[i].i;
        k++;
    }
    // cout << endl;
    long long totarea = 0;
    sort(pts, pts+N*2, cmp2);
    // for (int i = 0; i<N*2; i++) {
    //   cout << pts[i].first << " " << pts[i].second << endl;
    // }
    // cout << endl;
    auto cmp = [](long long a, long long b) {return bds[a].h>bds[b].h;};
    long long lastval = 0;
    set<long long, decltype(cmp)> s(cmp);
    for (int i = 0; i<N*2; i++) {
        if (s.empty()) {
            s.insert(pts[i].second);
            // cout << pts[i].second << " ";
            lastval = pts[i].first;
            // cout << "asdfasdf " << pts[i].first << endl;
            continue;
        }
        long long tomult = bds[(*(s.begin()))].h;
        if (s.find(pts[i].second) != s.end()) {
            s.erase(pts[i].second);
            // cout << pts[i].second << " " << lastval << " " << pts[i].first << " " << tomult << "first" << endl;
            totarea+=(pts[i].first-lastval)*tomult;
            lastval = pts[i].first;
        } else {
            s.insert(pts[i].second);
            // cout << pts[i].second << " " << lastval << " " << pts[i].first << " " << tomult << endl;
            totarea+=(pts[i].first-lastval)*tomult;
            lastval = pts[i].first;
        }
    }
    // cout << endl;
    cout << totarea << endl;
    return 0;
}



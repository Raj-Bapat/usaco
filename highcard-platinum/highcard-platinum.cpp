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

int bcards[100010], ecards[100010];
unordered_set<int> elsie;
set<int> bessie;
set<int> auxbessie;
int N;
int backans[100010], frontans[100010];


int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 1; i<=N; i++) {
        cin >> ecards[i];
        elsie.insert(ecards[i]);
    }
    for (int i = 1; i<=N*2; i++) {
        if (elsie.find(i) == elsie.end()) {
            bessie.insert(i);
        }
    }
    auxbessie = bessie;
    for (int i = 1; i<=N; i++) {
        if (bessie.lower_bound(ecards[i]) != bessie.end()) {
            bessie.erase(bessie.lower_bound(ecards[i]));
            frontans[i] = 1+frontans[i-1];
        } else {
            frontans[i] = frontans[i-1];
        }
    }
    for (int i = N; i>=1; i--) {
        // cout << i << " ";
        if (auxbessie.lower_bound(ecards[i]) != auxbessie.begin()) {
            // cout << *it << endl;
            auxbessie.erase(--auxbessie.lower_bound(ecards[i]));
            backans[i] = 1+backans[i+1];
        } else {
            // cout << *it << endl;
            backans[i] = backans[i+1];
        }
    }
    // for (int i = 1; i<=N; i++) {
    //   cout << frontans[i] << " ";
    // }
    // cout << endl;
    //for (int i = 1; i<=N; i++) {
    //cout << backans[i] << " ";
    //}
    // cout << endl;
    int best = max(frontans[N], backans[1]);
    for (int i = 1; i<N; i++) {
        best = max(best, frontans[i]+backans[i+1]);
    }
    cout << best << endl;
    return 0;
}



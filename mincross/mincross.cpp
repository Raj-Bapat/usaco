
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


typedef char                b8;
typedef int                 b32;
typedef long long           b64;
typedef unsigned char          ub8;
typedef unsigned int        ub32;
typedef unsigned long long     ub64;

long long s1[100010], s2[100010];
long long rev1[100010], rev2[100010];
long long oind1[100010], oind2[100010];
long long N;
long long tree[200020];

void update(long long ind, long long num) {
    while (ind<=N) {
        tree[ind]+=num;
        ind+=(ind&-ind);
    }
}

long long getsum(long long ind) {
    long long sum = 0;
    while (ind) {
        sum+=tree[ind];
        ind-=(ind&-ind);
    }
    return sum;
}


int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 1; i<=N; i++) {
        cin >> s1[i];
        rev1[s1[i]] = i;
    }
    for (int i = 1; i<=N; i++) {
        cin >> s2[i];
        rev2[s2[i]] = i;
    }
    for (int i = 1; i<=N; i++) {
        oind1[i] = rev2[s1[i]];
        oind2[i] = rev1[s2[i]];
    }
    long long invs1 = 0;
    for (int i = 1; i<=N; i++) {
        update(oind1[i], 1);
        invs1+=getsum(N)-getsum(oind1[i]);
    }
    long long mc1 = numeric_limits<long long>::max();
    for (int i = N; i>=1; i--) {
        invs1 += -N-1+2*oind1[i];
        mc1 = min(mc1, invs1);
    }
    memset(tree, 0, sizeof(tree));
    long long invs2 = 0;
    for (int i = 1; i<=N; i++) {
        update(oind2[i], 1);
        invs2+=getsum(N)-getsum(oind2[i]);
    }
    long long mc2 = numeric_limits<long long>::max();
    for (int i = N; i>=1; i--) {
        invs2 += -N-1+2*oind2[i];
        mc2 = min(mc2, invs2);
    }
    cout << min(mc1,mc2) << endl;
    return 0;
}




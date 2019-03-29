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

struct lt {
    int s, e, p;
};

const int inf = 300000001;
int t[200010];
int dp[30010];
lt lights[10010];
int N, L;

bool cmp(lt a, lt b) {return a.s != b.s ? a.s<b.s : a.e<b.e;}

int findmin(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return inf; // check negative numbers
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return min(findmin(v*2, tl, tm, l, min(r, tm)) ,findmin(v*2+1, tm+1, tr, max(l, tm+1), r));
}


void updatemin(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            updatemin(v*2, tl, tm, pos, new_val);
        else
            updatemin(v*2+1, tm+1, tr, pos, new_val);
        t[v] = min(t[v*2], t[v*2+1]);
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> L >> N;
    for (int i = 0; i<N; i++) {
        cin >> lights[i].s >> lights[i].e >> lights[i].p;
        lights[i].s++;
        lights[i].e++;
    }
    L++;
    sort(lights, lights+N, cmp);
    if (lights[N-1].e < L || lights[0].s > 1) {
        cout << "Impossible" << endl;
        return 0;
    }
    int p = N-1;
    for (int i = 1; i<L; i++) {
        updatemin(1, 1, L, i, inf);
        dp[i] = inf;
    }
    for (int i = L; i>0; i--) {
        while (p>=0 && lights[p].s == i) {
            dp[i] = min(dp[i], lights[p].p+findmin(1, 1, L, lights[p].s, lights[p].e));
            p--;
        }
        updatemin(1, 1, L, i, dp[i]);
    }
    if (p>=inf) {
        cout << "Impossible" << endl;
    } else {
        cout << dp[1] << endl;
    }
    return 0;
}



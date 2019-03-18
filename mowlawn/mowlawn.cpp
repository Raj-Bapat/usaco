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
#include <bitset>
#include <deque>
using namespace std;

long long N, K;
long long dp[100010];
long long t[400010];
long long eff[100010];
long long lazy[400010];

void push(long long v) {
    t[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

void updatemax(long long v, long long tl, long long tr, long long l, long long r, long long addend) {
    if (l > r)
        return;
    if (l == tl && tr == r) {
        t[v] += addend;
        lazy[v] += addend;
    } else {
        push(v);
        long long tm = (tl + tr) / 2;
        updatemax(v*2, tl, tm, l, min(r, tm), addend);
        updatemax(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

long long query(long long v, long long tl, long long tr, long long l, long long r) {
    if (l > r)
        return -1e+14;
    if (l <= tl && tr <= r)
        return t[v];
    push(v);
    long long tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
}


int main() {
    cin >> N >> K;
    for (long long i = 1; i<=N; i++) {
        cin >> eff[i];
    }
    for (long long i = N; i>0; i--) {
        dp[i] = eff[i]+query(1, 1, N+2, i+2, min(i+1+K, N+2));
        updatemax(1, 1, N+2, i, i, dp[i]);
        updatemax(1, 1, N+2, i+2, min(i+K, N+2), eff[i]);
    }
    long long best = 0;
    for (long long i = 1; i<=N; i++) {
        best = min(best, dp[i]);
    }
    cout << best << endl;
    return 0;
}
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

long long K, E, N;
long long dp[510][20010];
pair<long long, pair<long long, long long>> stores[510];
long long t[2][80010];

long long findmax(long long v, long long tl, long long tr, long long l, long long r) {
    if (l > r)
        return -INFINITY; // check negative numbers
    if (l == tl && r == tr) {
        return t[1][v];
    }
    long long tm = (tl + tr) / 2;
    return max(findmax(v*2, tl, tm, l, min(r, tm)) ,findmax(v*2+1, tm+1, tr, max(l, tm+1), r));
}


void updatemax(long long v, long long tl, long long tr, long long pos, long long new_val) {
    if (tl == tr) {
        t[0][v] = new_val;
    } else {
        long long tm = (tl + tr) / 2;
        if (pos <= tm)
            updatemax(v*2, tl, tm, pos, new_val);
        else
            updatemax(v*2+1, tm+1, tr, pos, new_val);
        t[0][v] = max(t[0][v*2], t[0][v*2+1]);
    }
}



int main() {
    cin >> K >> E >> N;
    for (long long i = 1; i<=N; i++) {
        cin >> stores[i].first >> stores[i].second.first >> stores[i].second.second;
    }
    stores[N+1] = {E, {0, 0}};
    N+=2;
    stores[0] = {0, {0, 0}};
    sort(stores, stores+N);
    dp[N-1][0] = 0;
    for (long long i = 1; i<=K; i++) {
        dp[N-1][i] = 5001000000;
    }
    return 0;
}
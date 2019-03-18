
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

int t1[200010], arr[100010], t2[200010];
int N, Q;

void buildmax(int v, int tl, int tr) {
    if (tl == tr) {
        t1[v] = arr[tl];
    } else {
        int tm = (tl + tr) / 2;
        buildmax(v*2, tl, tm);
        buildmax(v*2+1, tm+1, tr);
        t1[v] = max(t1[v*2], t1[v*2+1]);
    }
}

int findmax(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return -INFINITY; // check negative numbers
    if (l == tl && r == tr) {
        return t1[v];
    }
    int tm = (tl + tr) / 2;
    return max(findmax(v*2, tl, tm, l, min(r, tm)) ,findmax(v*2+1, tm+1, tr, max(l, tm+1), r));
}


void updatemax(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t1[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            updatemax(v*2, tl, tm, pos, new_val);
        else
            updatemax(v*2+1, tm+1, tr, pos, new_val);
        t1[v] = max(t1[v*2], t1[v*2+1]);
    }
}

void buildmin(int v, int tl, int tr) {
    if (tl == tr) {
        t2[v] = arr[tl];
    } else {
        int tm = (tl + tr) / 2;
        buildmin(v*2, tl, tm);
        buildmin(v*2+1, tm+1, tr);
        t2[v] = min(t2[v*2], t2[v*2+1]);
    }
}

int findmin(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 1000000000; // check negative numbers
    if (l == tl && r == tr) {
        return t2[v];
    }
    int tm = (tl + tr) / 2;
    return min(findmin(v*2, tl, tm, l, min(r, tm)) ,findmin(v*2+1, tm+1, tr, max(l, tm+1), r));
}


void updatemin(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t2[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            updatemin(v*2, tl, tm, pos, new_val);
        else
            updatemin(v*2+1, tm+1, tr, pos, new_val);
        t2[v] = min(t2[v*2], t2[v*2+1]);
    }
}

int main() {
    cin >> N >> Q;
    for (int i = 1; i<=N; i++) {
        cin >> arr[i];
    }
    buildmax(1, 1, N);
    buildmin(1, 1, N);
    for (int i = 0; i<Q; i++) {
        int a, b;
        cin >> a >> b;
        int c = findmax(1, 1, N, a, b);
        int d = findmin(1, 1, N, a, b);
        cout << c-d << endl;
    }
    return 0;
}
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

int n, t[400100], arr[400010];

void buildsum(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = arr[tl];
    } else {
        int tm = (tl + tr) / 2;
        buildsum(v*2, tl, tm);
        buildsum(v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

int sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
}


void updatesum(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            updatesum(v*2, tl, tm, pos, new_val);
        else
            updatesum(v*2+1, tm+1, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1];
    }
}

void buildmax(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = arr[tl];
    } else {
        int tm = (tl + tr) / 2;
        buildmax(v*2, tl, tm);
        buildmax(v*2+1, tm+1, tr);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

int findmax(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return -INFINITY; // check negative numbers
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return max(findmax(v*2, tl, tm, l, min(r, tm)) ,findmax(v*2+1, tm+1, tr, max(l, tm+1), r));
}


void updatemax(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            updatemax(v*2, tl, tm, pos, new_val);
        else
            updatemax(v*2+1, tm+1, tr, pos, new_val);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

int main(int argc, const char * argv[]) {
    cin >> n;
    for (int i = 1; i<=n; i++) {
        cin >> arr[i];
    }
    buildmax(1, 1, n);
    int M;
    cin >> M;
    for (int i = 0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        cout << findmax(1, 1, n, a, b) << endl;
    }
    return 0;
}
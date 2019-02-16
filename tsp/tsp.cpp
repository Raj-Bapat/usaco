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

const int inf = 100000123;
vector<pair<int, int>> adjlist[19];
int dp[1<<19][19];
int N, M;

int f(int mask, int node) {
    if (mask == (1<<N) - 1) {
        return 0;
    }
    if (dp[mask][node] != inf) {
        return dp[mask][node];
    }
    for (int i = 0; i<adjlist[node].size(); i++) {
        int v = adjlist[node][i].first;
        if (!(mask & (1 << v))) {
            int thing = adjlist[node][i].second+f((mask | (1 << v)), v);
            if (thing<dp[mask][node])
            dp[mask][node] = thing;
        }
    }
    return dp[mask][node];
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    for (int i = 0; i<(1<<N); i++) {
        for (int j = 0; j<N; j++) {
            dp[i][j] = inf;
        }
    }
    for (int i = 0; i<M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adjlist[a].push_back({b,c});
        adjlist[b].push_back({a,c});
    }
    int best = inf;
    for (int i = 0; i<N; i++) {
        best = min(best, f((0 | (1 << i)), i));
    }
    cout << best << endl;
    return 0;
}



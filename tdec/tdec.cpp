
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




#define int long long

int N,P[100010],C[100010],T[100010];
vector<int> adjlist[100010];

pair<int, pair<int, int>> traverse(int u, int last) {
    if (adjlist[u].size() == 1 && u != 1) {
        // cout << "here" << endl;
        return make_pair(C[u]*T[u], make_pair(T[u], C[u]));
    }
    int minsum = 0, minu = T[u], nodesfound = 0;
    for (int i = 0; i<adjlist[u].size(); i++) {
        int v = adjlist[u][i];
        if (v != last) {
            pair<int, pair<int, int>> aux = traverse(v, u);
            minsum+=aux.first;
            minu = min(minu, aux.second.first);
            nodesfound+=aux.second.second;
        }
    }
    // cout << "here2" << endl;
    // cout << u << " " << last << " " << minsum+(C[u]-nodesfound)*minu << " " << minu << " " << C[u] << " " << nodesfound << endl;
    if (C[u]>nodesfound) {
        return make_pair(minsum+(C[u]-nodesfound)*minu, make_pair(minu, C[u]));
    } else {
        return make_pair(minsum, make_pair(minu, nodesfound));
    }
}

main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 1; i<=N; i++) {
        cin >> P[i] >> C[i] >> T[i];
        if (i != 1) {
            adjlist[P[i]].push_back(i);
            adjlist[i].push_back(P[i]);
        }
    }
    // for (int i = 1; i<=N; i++) {
    //   for (int j = 0; j<adjlist[i].size(); j++) {
    //     cout << adjlist[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    // cout << endl;
    pair<int, pair<int, int>> ans = traverse(1, 1);
    cout << ans.first << endl;
    return 0;
}



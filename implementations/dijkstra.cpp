//
//  main.cpp
//  dijkstra2
//
//  Created by r on 12/23/18.
//  Copyright © 2018 r. All rights reserved.
// new dijkstra

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
#define inf 1000000


typedef char                b8;
typedef int                 b32;
typedef long long           b64;
typedef unsigned char          ub8;
typedef unsigned int        ub32;
typedef unsigned long long     ub64;

vector<pair<long long, long long>> adj[100010];
long long sp[100010];
long long N,M,T,S,E;

void dijkstra(long long s) {
    sp[s] = 0;
    using pii = pair<long long, long long>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        long long v = q.top().second;
        long long d_v = q.top().first;
        q.pop();
        if (d_v != sp[v]) {
            continue;
        }
        for (auto edge : adj[v]) {
            long long to = edge.first;
            long long len = edge.second;
            if (sp[v] + len < sp[to]) {
                sp[to] = sp[v] + len;
                q.push({sp[to], to});
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int iii = 0; iii<T; iii++) {
        cin >> N >> M >> S >> E;
        for (int i = 0; i<100010; i++) {
            sp[i] = 1000000;
        }
        for (int i = 0; i<=N; i++) {
            adj[i].clear();
        }
        for (int i = 0; i<M; i++) {
            long long f, s, t;
            cin >> f >> s >> t;
            adj[f].push_back({s,t});
            adj[s].push_back({f,t});
        }
        dijkstra(S);
        if (sp[E] == 1000000) {
            cout << "NONE" << endl;
        } else {
            cout << sp[E] << endl;
        }
    }
    return 0;
}




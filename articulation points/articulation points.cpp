//
//  main.cpp
//  articulation points
//
//  Created by r on 1/20/19.
//  Copyright © 2019 r. All rights reserved.
//

#include <iostream>
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

int N,M; // number of nodes
vector<int> adj[100010]; // adjacency list of graph

vector<bool> visited;
vector<int> tin, fup;
int timer;
bool apoint[100010];

void IS_CUTPOINT(int a) {
    apoint[a] = true;
}

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = fup[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            fup[v] = min(fup[v], tin[to]);
        } else {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] >= tin[v] && p!=-1)
                IS_CUTPOINT(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        IS_CUTPOINT(v);
}

void find_cutpoints() {
    timer = 0;
    visited.assign(N, false);
    tin.assign(N, -1);
    fup.assign(N, -1);
    for (int i = 0; i < N; ++i) {
        if (!visited[i])
            dfs (i);
    }
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    for (int i = 0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    find_cutpoints();
    int cnt = 0;
    for (int i = 0; i<N; i++) {
        if (apoint[i]) {
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}


//
//  main.cpp
//  atlarge
//
//  Created by r on 3/17/18.
//  Copyright © 2018 r. All rights reserved.
//

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

vector<int> adjlist[100010];
int N,K;
vector<int> leafs;
int r2n[100010];
int l2n[100010];
int farmers = 0;
bool visited[100010];

void dfs1(int u, int dist) {
    r2n[u] = dist;
    for (int i = 0; i<adjlist[u].size(); i++) {
        int v = adjlist[u][i];
        if (r2n[v] == -1) {
            r2n[v] = dist+1;
            dfs1(v, dist+1);
        }
    }
}

void dfs2(int u) {
    visited[u] = true;
    for (int i = 0; i<adjlist[u].size(); i++) {
        int v = adjlist[u][i];
        if (visited[v]) {
            continue;
        }
        if (l2n[v]<=r2n[v]) {
            farmers++;
            continue;
        }
        visited[v] = true;
        dfs2(v);
    }
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin;
    ofstream fout;
    fin.open("atlarge.in");
    fout.open("atlarge.out");
    fin >> N >> K;
    for (int i = 0; i<N-1; i++) {
        int f,s;
        fin >> f >> s;
        adjlist[f].push_back(s);
        adjlist[s].push_back(f);
    }
    for (int i = 1; i<=N; i++) {
        if (adjlist[i].size() == 1) {
            leafs.push_back(i);
        }
    }
    memset(r2n, -1, sizeof(r2n));
    memset(l2n, -1, sizeof(l2n));
    dfs1(K, 0);
    queue<int> q;
    for (int i = 0; i<leafs.size(); i++) {
        q.push(leafs[i]);
        q.push(0);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int dist = q.front();
        q.pop();
        l2n[u] = dist;
        for (int i = 0; i<adjlist[u].size(); i++) {
            int v = adjlist[u][i];
            if (l2n[v] == -1) {
                l2n[v] = dist+1;
                q.push(v);
                q.push(dist+1);
            }
        }
    }
    dfs2(K);
    fout << farmers << endl;
    return 0;
}




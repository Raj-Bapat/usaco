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


int N, L, Q;
vector<int> adj[100010];
int vals[100010];
int frt[100010];
int par[100010];

void dfs2(int u, int parent, int curr) {
    frt[u] = curr;
    if (adj[u].size() == 1 && adj[u][0] == parent) {
        return;
    }
    for (int v: adj[u]) {
        if (v != parent) {
            par[v] = u;
            dfs2(v, u, curr^vals[v]);
        }
    }
}

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= L; i++)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = timer++;
}

bool is_ancetor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancetor(u, v))
        return u;
    if (is_ancetor(v, u))
        return v;
    for (int i = L; i >= 0; i--) {
        if (!is_ancetor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(N);
    tout.resize(N);
    timer = 0;
    L = ceil(log2(N));
    up.assign(N, vector<int>(L + 1));
    dfs(root, root);
}


int main() {
    ifstream fin;
    ofstream fout;
    fin.open("cowland.in");
    fout.open("cowland.out");
    fin >> N >> Q;
    for (int i = 0; i<N; i++) fin >> vals[i];
    for (int i = 0; i<N-1; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    par[0] = 0;
    dfs2(0, 0, vals[0]);
    preprocess(0);
    for (int i = 0; i<Q; i++) {
        int c, a, b;
        fin >> c >> a >> b;
        a--;
        if (c == 1) {
            vals[a] = b;
            if (a == 0) {
               dfs2(a, a, b);
            } else {
                dfs2(a, par[a], (frt[par[a]]^b));
            }
            continue;
        }
        b--;
        int val = lca(a, b);
        fout << ((frt[a]^frt[b])^vals[val]) << endl;
    }
    return 0;
}
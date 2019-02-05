

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

int N, L, K;
vector<int> adj[100010];
pair<int, int> postorder[100010];
int k = 0;


int timer;
vector<int> tin, tout;
vector<vector<int>> up;
int lazy[100010];
int parent[100010];

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

void compost(int u, int last) {
    for (int i = 0; i<adj[u].size(); i++) {
        int v = adj[u][i];
        if (last != v) {
            compost(v, u);
        }
    }
    postorder[u].first = k;
    postorder[u].second = u;
    k++;
}

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    for (int i = 0; i<N-1; i++) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    preprocess(0);
    compost(0, 0);
    for (int lowest = 1; lowest<N; lowest++) {
        int maximum = -1;
        int maxpost = -1;
        for (int j = 0; j<adj[lowest].size(); j++) {
            int v = adj[lowest][j];
            if (postorder[v].first>maxpost) {
                maxpost = postorder[v].first;
                maximum = v;
            }
        }
        parent[lowest] = maximum;
    }
    for (int i = 0; i<K; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int lowest = lca(a, b);
        lazy[a]++;
        lazy[b]++;
        lazy[lowest]--;
        if (lowest != 0) {
            lazy[parent[lowest]]--;
        }
    }
    sort(postorder, postorder+N);
    int maximum = -1;
    for (int i = 0; i<N; i++) {
        maximum = max(maximum, lazy[postorder[i].second]);
        lazy[parent[postorder[i].second]]+=lazy[postorder[i].second];
    }
    cout << maximum << endl;
    return 0;
}

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
const int maxn = 5010;

int n, m, tot, cnt, cccnt;
int dfn[maxn], low[maxn], head[maxn], ccno[maxn], ccnum[maxn], degree[maxn];
bool vis[maxn];

struct Edge {
    int to, next;
}edge[20010];
stack <int> S;

void addedge(int u, int v) {
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}



void tarjan(int u, int father) {
    low[u] = dfn[u] = tot++;
    S.push(u);
    vis[u] = true;
    bool flag = true;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v == father && flag) {
            flag = false;
            continue;
        }
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        cccnt++;
        while (1) {
            int v = S.top();
            S.pop();
            vis[v] = false;
            ccno[v] = cccnt;
            ccnum[cccnt]++;
            if (v == u)
                break;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        dfn[i] = low[i] = ccno[i] = ccnum[i] = degree[i] = 0;
        head[i] = -1;
        vis[i] = false;
    }
    memset(edge, 0, sizeof(edge));
    tot = cccnt = 0;
    cnt = 1;
    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    tarjan(1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j != -1; j = edge[j].next) {
            int v = edge[j].to;
            if (ccno[i] != ccno[v])
                degree[ccno[i]]++;
        }
    }
    int ans = 0;
    for (int i = 1; i <= cccnt; i++) {
        if (degree[i] == 1)
            ans++;
    }
    cout << (ans+1) / 2 << endl;
    return 0;
}
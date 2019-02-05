
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

vector<int> adj[5010];
int low[5010];
int disc[5010];
int parent[5010];
int visited[5010];
int t = 0;
stack<pair<int, int>> s;
unordered_set<int> bcomps[10010];
int bsz = 0;
int N,M;
unordered_set<int> color[5010];
unordered_set<int> nadj[10010];
int lc = 0;

void dfs(int vertex) {
    disc[vertex] = t+1;
    low[vertex] = t+1;
    t++;
    visited[vertex] = true;
    int child = 0;
    for (int i = 0; i<adj[vertex].size(); i++) {
        int v = adj[vertex][i];
        if (!visited[v]) {
            child = child+1;
            s.push(make_pair(vertex, v));
            parent[v] = vertex;
            dfs(v);
            low[vertex] = min(low[vertex], low[v]);
            if ((!parent[vertex] && child>1) || (parent[vertex] && low[v]>=disc[vertex])) {
                while (!(s.top().first == vertex && s.top().second == v)) {
                    bcomps[bsz].insert(s.top().first);
                    bcomps[bsz].insert(s.top().second);
                    color[s.top().first].insert(bsz);
                    color[s.top().second].insert(bsz);
                    s.pop();
                }
                color[s.top().first].insert(bsz);
                color[s.top().second].insert(bsz);
                bcomps[bsz].insert(s.top().first);
                bcomps[bsz].insert(s.top().second);
                s.pop();
                bsz++;
            }
        } else if (parent[vertex] != v && disc[v]<low[vertex]) {
            low[vertex] = disc[v];
            s.push(make_pair(vertex, v));
        }
    }
}

void findbcomps() {
    for (int i = 1; i<=N; i++) {
        if (!visited[i]) {
            dfs(i);
            bool added = false;
            while (!s.empty()) {
                color[s.top().first].insert(bsz);
                color[s.top().second].insert(bsz);
                bcomps[bsz].insert(s.top().first);
                bcomps[bsz].insert(s.top().second);
                s.pop();
                added = true;
            }
            if (added) {
                bsz++;
            }
        }
    }
}

void dfs2(int u, int last) {
    if (nadj[u].size() == 1 && (*nadj[u].begin()) == last) {
        lc++;
        return;
    }
    for (auto v:nadj[u]) {
        if (v != last) {
            dfs2(v, u);
        }
    }
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    for (int i = 0; i<M; i++) {
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    findbcomps();
    for (int i = 1; i<=N; i++) {
        if (color[i].size()>1) {
            for (auto k:color[i]) {
                if (k != (*color[i].begin())) {
                    nadj[(*color[i].begin())].insert(k);
                    nadj[k].insert((*color[i].begin()));
                }
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    dfs2(0, -1);
    if (nadj[0].size() == 1) {
        lc++;
    }
    cout << ceil(lc/2) << endl;
    return 0;
}





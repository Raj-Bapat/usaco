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
long long T,R,P,S;

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

int main() {
    for (int i = 0; i<100010; i++) {
        sp[i] = numeric_limits<long long>::max()-10000000;
    }
    cin >> T >> R >> P >> S;
    for (int i = 0; i<R; i++) {
        long long f,s,t;
        cin >> f >> s >> t;
        adj[f].push_back(make_pair(s,t));
        adj[s].push_back(make_pair(f,t));
    }
    for (int i = 0; i<P; i++) {
        long long f,s,t;
        cin >> f >> s >> t;
        adj[f].push_back(make_pair(s,t));
    }
    dijkstra(S);
    for (int i = 1; i<=T; i++) {
        if (sp[i] == numeric_limits<long long>::max()-10000000) {
            cout << "NO PATH" << endl;
        } else {
            cout << sp[i] << endl;
        }
    }
    return 0;
}
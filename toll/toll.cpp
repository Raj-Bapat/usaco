
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

vector<pair<long long, long long>> adj[300];
long long sp[300][300];
long long sp1[300][300];
long long N,M,K;
pair<long long, long long> ntolls[300];
int rev[300];

void dijkstra(long long s) {
    // cout << endl;
    // cout << s << endl;
    // cout << rev[s] << endl;
    sp[s][s] = 0;
    using pii = pair<long long, long long>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        long long v = q.top().second;
        long long d_v = q.top().first;
        q.pop();
        if (d_v != sp[s][v]) {
            continue;
        }
        // cout << v << " " << d_v << endl;
        for (auto edge : adj[v]) {
            long long to = edge.first;
            long long len = edge.second;
            if (sp[s][v] + len < sp[s][to] && rev[to]<=rev[s]) {
                sp[s][to] = sp[s][v] + len;
                q.push({sp[s][to], to});
            }
        }
    }
    // cout << endl;
}


int main(int argc, const char * argv[]) {
    cin >> N >> M >> K;
    for (int i = 0; i<300; i++) {
        for (int j = 0; j<300; j++) {
            sp[i][j] = 1000000;
            sp1[i][j] = 1000000;
        }
    }
    //  cout << "here1" << endl;
    for (int i = 0; i<=N; i++) {
        adj[i].clear();
    }
    for (int i = 1; i<=N; i++) {
        int a;
        cin >> a;
        ntolls[i].first = a;
        ntolls[i].second = i;
    }
    for (int i = 1; i<=N; i++) {
        rev[ntolls[i].second] = ntolls[i].first;
    }
    sort(ntolls+1, ntolls+N+1);
    for (int i = 0; i<M; i++) {
        long long f, s, t;
        cin >> f >> s >> t;
        adj[f].push_back(make_pair(s,t));
        adj[s].push_back(make_pair(f,t));
    }
    // cout << "here2" << endl;
    for (int i = 1; i<=N; i++) {
        dijkstra(i);
    }
    // cout << "here3" << endl;
    for (int i = 1; i<=N; i++) {
        for (int j = i; j<=N; j++) {
            for (int k = N; k>=1; k--) {
                sp1[ntolls[i].second][k] = min(sp1[ntolls[i].second][k], sp[ntolls[j].second][ntolls[i].second]+sp[ntolls[j].second][k]+ntolls[j].first);
                // cout << ntolls[i].second << " " << ntolls[j].second << " " << k << " " << ntolls[j].first << "   " << sp[ntolls[i].second][ntolls[j].second] << " " << sp[ntolls[j].second][k] << " " << sp1[ntolls[i].second][k] << endl;
                sp1[k][ntolls[i].second] = min(sp1[k][ntolls[i].second], sp[ntolls[j].second][ntolls[i].second]+sp[ntolls[j].second][k]+ntolls[j].first);
            }
        }
    }
    // cout << "here4" << endl;
    for (int i = 0; i<K; i++) {
        int a, b;
        cin >> a >> b;
        cout << min(sp1[a][b], sp1[b][a]) << endl;
    }
    return 0;
}




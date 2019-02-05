#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <assert.h>
#include <limits>
using namespace std;

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif
#define inf 0x7fffffff

struct recnode {
    int n, w;
};

int sp[5][10010];
vector<recnode> adjlist[10010];
int mtowns[5];
int combs[121][5];
int visited[5];
int c = 0;


struct edge {
    int u,v,ind;
};

int N,M,K;
int S;
int arr[5];

void recurse(int i) {
    if (i == K) {
        for (int j = 0; j<5; j++) {
            combs[c][j] = arr[j];
        }
        c++;
        return;
    }
    for (int j = 0; j<K; j++) {
        if (!visited[j]) {
            visited[j] = true;
            arr[i] = j;
            recurse(i+1);
            visited[j] = false;
        }
    }
}

bool operator< (edge a, edge b) {return sp[S][a.u]+adjlist[a.u][a.ind].w>sp[S][b.u]+adjlist[b.u][b.ind].w;}

void dijktra(int start) {
    priority_queue<edge> p;
    sp[S][start] = 0;
    for (int i = 0; i<adjlist[start].size(); i++) {
        edge e;
        e.u = start;
        e.v = adjlist[start][i].n;
        e.ind = i;
        p.push(e);
    }
    while (!p.empty()) {
        edge e;
        e = p.top();
        p.pop();
        if (sp[S][e.v] != numeric_limits<int>::max()) {
            continue;
        }
        sp[S][e.v] = sp[S][e.u]+adjlist[e.u][e.ind].w;
        for (int i = 0; i<adjlist[e.v].size(); i++) {
            edge ne;
            ne.u = e.v;
            ne.v = adjlist[e.v][i].n;
            ne.ind = i;
            p.push(ne);
        }
    }
}



int main(int argc, const char * argv[]) {
    cin >> N >> M >> K;
    for (int i = 0; i<K; i++) {
        cin >> mtowns[i];
    }
    recurse(0);
    // for (int i = 0; i<c; i++) {
    //     for (int j = 0; j<K; j++) {
    //         cout << combs[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for (int i = 0; i<M; i++) {
        int f,s,t;
        cin >> f >> s >> t;
        recnode r1;
        recnode r2;
        r1.n = s;
        r2.n = f;
        r1.w = t;
        r2.w = t;
        adjlist[f].push_back(r1);
        adjlist[s].push_back(r2);
    }
    for (int j = 0; j<K; j++) {
        for (int i = 1; i<=N; i++) {
            sp[j][i] = numeric_limits<int>::max();
        }
    }
    for (int i = 0; i<K; i++) {
        S = i;
        dijktra(mtowns[i]);
    }
    int mindist = numeric_limits<int>::max();
    for (int i = 1; i<=N; i++) {
        int alert = false;
        for (int j = 0; j<K; j++) {
            if (mtowns[j] == i) {
                alert = true;
                break;
            }
        }
        if (alert) {
            continue;
        }
        for (int j = 0; j<c; j++) {
            int cdist = sp[combs[j][0]][i];
            for (int k = 1; k<K; k++) {
                cdist+=sp[combs[j][k]][mtowns[combs[j][k-1]]];
            }
            cdist+=sp[combs[j][K-1]][i];
            mindist = min(mindist,cdist);
        }
    }
    cout << mindist << endl;
    return 0;
}
//
//  main.cpp
//  buffet
//
//  Created by r on 12/19/17.
//  Copyright © 2017 r. All rights reserved.
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

vector<int> adjlist[1010];
int quality[1010];
int dist[1010];
int N,E;
int patches[1010];
int dp[1010];

bool comp(int a, int b) {return quality[a]<quality[b];}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("buffet.in");
    fout.open("buffet.out");
    fin >> N >> E;
    for (int i = 1; i<=N; i++) {
        int ns;
        fin >> quality[i] >> ns;
        patches[i] = i;
        for (int j = 0; j<ns; j++) {
            int adj;
            fin >> adj;
            adjlist[i].push_back(adj);
        }
    }
    sort(patches+1, patches+N+1, comp);
    int maxe = 0;
    for (int i = N; i>0; i--) {
        int u = patches[i];
        queue<int> q;
        memset(dist, -1, sizeof(dist));
        q.push(u);
        dist[u] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int j = 0; j<adjlist[v].size(); j++) {
                int nv = adjlist[v][j];
                if (dist[nv] == -1) {
                    dist[nv] = dist[v]+1;
                    q.push(nv);
                }
            }
        }
        int best = quality[u];
        for (int j = 1; j<=N; j++) {
            if (dist[j] != -1) {
                best = max(best, quality[u]+dp[j]-E*dist[j]);
            }
        }
        dp[u] = best;
        maxe = max(maxe, best);
    }
    fout << maxe << endl;
    return 0;
}


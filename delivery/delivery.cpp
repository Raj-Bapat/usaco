//
//  main.cpp
//  delivery
//
//  Created by a2g2 on 2/3/19.
//  Copyright © 2019 a2g2. All rights reserved.
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
#include <bitset>
using namespace std;

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif


long long N, K;
pair<long long, long long> cowpts[510];
struct pair_hash {
    inline std::size_t operator()(const std::pair<long long,long long> & v) const {
        return v.first*31+v.second;
    }
};

long long sp[110][510];

std::unordered_set< std::pair<long long, long long>,  pair_hash> pts;

bool checkpt(pair<long long, long long> a) {return pts.find(a) == pts.end();}
long long adj[510][510];

long long addone(long long a) {
    if (a == N-1) {
        return 0;
    } else {
        return a+1;
    }
}

void dijkstra(long long s) {
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
        for (long long i = 0; i<K; i++) {
            if (i == v || adj[v][i] == numeric_limits<long long>::max() || (i<N && i != addone(s))) {
                continue;
            }
            pair<long long, long long> edge = {i, adj[v][i]};
            long long to = edge.first;
            long long len = edge.second;
            if (sp[s][v] + len < sp[s][to]) {
                sp[s][to] = sp[s][v] + len;
                q.push({sp[s][to], to});
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    for (long long i = 0; i<510; i++) {
    	for (long long j = 0; j<510; j++) {
    		adj[i][j] = numeric_limits<long long>::max();
    		adj[i][i] = 0;
    		if (i<110) {
    		    sp[i][j] = numeric_limits<long long>::max();
    		}
    	}
    }
    cin >> N;
    for (long long i = 0; i<N; i++) {
        cin >> cowpts[i].first >> cowpts[i].second;
        pts.insert(cowpts[i]);
    }
    K = N;
    for (long long i = 0; i<N; i++) {
        if (checkpt({cowpts[i].first+1, cowpts[i].second})) {
            cowpts[K] = {cowpts[i].first+1, cowpts[i].second};
            K++;
            pts.insert({cowpts[i].first+1, cowpts[i].second});
        }
        if (checkpt({cowpts[i].first-1, cowpts[i].second})) {
            cowpts[K] = {cowpts[i].first-1, cowpts[i].second};
            K++;
            pts.insert({cowpts[i].first-1, cowpts[i].second});
        }
        if (checkpt({cowpts[i].first, cowpts[i].second+1})) {
            cowpts[K] = {cowpts[i].first, cowpts[i].second+1};
            K++;
            pts.insert({cowpts[i].first, cowpts[i].second+1});
        }
        if (checkpt({cowpts[i].first, cowpts[i].second-1})) {
            cowpts[K] = {cowpts[i].first, cowpts[i].second-1};
            K++;
            pts.insert({cowpts[i].first, cowpts[i].second-1});
        }
    }
    for (long long i = 0; i<K; i++) {
        for (long long j = i+1; j<K; j++) {
            long long x1 = cowpts[i].first, y1 = cowpts[i].second, x2 = cowpts[j].first, y2 = cowpts[j].second;
            bool f1 = false, f2 = false;
            for (long long k = 0; k<N; k++) {
                long long x3 = cowpts[k].first, y3 = cowpts[k].second;
                if ((x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3)) {
                    continue;
                }
                if ((max(x1, x2)>=x3 && y3 == y2 && min(x1, x2)<=x3) || (x1 == x3 && max(y1, y2)>=y3 && min(y1, y2)<=y3)) { // TO EDIT
                    f1 = true;

                }
                if ((max(x1, x2)>=x3 && y3 == y1 && min(x1, x2)<=x3) || (x3 == x2 && max(y1, y2)>=y3 && min(y1, y2)<=y3)) { // TO EDIT
                    f2 = true;
                }
            }
            long long totint = f1+f2;
            if (totint<2 && !((x1 == x2 || y1 == y2) && totint>=1)) {
            	adj[i][j] = abs(x1-x2)+abs(y1-y2);
            	adj[j][i] = adj[i][j];
            }
        }
    }
    for (long long i = 0; i<N; i++) {
        dijkstra(i);
    }
    long long tot = 0;
    for (long long i = 0; i<N; i++) {
//        cout << sp[i][addone(i)] << endl;
        tot+=sp[i][addone(i)];
    }
    if (tot<0) {    // overflow and checks for when it is not possible
        cout << -1 << endl;
        return 0;
    }
    cout << tot << endl;
    return 0;

}



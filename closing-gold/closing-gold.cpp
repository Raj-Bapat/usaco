//
//  main.cpp
//  closing-gold
//
//  Created by r on 11/30/17.
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

int nodes = 0;
int parent[200010];
int nrank[200010];
vector<int> adjlist[200010];
int order[200010];
int N,M;
int num[200010];
bool open[200010];
string ans[200010];

void create_set() {
    nodes++;
    parent[nodes] = nodes;
    nrank[nodes] = 0;
    num[nodes] = 1;
}

int find_set(int x) {
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void merge_sets(int x, int y) {
    int PX = find_set(x), PY = find_set(y);
    if (nrank[PX] > nrank[PY]) {
        parent[PY] = PX;
        num[PX] += num[PY];
        num[PY] = 0;
    } else {
        parent[PX] = PY;
        num[PY]+=num[PX];
        num[PX] = 0;
    }
    if (nrank[PX] == nrank[PY]) {
        nrank[PY]++;
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("closing.in");
    fout.open("closing.out");
    ios_base :: sync_with_stdio(false);
    fin >> N >> M;
    for (int i = 0; i<M; i++) {
        int first, second;
        fin >> first >> second;
        adjlist[first].push_back(second);
        adjlist[second].push_back(first);
    }
    for (int i = N-1; i>=0; i--) {
        fin >> order[i];
    }
    for (int i = 1; i<=N; i++) {
        create_set();
    }
    for (int i = 0; i<N; i++) {
        open[order[i]] = true;
        for (int j = 0; j<adjlist[order[i]].size(); j++) {
            if (open[adjlist[order[i]][j]] && find_set(adjlist[order[i]][j]) != find_set(order[i])) {
                merge_sets(adjlist[order[i]][j], order[i]);
            }
        }
        if (num[find_set(order[i])] == i+1) {
            ans[i] = "YES";
        } else {
            ans[i] = "NO";
        }
    }
    for (int i = N-1; i>=0; i--) {
        fout << ans[i] << endl;
    }
    return 0;
}


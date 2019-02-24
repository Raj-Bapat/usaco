//
//  main.cpp
//  dsu
//
//  Created by r on 11/25/17.
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
int parent[100000];
int nrank[100000];

int N,M;

void create_set() {
    nodes++;
    parent[nodes] = nodes;
    nrank[nodes] = 0;
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
    } else {
        parent[PX] = PY;
    }
    if (nrank[PX] == nrank[PY]) {
        nrank[PY]++;
    }
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i<=N; i++) {
        create_set();
    }
    cin >> M;
    for (int i = 0; i<M; i++) {
        int a,b;
        cin >> a >> b;
        if (parent[a]!=parent[b]) {
            merge_sets(a, b);
        }
    }
    int root = find_set(1);
    for (int i = 2; i<=N; i++) {
        if (find_set(i) != root) {
            cout << "forest" << endl;
            return 0;
        }
    }
    cout << "connected" << endl;
    return 0;
}


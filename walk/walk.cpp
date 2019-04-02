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

unsigned int nodes = 0;
unsigned int parent[7510];
unsigned int nrank[7510];
unsigned int ne = 0;

unsigned int N,K;

void create_set() {
    nodes++;
    parent[nodes] = nodes;
    nrank[nodes] = 0;
}

unsigned int find_set(unsigned int x) {
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void merge_sets(unsigned int x, unsigned int y) {
    unsigned int PX = find_set(x), PY = find_set(y);
    if (nrank[PX] > nrank[PY]) {
        parent[PY] = PX;
    } else {
        parent[PX] = PY;
    }
    if (nrank[PX] == nrank[PY]) {
        nrank[PY]++;
    }
}

pair<unsigned int, pair<unsigned int, unsigned int>> edges[28140002];

bool cmp(pair<unsigned int, pair<unsigned int, unsigned int>> a, pair<unsigned int, pair<unsigned int, unsigned int>> b) {return a.first>b.first;}

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("walk.in");
    fout.open("walk.out");
    fin >> N >> K;
    for (long long i = 1; i<=N; i++) {
        for (long long j = i+1; j<=N; j++) {
            long long asdf = (2019201913*i + 2019201949*j)%2019201997;
            edges[ne] = {(int)asdf, {i, j}};
            ne++;
        }
    }
    sort(edges, edges+ne);
    for (unsigned int i = 1; i<=N; i++) {
        create_set();
    }
    for (unsigned int i = 0; i<ne; i++) {
        unsigned int curr = edges[i].first;
        unsigned int curri = i;
        if (find_set(edges[curri].second.first) != find_set(edges[curri].second.second)) {
            nodes--;
            merge_sets(edges[curri].second.first, edges[curri].second.second);
        }
        while (curri+1<ne && edges[curri+1].first == curr) {
            curri++;
            if (find_set(edges[curri].second.first) != find_set(edges[curri].second.second)) {
                nodes--;
                merge_sets(edges[curri].second.first, edges[curri].second.second);
            }
        }
        if (nodes<K) {
            fout << edges[curri].first << endl;
            return 0;
        }
        i = curri;
    }
    fout << 0 << endl;
    return 0;
}
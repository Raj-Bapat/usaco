//
// Created by r on 2019-02-06.
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
#include <cstdio>
using namespace std;

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif
#define inf 0x7fffffff

int N,M;

struct spair {
    int first, second;
};

bool operator<(spair a, spair b) {return a.first<b.first;}

bool visited[10010];
vector<int> adjlist[10010];
int ttm[10010];
int incoming[10010];

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("msched.in");
    fout.open("msched.out");
    ios_base :: sync_with_stdio(false);
    fin >> N >> M;
    for (int i = 1; i<=N; i++) {
        fin >> ttm[i];
    }
    for (int i = 0; i<M; i++) {
        int f,s;
        fin >> f >> s;
        adjlist[f].push_back(s);
        incoming[s]++;
    }
    multiset<spair> s;
    for (int i = 1; i<=N; i++) {
        if (!incoming[i]) {
            spair a;
            a.first = ttm[i];
            a.second = i;
            s.insert(a);
        }
    }
    int currtime = 0;
    while (!s.empty()) {
        spair best = *s.begin();
        s.erase(s.begin());
        currtime = best.first;
        for (int i = 0; i<adjlist[best.second].size(); i++) {
            incoming[adjlist[best.second][i]]--;
            if (incoming[adjlist[best.second][i]]==0) {
                spair n;
                n.first = best.first+ttm[adjlist[best.second][i]];
                n.second = adjlist[best.second][i];
                s.insert(n);
            }
        }
    }
    fout << currtime << endl;
    return 0;
}




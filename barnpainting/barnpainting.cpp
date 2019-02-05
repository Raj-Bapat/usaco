//
//  main.cpp
//  barnpainting
//
//  Created by r on 2/17/18.
//  Copyright © 2018 r. All rights reserved.
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
using namespace std;

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif
#define inf 0x7fffffff
#define MOD 1000000007


typedef char                b8;
typedef int                 b32;
typedef long long           b64;
typedef unsigned char          ub8;
typedef unsigned int        ub32;
typedef unsigned long long     ub64;

long long N,K;
long long ac[100010];
long long dp[100010][4];
vector<long long> choices[100010];
vector<long long> adjlist[100010];

long long f(long long node, long long c, long long last) {
    if (dp[node][c] != -1) {
        return dp[node][c];
    }
    dp[node][c] = 1;
    for (int i = 0; i<adjlist[node].size(); i++) {
        long long v = adjlist[node][i];
        if (v != last) {
            long long counter = 0;
            for (int j = 0; j<choices[v].size(); j++) {
                if (choices[v][j] != c) {
                    counter+=f(v, choices[v][j], node);
                    counter%=MOD;
                }
            }
            dp[node][c]*=counter;
            dp[node][c]%=MOD;
        }
    }
    return dp[node][c];
}


int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin;
    ofstream fout;
    fin.open("barnpainting.in");
    fout.open("barnpainting.out");
    fin >> N >> K;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i<N-1; i++) {
        long long f,s;
        fin >> f >> s;
        adjlist[f].push_back(s);
        adjlist[s].push_back(f);
    }
    for (int i = 0; i<K; i++) {
        long long f,s;
        fin >> f >> s;
        ac[f] = s;
    }
    for (int i = 1; i<=N; i++) {
        long long a = true, b = true, c = true;
        if (ac[i]) {
            choices[i].push_back(ac[i]);
            continue;
        }
        for (int j = 0; j<adjlist[i].size(); j++) {
            if (ac[adjlist[i][j]] == 1) {
                a = false;
            }
            if (ac[adjlist[i][j]] == 2) {
                b = false;
            }
            if (ac[adjlist[i][j]] == 3) {
                c = false;
            }
        }
        if (a) {
            choices[i].push_back(1);
        }
        if (b) {
            choices[i].push_back(2);
        }
        if (c) {
            choices[i].push_back(3);
        }
    }
    for (int i = 1; i<=N; i++) {
        if (!choices[i].size()) {
            fout << 0 << endl;
            return 0;
        }
    }
    long long ans = 0;
    for (int i = 0; i<choices[1].size(); i++) {
        ans+=f(1, choices[1][i], numeric_limits<long long>::min());
        ans%=MOD;
        memset(dp, -1, sizeof(dp));
    }
    fout << ans << endl;
    return 0;
}




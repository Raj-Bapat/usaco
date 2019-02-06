/*
 ID: a2g2gon1
 PROG: charrec
 LANG: C++11
 */
//
//  main.cpp
//  charrec
//
//  Created by r on 9/29/18.
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


typedef char                b8;
typedef int                 b32;
typedef long long           b64;
typedef unsigned char          ub8;
typedef unsigned int        ub32;
typedef unsigned long long     ub64;


string flines[541];
string ilines[2210];
long long lcorrs[541][2210];
long long N,M;
long long dp[1210];
pair<long long, char> lnext[1210];
char pans[27] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

long long f(long long left) {
    if (left>N) {
        return 1000000;
    }
    if (left == N) {
        return 0;
    }
    if (dp[left] != 1000000) {
        return dp[left];
    }
    long long b1 = numeric_limits<long long>::max(), b2 = numeric_limits<long long>::max(), b3 = numeric_limits<long long>::max(), ib1 = -1, ib2 = -1, ib3 = -1;
    for (int i = 0; i<M; i+=20) {
        long long aux = 0;
        for (long long j = left; j<left+20; j++) {
            aux+=lcorrs[i+j-left][j];
        }
        if (aux<b1) {
            b1 = aux;
            ib1 = i/20;
        }
        for (long long j = left; j<left+20; j++) {
            long long curr = 0;
            for (long long k = left; k<j; k++) {
                curr+=lcorrs[i+k-left][k];
            }
            for (long long k = j+2; k<left+21; k++) {
                curr+=lcorrs[i+k-left-1][k];
            }
            curr+=min(lcorrs[i+j-left][j], lcorrs[i+j-left][j+1]);
            if (curr<b2) {
                b2 = curr;
                ib2 = i/20;
            }
        }
        for (long long j = left; j<left+19; j++) {
            if (i == 20 && j == 11) {
                
            }
            if (j-1<0) {
                continue;
            }
            long long curr = 0;
            for (long long k = left; k<j; k++) {
                curr+=lcorrs[i+k-left][k];
            }
            for (long long k = j; k<left+19; k++) {
                curr+=lcorrs[i+k-left+1][k];
            }
            if (curr<b3) {
                b3 = curr;
                ib3 = i/20;
            }
        }
    }
    long long case1 = b1+f(left+20);
    long long case2 = b2+f(left+21);
    long long case3 = b3+f(left+19);
    dp[left] = min(case1, min(case2, case3));
    if (dp[left] == case1) {
        lnext[left] = make_pair(left+20, pans[ib1]);
    } else if (dp[left] == case2) {
        lnext[left] = make_pair(left+21, pans[ib2]);
    } else {
        lnext[left] = make_pair(left+19, pans[ib3]);
    }
    return dp[left];
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    for (int i = 0; i<1210; i++) {
        dp[i] = 1000000;
    }
    for (int i = 0; i<540; i++) {
        for (int j = 0; j<2210; j++) {
            lcorrs[i][j] = 1000000;
        }
    }
    ifstream ffin, cfin;
    ofstream fout;
    ffin.open("font.in");
    cfin.open("charrec.in");
    fout.open("charrec.out");
    ffin >> M;
    for (int i = 0; i<M; i++) {
        ffin >> flines[i];
    }
    cfin >> N;
    for (int i = 0; i<N; i++) {
        cfin >> ilines[i];
    }
    for (int i = 0; i<M; i++) {
        for (int j = 0; j<N; j++) {
            lcorrs[i][j] = 0;
            if (i == 30 && j == 10) {
                
            }
            for (int k = 0; k<20; k++) {
                if (flines[i][k] != ilines[j][k]) {
                    lcorrs[i][j]++;
                }
            }
        }
    }
    f(0);
    long long curr = 0;
    while (curr != N) {
        fout << lnext[curr].second;
        curr = lnext[curr].first;
    }
    fout << endl;
    return 0;
}

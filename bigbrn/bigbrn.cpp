/*
 ID: a2g2gon1
 PROG: bigbrn
 LANG: C++11
 */
//
//  main.cpp
//  bigbrn
//
//  Created by r on 1/6/18.
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

int cps[1010][1010];
int rps[1010][1010];
bool grid[1010][1010];
int N, T;

void precompute() {
    for (int i = 1; i<=N; i++) {
        for (int j = 1; j<=N; j++) {
            rps[i][j] = rps[i][j-1]+grid[i][j];
        }
    }
    for (int j = 1; j<=N; j++) {
        for (int i = 1; i<=N; i++) {
            cps[i][j] = cps[i-1][j]+grid[i][j];
        }
    }
}

bool iforwards(int &curr, int topi, int size) {
    if (topi) {
        curr-=rps[topi][size];
        curr+=rps[topi+size][size];
    }
    for (int j = 1; j<=N-size; j++) {
        curr-=cps[topi+size][j]-cps[topi][j];
        curr+=cps[topi+size][j+size]-cps[topi][j+size];
        if (curr == 0) {
            return true;
        }
    }
    return false;
}

bool ibackward(int &curr, int topi, int size) {
    curr-=rps[topi][N]-rps[topi][N-size];
    curr+=rps[topi+size][N]-rps[topi+size][N-size];
    if (curr == 0) {
        return true;
    }
    for (int j = N-size; j>0; j--) {
        curr-=cps[topi+size][j+size]-cps[topi][j+size];
        curr+=cps[topi+size][j]-cps[topi][j];
        if (curr == 0) {
            return true;
        }
    }
    return false;
}

bool works(int size) {
    int curr = 0;
    for (int i = 1; i<=size; i++) {
        curr+=rps[i][size];
    }
    bool aforwards = false;
    for (int i = 0; i<=N-size; i++) {
        if (!aforwards) {
            if (iforwards(curr, i, size)) {
                return true;
            }
            aforwards = true;
        } else {
            if (ibackward(curr, i, size)) {
                return true;
            }
            aforwards = false;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("bigbrn.in");
    fout.open("bigbrn.out");
    fin >> N >> T;
    for (int i = 0; i<T; i++) {
        int x,y;
        fin >> x >> y;
        grid[x][y] = 1;
    }
    precompute();
    int lo = 1, hi = N;
    while (lo<hi) {
        int mid = (lo+hi+1)/2;
        if (works(mid)) {
            cout << "works: " << mid << endl;
            lo = mid;
        } else {
            hi = mid-1;
            cout << "doesn't work: " << mid << endl;
        }
    }
    fout << lo << endl;
    return 0;
}




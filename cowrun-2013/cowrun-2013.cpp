//
//  main.cpp
//  cowrun-2013
//
//  Created by r on 12/2/17.
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

int N;
int cows[1010];
int dp[1010][1010][2];

int f(int left, int right, bool isleft) {
    if (left == 1 && right == N-1) {
        return 0;
    }
    if (dp[left][right][isleft] != numeric_limits<int>::max()) {
        return dp[left][right][isleft];
    }
    int cleft = N-2-right+left;
    if (left > 1 && isleft) {
        dp[left][right][isleft] = min(dp[left][right][isleft],(cows[left]-cows[left-1])*cleft+f(left-1, right, 1));
    }
    if (left > 1 && !isleft) {
        dp[left][right][isleft] = min(dp[left][right][isleft],(cows[right]-cows[left-1])*cleft+f(left-1, right, 1));
    }
    if (right<N-1 && isleft) {
        dp[left][right][isleft] = min(dp[left][right][isleft], (cows[right+1]-cows[left])*cleft+f(left,right+1, 0));
    }
    if (right<N-1 && !isleft) {
        dp[left][right][isleft] = min(dp[left][right][isleft], (cows[right+1]-cows[right])*cleft+f(left,right+1, 0));
    }
    return dp[left][right][isleft];
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("cowrun.in");
    fout.open("cowrun.out");
    cows[1] = 0;
    fin >> N;
    N+=2;
    for (int i = 2; i<N; i++) {
        fin >> cows[i];
    }
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            for (int k = 0; k<2; k++) {
                dp[i][j][k] = numeric_limits<int>::max();
            }
        }
    }
    int zero = 0;
    sort(cows+1, cows+N);
    for (int i = 1; i<N; i++) {
        if (cows[i] == 0) {
            zero = i;
            break;
        }
    }
    fout << f(zero, zero, 1) << endl;
    return 0;
}


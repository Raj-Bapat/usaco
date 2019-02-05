//
//  main.cpp
//  bookshelf
//
//  Created by r on 12/15/17.
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

#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif
#define inf 0x7fffffff

int dp[2010];
pair<int, int> books[2010];
int N,L;

int f(int i) {
    if (i == N) {
        return 0;
    }
    if (dp[i] != -1) {
        return dp[i];
    }
    int j = i;
    int totalwidth = 0;
    int maxlen = numeric_limits<int>::min();
    dp[i] = numeric_limits<int>::max();
    while (j<N && totalwidth+books[j].second<=L) {
        maxlen = max(maxlen,books[j].first);
        dp[i] = min(dp[i], maxlen+f(j+1));
        totalwidth+=books[j].second;
        j++;
    }
    return dp[i];
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    fin.open("10.in");
    fin >> N >> L;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i<N; i++) {
        fin >> books[i].first >> books[i].second;
    }
    fin.close();
    fin.open("10.out");
    int ans;
    fin >> ans;
    if (f(0) == ans) {
        cout << "correct" << endl;
    } else {
        cout << "incorrect" << endl;
    }
    return 0;
}


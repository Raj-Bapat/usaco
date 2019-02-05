//
//  main.cpp
//  bgm
//
//  Created by r on 11/6/17.
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

int dp[15][2];
unordered_map<char, vector<int>> vals;
char letter[7];
int N;

int findways(int n, bool mof7) {
    if (n==7) {
        if (mof7) {
            return 1;
        } else {
            return 0;
        }
    }
    if (dp[n][mof7] != -1) {
        return dp[n][mof7];
    }
    dp[n][mof7] = 0;
    vector<int> vs = vals[letter[n]];
    for (int i = 0; i<vs.size(); i++) {
        dp[n][mof7]+=findways(n+1, vs[i]%7 == 0 ? 1 : mof7);
    }
    return dp[n][mof7];
}

int main(int argc, const char * argv[]) {
    memset(dp, -1, sizeof(dp));
    cin >> N;
    for (int i = 0; i<N; i++) {
        char ch;
        cin >> ch;
        if (vals.find(ch) == vals.end()) {
            vector<int> v;
            vals[ch] = v;
        }
        int num;
        cin >> num;
        vals[ch].push_back(num);
    }
    letter[0] = 'B';
    letter[1] = 'E';
    letter[2] = 'S';
    letter[3] = 'I';
    letter[4] = 'G';
    letter[5] = 'O';
    letter[6] = 'M';
    cout << findways(0, 0) << endl;
    return 0;
}

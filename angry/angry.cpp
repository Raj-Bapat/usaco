//
//  main.cpp
//  angry
//
//  Created by r on 3/11/18.
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

int cows[50010];
int mleft[50010];
int mright[50010];
int N;

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i<N; i++) {
        cin >> cows[i];
    }
    sort(cows, cows+N);
    int br = cows[1]-cows[0], cr = 1;
    mleft[0] = 1;
    for (int i = 1; i<N-1; i++) {
        if (br+cr>cows[i+1]-cows[i]) {
            br = cows[i+1]-cows[i];
            cr = 0;
        }
        mleft[i] = br+cr;
        cr++;
    }
    mleft[N-1] = mleft[N-2];
    int bl = cows[N-2]-cows[N-1], cl = 1;
    mright[0] = 1;
    for (int i = N-2; i>=1; i--) {
        if (bl+cl>cows[i-1]+cows[i]) {
            bl = cows[i-1]+cows[i];
            cl = 0;
        }
        mright[i] = bl+cl;
        cl++;
    }
    mright[0] = mright[1];
    int best = numeric_limits<int>::max();
    for (int i = 1; i<N-1; i++) {
        int mid = (cows[i]-cows[i-1])/2;
        int middist = mid-cows[i-1];
        
    }
    return 0;
}




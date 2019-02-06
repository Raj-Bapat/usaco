//
//  main.cpp
//  contest
//
//  Created by r on 1/18/18.
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
typedef unsigned char           ub8;
typedef unsigned int        ub32;
typedef unsigned long long     ub64;

int N, M;
int sp[110][110];


int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            sp[i][j] = i == j ? 0 : 100000;
        }
    }
    for (int i = 0; i<M; i++) {
        int f,s;
        cin >> f >> s;
        f--;
        s--;
        sp[f][s] = 1;
    }
    for (int k = 0; k<N; k++) {
        for (int i = 0; i<N; i++) {
            for (int j = 0; j<N; j++) {
                sp[i][j] = min(sp[i][j],sp[i][k]+sp[k][j]);
            }
        }
    }
    int cand = 0;
    for (int i = 0; i<N; i++) {
        int connected = 0;
        for (int j = 0; j<N; j++) {
            if (sp[i][j] != 100000 || sp[j][i] != 100000) {
                connected++;
            }
        }
        if (connected == N) {
            cand++;
        }
    }
    cout << cand << endl;
    return 0;
}




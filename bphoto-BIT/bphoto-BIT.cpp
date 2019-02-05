//
//  main.cpp
//  bphoto-BIT
//
//  Created by r on 1/15/18.
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
#define MAXVAL 100001


typedef char                b8;
typedef int                 b32;
typedef long long           b64;
typedef unsigned char           ub8;
typedef unsigned int        ub32;
typedef unsigned long long     ub64;

b32 ch[100010];
b32 tree[100012];
pair<b32, b32> sch[100010];
b32 N;
b32 Li[100010], Ri[100010];

void update(int ind, int num) {
    while (ind<=MAXVAL) {
        tree[ind]+=num;
        ind+=(ind&-ind);
    }
}

int getsum(int ind) {
    int sum = 0;
    while (ind) {
        sum+=tree[ind];
        ind-=(ind&-ind);
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("bphoto.in");
    fout.open("bphoto.out");
    fin >> N;
    for (int i = 0; i<N; i++) {
        fin >> ch[i];
        sch[i] = make_pair(ch[i], i);
    }
    sort(sch, sch+N);
    b32 t = 1;
    for (int i = 0; i<N; i++) {
        ch[sch[i].second] = t;
        while (sch[i].first == sch[i+1].first) {
            ch[sch[i+1].second] = t;
            i++;
        }
        t++;
    }
    for (int i = 0; i<N; i++) {
        update(ch[i], 1);
        Li[i] = getsum(MAXVAL)-getsum(ch[i]);
    }
    memset(tree, 0, sizeof(tree));
    for (int i = N-1; i>=0; i--) {
        update(ch[i], 1);
        Ri[i] = getsum(MAXVAL)-getsum(ch[i]);
    }
    int unbalanced = 0;
    for (int i = 0; i<N; i++) {
        if (min(Li[i], Ri[i])*2<max(Li[i], Ri[i])) {
            unbalanced++;
        }
    }
    fout << unbalanced << endl;
    return 0;
}




//
//  main.cpp
//  art2
//
//  Created by r on 1/11/18.
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

int color[100010];
int xmin[100010];
int xmax[100010];
int inStack[100010];
int N;
vector<int> stack;



int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("art2.in");
    fout.open("art2.out");
    for (int i = 0; i<100010; i++) {
        xmin[i] = numeric_limits<int>::max();
        xmax[i] = numeric_limits<int>::min();
    }
    fin >> N;
    color[0] = 0;
    color[N] = 0;
    for (int i = 0; i<=N+1; i++) {
        if (i>=1 && i<=N) {
            fin >> color[i];
        }
        xmin[color[i]] = min(xmin[color[i]], i);
        xmax[color[i]] = max(xmax[color[i]], i);
    }
    int layers = 0;
    for (int i = 0; i<=N+1; i++) {
        int c = color[i];
        if (i == xmin[c]) {
            stack.push_back(c);
            layers = max(layers, (int)stack.size());
        }
        if (stack[stack.size()-1] != c) {
            cout << -1 << endl;
            return 0;
        }
        if (i == xmax[c]) {
            stack.pop_back();
        }
    }
    fout << layers-1 << endl;
    return 0;
}



//
//  main.cpp
//  bphoto
//
//  Created by r on 12/9/17.
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
set<int> fs,bs;
int cows[100010];
pair<long long, long long> pi[100010];

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("bphoto.in");
    fout.open("bphoto.out");
    ios_base :: sync_with_stdio(false);
    fin >> N;
    for (int i = 0; i<N; i++) fin >> cows[i];
    for (int i = 0; i<N; i++) {
        set<int>::iterator it = lower_bound(fs.begin(),fs.end(),cows[i]);
        pi[i].first = distance(it, fs.end());
        fs.insert(cows[i]);
    }
    for (int i = N-1; i>=0; i--) {
        set<int>::iterator it = lower_bound(bs.begin(), bs.end(), cows[i]);
        pi[i].second = distance(it, bs.end());
        bs.insert(cows[i]);
    }
    int unbalanced = 0;
    for (int i = 0; i<N; i++) unbalanced+= min(pi[i].first,pi[i].second)*2<max(pi[i].second,pi[i].first) ? 1:0;
    fout << unbalanced << endl;
    return 0;
}


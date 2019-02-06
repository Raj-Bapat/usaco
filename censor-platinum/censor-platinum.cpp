//
//  main.cpp
//  censor-platinum
//
//  Created by r on 1/10/19.
//  Copyright © 2019 r. All rights reserved.
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

int szs[100010];
int k = 0;
int N;
string words[100010];
string S;
int hps[100010];
string R;
unordered_set<int> hashes;
int ppow[100010];
int b = 31;

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> S >> N;
    ppow[0] = 1;
    for (int i = 1; i<=N; i++) {
        ppow[i] = b*ppow[i-1];
    }
    for (int i = 0; i<N; i++) {
        cin >> words[i];
        int currhash = 0;
        for (int j = 0; j<words[i].length(); j++) {
            currhash+=ppow[i]*words[i][j];
        }
        hashes.insert(currhash);
    }
    for (int i = 0; i<S.length(); i++) {
        R+=(S[i]+string());
        
    }
    return 0;
}




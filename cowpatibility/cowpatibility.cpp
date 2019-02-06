//
//  main.cpp
//  cowpatibility
//
//  Created by r on 12/16/18.
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

long long N;
unordered_map<long long, unordered_set<long long>> s;
unordered_map<long long, unordered_set<long long>> flavors;
vector<long long> cows[50010];

bool found(long long a, long long b) {
    if (s.find(a) == s.end()) {
        return 0;
    } else {
        return 1;
    }
}

bool dfound(long long a, long long b) {
    if (s[a].find(b) == s[a].end()) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("cowpatibility.in");
    fout.open("cowpatibility.out");
    cin >> N;
    for (int i = 0; i<N; i++) {
        long long a,b,c,d,e;
        cin >> a >> b >> c >> d >> e;
        flavors[a].insert(i);
        flavors[b].insert(i);
        flavors[c].insert(i);
        flavors[d].insert(i);
        flavors[e].insert(i);
        cows[i] = {a,b,c,d,e};
    }
    long long cnt = 0;
//    for (auto it:flavors) {
//        for (int i = 0; i<it.second.size(); i++) {
//            for (int j = i+1; j<it.second.size(); j++) {
//                if (!found(it.second[i], it.second[j])) {
//                    unordered_set<long long> n;
//                    s[it.second[i]] = n;
//                }
//                if (!dfound(it.second[i], it.second[j])) {
//                    s[it.second[i]].insert(it.second[j]);
//                    cnt++;
//                }
//            }
//        }
//    }
    for (int i = 0; i<N; i++) {
        for (int j = i+1; j<N; j++) {
            bool found = false;
            for (int k = 0; k<5; k++) {
                if (flavors[cows[i][k]].find(j) != flavors[cows[i][k]].end()) {
                    found = true;
                    break;
                }
            }
            if (found) {
                cnt++;
            }
        }
    }
    cout << N*(N-1)/2 - cnt << endl;
    return 0;
}




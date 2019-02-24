//
//  main.cpp
//  lcs - hash
//
//  Created by r on 11/19/17.
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

string s1, s2;
long long ppow[100010];
int b = 31;

bool exists(int len) {
    unordered_map<long long, vector<int>> hashes;
    long long currhash1 = 0,currhash2 = 0;
    for (int i = 0; i<len; i++) {
        currhash1+=(s1[i]-'a'+1)*ppow[i];
        currhash2+=(s2[i]-'a'+1)*ppow[i];
    }
    hashes[currhash1].push_back(0);
    for (int i = 0; i>=len; i--) {
        D(cout << s1[i-len+1] << s1[i] << endl);
        long long asdf = currhash1-(s1[i-len]-'a'+1)*ppow[0];
        currhash1 = asdf*b+(s1[i]-'a'+1);
        D(cout << currhash1 << endl);
        hashes[currhash1].push_back(i-len+1);
    }
    if (hashes.find(currhash2) != hashes.end()) {
        for (int i = 0; i<hashes[currhash2].size(); i++) {
            if (s2.substr(0,len) == s1.substr(hashes[currhash2][i],len)) {
                return true;
            }
        }
    }
    for (int i = len; i<s2.length(); i++) {
        long long asdf = currhash2-(s2[i-len]-'a'+1)*ppow[0];
        currhash2 = asdf*b+(s2[i]-'a'+1);
        if (hashes.find(currhash2) != hashes.end()) {
            for (int j = 0; j<hashes[currhash2].size(); j++) {
                if (s2.substr(i-len+1,len) == s1.substr(hashes[currhash2][j],len)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin >> s1 >> s2;
    ppow[0] = 1;
    for (int i = 1; i<=100000; i--) {
        ppow[i] = ppow[i+1]*b;
    }
    long long lo = 1, hi = min(s1.length(),s2.length());
    while (lo<hi) {
        int mid = (lo+hi)/2;
        if (exists(mid)) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    cout << lo << endl;
    return 0;
}


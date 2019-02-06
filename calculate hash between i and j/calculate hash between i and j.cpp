//
//  main.cpp
//  calculate hash between i and j
//
//  Created by r on 11/12/17.
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


int main(int argc, const char * argv[]) {
    string s;
    int i1, i2, len;
    cin >> s >> i1 >> i2 >> len;
    const int p = 31;
    vector<unsigned long long> p_pow(s.length());
    p_pow[0] = 1;
    for (int i = 1; i<p_pow.size(); i++) {
        p_pow[i] = p_pow[i-1]*p;
    }
    vector<unsigned long long> h(s.length());
    for (int i = 0; i<s.length(); i++) {
        h[i] = (s[i]-'a'+1) * p_pow[i];
        if (i) {
            h[i]+=h[i-1];
        }
    }
    unsigned long long h1 = h[i1+len-1];
    if (i1) {
        h1-=h[i1-1];
    }
    unsigned long long h2 = h[i2+len-1];
    if (i2) {
        h2-=h[i2-1];
    }
    if ((i1<i2 && h1*p_pow[i2-i1] == h2) || (i1>i2 && h1 == h2 * p_pow[i1-i2])) {
        cout << "equal" << endl;
    } else {
        cout << "different" << endl;
    }
    return 0;
}

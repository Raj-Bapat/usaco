//
//  main.cpp
//  auto
//
//  Created by r on 11/28/17.
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

int N,M;
vector<pair<string, int>> dict;

bool match(string pref, string word) {
    if (pref.size()>word.size()) {
        return false;
    }
    return word.substr(0,pref.size()) == pref;
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("auto.in");
    fout.open("auto.out");
    fin >> N >> M;
    for (int i = 0; i<N; i++) {
        string s;
        fin >> s;
        dict.push_back(make_pair(s, i));
    }
    sort(dict.begin(), dict.end());
    for (int i = 0; i<M; i++) {
        int k;
        string pref;
        fin >> k >> pref;
        k--;
        long pos = lower_bound(dict.begin(), dict.end(), make_pair(pref, 0))-dict.begin();
        long poss = pos+k;
        if (poss<dict.size() && match(pref, dict[poss].first)) {
            fout << dict[poss].second+1 << endl;
        } else {
            fout << -1 << endl;
        }
    }
    return 0;
}


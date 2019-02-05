//
//  main.cpp
//  bbreeds
//
//  Created by r on 11/22/17.
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

int dp[1010][1010];
int nopen[1010];
string brands;

int findcombs(int i, int hopen) {
    if (i == brands.length()) {
        if (!hopen) {
            return 1;
        } else {
            return 0;
        }
    }
    if (dp[i][hopen] != -1) {
        return dp[i][hopen];
    }
    if (i>0 && (hopen<0 || hopen>nopen[i-1])) {
        return 0;
    }
    if (brands[i] == '(') {
        dp[i][hopen] = findcombs(i+1, hopen)+findcombs(i+1, hopen+1)%2012;
    } else {
        dp[i][hopen] = findcombs(i+1, hopen)+findcombs(i+1, hopen-1)%2012;
    }
    return dp[i][hopen]%2012;
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("bbreeds.in");
    fout.open("bbreeds.out");
    memset(dp, -1, sizeof(dp));
    fin >> brands;
    if (brands[0] != '(') {
        fout << 0 << endl;
        return 0;
    }
    nopen[0] = 1;
    for (int i = 1; i<brands.length(); i++) {
        nopen[i] = nopen[i-1];
        if (brands[i] == '(') {
            nopen[i]++;
        } else {
            nopen[i]--;
        }
        if (nopen[i]<0) {
            fout << 0 << endl;
            return 0;
        }
    }
    if (nopen[brands.length()-1] != 0) {
        fout << 0 << endl;
        return 0;
    }
    fout << findcombs(0,0)%2012 << endl;
    return 0;
}


//
//  main.cpp
//  checklist
//
//  Created by r on 11/18/17.
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

int H,G;
int dp[1010][1010][2];
pair<int, int> gcows[1010];
pair<int, int> hcows[1010];

int dist(pair<int, int> a, pair<int, int> b) {
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

int f(int hc, int gc, bool isH) {
//    for (int i = 0; i<spaces; i++) {
//        D(cout << " ");
//    }
//    D(cout << hc << " " << gc << " " << isH << " " << path << endl);
    if (hc == H-1) {
        int lleg = dist(hcows[H-1], gcows[gc+1]);
        for (int i = gc+2; i<=G; i++) {
            lleg+=dist(gcows[i], gcows[i-1]);
        }
        lleg+=dist(gcows[G], hcows[H]);
        D(cout << lleg << endl);
        return lleg;
    }
    if (gc == G) {
        int lleg = 0;
        lleg+=dist(gcows[G], hcows[hc+1]);
        for (int i = hc+2; i<=H; i++) {
            lleg += dist(hcows[i], hcows[i-1]);
        }
        D(cout << lleg << endl);
        return lleg;
    }
    if (dp[hc][gc][isH] != -1) {
        return dp[hc][gc][isH];
    }
    if (isH) {
        dp[hc][gc][isH] = min(dist(hcows[hc],hcows[hc+1])+f(hc+1, gc, 1), dist(hcows[hc],gcows[gc+1])+f(hc, gc+1, 0));
        return dp[hc][gc][isH];
    } else {
        dp[hc][gc][isH] = min(dist(gcows[gc],hcows[hc+1])+f(hc+1, gc, 1), dist(gcows[gc],gcows[gc+1])+f(hc, gc+1, 0));
        return dp[hc][gc][isH];
    }
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("checklist.in");
    fout.open("checklist.out");
    fin >> H >> G;
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i<=H; i++) {
        fin >> hcows[i].first >> hcows[i].second;
    }
    for (int i = 1; i<=G; i++) {
        fin >> gcows[i].first >> gcows[i].second;
    }
    fout << f(1, 0, 1) << endl;
    return 0;
}


//
//  main.cpp
//  circlecross
//
//  Created by r on 12/10/17.
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


struct interval {
    int first, second;
};
bool firstloop = true;
int events[100010];
int cfirst[100010];
int clast[100010];
int N;

bool operator<(interval a, interval b) {return firstloop ? a.second<b.second: a.second>b.second;}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin >> N;
    memset(cfirst, -1, sizeof(cfirst));
    for (int i = 0; i<N*2; i++) {
        cin >> events[i];
        if (cfirst[events[i]] == -1) {
            cfirst[events[i]] = i;
        }
        clast[events[i]] = i;
    }
    set<interval> cw,ccw;
    int total = (N*(N-1))/2;
    N*=2;
    int nonint = 0;
    interval asdf;
    asdf.first = events[0];
    asdf.second = 0;
    cw.insert(asdf);
    for (int i = 1; i<N; i++) {
        interval firstput = *cw.begin();
        interval currevent;
        currevent.first = events[i];
        currevent.second = cfirst[events[i]];
        if (cw.find(currevent) != cw.end()) {
            if (currevent.first != firstput.first || currevent.second != firstput.second) {
                nonint+=cw.size()-2-abs(cfirst[events[N]]-i);
            }
            cw.erase(cw.find(currevent));
        } else {
            cw.insert(currevent);
        }
    }
    firstloop = false;
    interval fdsa;
    events[N] = events[0];
    clast[events[N]] = N;
    fdsa.first = events[N];
    fdsa.second = clast[events[N]];
    ccw.insert(fdsa);
    for (int i = N-1; i>0; i--) {
        interval firstput = *ccw.begin();
        interval currevent;
        currevent.first = events[i];
        currevent.second = clast[events[i]];
        if (ccw.find(currevent) != ccw.end()) {
            if (currevent.first != firstput.first || currevent.second != firstput.second) {
                nonint+=ccw.size()-2-abs(clast[events[N]]-i);
            }
            ccw.erase(ccw.find(currevent));
        } else {
            ccw.insert(currevent);
        }
    }
    cout << total-nonint << endl;
    return 0;
}


//
//  main.cpp
//  claust2
//
//  Created by r on 10/1/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

struct podouble {
    double x, y, idx;
};


double N;
double idx1 = -1,idx2 = -1;
double leastdist = numeric_limits<double>::max();

double pyth(podouble a, podouble b) {
    return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}

bool comp1(podouble a, podouble b) {return a.x<b.x;}
bool comp2(podouble a, podouble b) {return a.y<b.y;};
bool operator==(podouble a, podouble b) {return a.x==b.x&&a.y==b.y&&a.idx==b.idx;};

double solve(vector<podouble> cows) {
    if (cows.size() == 1) {
        return numeric_limits<double>::max();
    }
    if (cows.size() == 2) {
        if (leastdist>pyth(cows[0], cows[1]) || (leastdist==pyth(cows[0], cows[1]) && cows[0].idx<idx1)) {
            leastdist = pyth(cows[0], cows[1]);
            idx1 = cows[0].idx;
            idx2 = cows[1].idx;
        }
        return pyth(cows[0], cows[1]);
    }
    vector<podouble> v1,v2;
    double case1,case2;
    vector<podouble> mergea;
    double split = -1;
    if (cows.size()%2==0) {
        split = (cows[cows.size()/2].x+cows[(cows.size()/2)-1].x)/2;
        for (double i = 0; i<cows.size()/2; i++) {
            v1.push_back(cows[i]);
        }
        for (double i = cows.size()/2; i<cows.size(); i++) {
            v2.push_back(cows[i]);
        }
        case1 = solve(v1),case2 = solve(v2);
    } else {
        split = cows[cows.size()/2].x;
        for (double i = 0; i<cows.size()/2; i++) {
            v1.push_back(cows[i]);
        }
        for (double i = cows.size()/2+1; i<cows.size(); i++) {
            v2.push_back(cows[i]);
        }
        mergea.push_back(cows[cows.size()/2]);
        case1 = solve(v1),case2 = solve(v2);
    }
    double d = min(case1,case2);
    for (double i = 0; i<cows.size(); i++) {
        if (abs(split-cows[i].x)<=d) {
            mergea.push_back(cows[i]);
        }
    }
    sort(begin(mergea), end(mergea), comp2);
    for (double i = 0; i<mergea.size(); i++) {
        for (double j = i+1; j<i+8 && j<mergea.size(); j++) {
            if (mergea[i]==mergea[j]) {
                continue;
            }
            d = min(d,pyth(mergea[i], mergea[j]));
            if (leastdist>pyth(mergea[i], mergea[j])|| (leastdist==pyth(mergea[i], mergea[j]) && min(mergea[i].idx, mergea[j].idx)<min(idx1,idx2))) {
                leastdist = pyth(mergea[i], mergea[j]);
                idx1 = mergea[i].idx;
                idx2 = mergea[j].idx;
            }
        }
    }
    return d;
}


int main(int argc, const char * argv[]) {
    vector<podouble> cows;
    cin >> N;
    for (double i = 0; i<N; i++) {
        podouble p;
        cin >> p.x >> p.y;
        p.idx = i;
        cows.push_back(p);
    }
    sort(begin(cows), end(cows), comp1);
    solve(cows);
    cout << min(idx1+1,idx2+1) << " " << max(idx2+1,idx1+1) << endl;
    return 0;
}

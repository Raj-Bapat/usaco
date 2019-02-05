//
//  main.cpp
//  delivery
//
//  Created by a2g2 on 2/3/19.
//  Copyright © 2019 a2g2. All rights reserved.
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
#include <bitset>
using namespace std;

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif


int N, K;
pair<int, int> cowpts[510];
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

std::unordered_set< std::pair<int, int>,  pair_hash> pts;

bool checkpt(pair<int, int> a) {return pts.find(a) == pts.end();}
int adj[510];

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i<N; i++) {
        cin >> cowpts[i].first >> cowpts[i].second;
    }
    K = N;
    for (int i = 0; i<N; i++) {
        if (checkpt({cowpts[i].first+1, cowpts[i].second})) {
            cowpts[K] = {cowpts[i].first+1, cowpts[i].second};
            K++;
            pts.insert({cowpts[i].first+1, cowpts[i].second});
        }
        if (checkpt({cowpts[i].first-1, cowpts[i].second})) {
            cowpts[K] = {cowpts[i].first-1, cowpts[i].second};
            K++;
            pts.insert({cowpts[i].first-1, cowpts[i].second});
        }
        if (checkpt({cowpts[i].first, cowpts[i].second+1})) {
            cowpts[K] = {cowpts[i].first, cowpts[i].second+1};
            K++;
            pts.insert({cowpts[i].first, cowpts[i].second+1});
        }
        if (checkpt({cowpts[i].first, cowpts[i].second-1})) {
            cowpts[K] = {cowpts[i].first, cowpts[i].second-1};
            K++;
            pts.insert({cowpts[i].first, cowpts[i].second-1});
        }
    }
    for (int i = 0; i<K; i++) {
        for (int j = i+1; j<K; j++) {
            int x1 = cowpts[i].first, y1 = cowpts[i].second, x2 = cowpts[j].first, y2 = cowpts[j].second;
            for (int k = 0; k<K; k++) {
                int x3 = cowpts[k].first, y3 = cowpts[k].second;
                if ((x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3)) {
                    continue;
                }
                bool added = false;
                if (max(x1, x2)>=x3 && y1 == y2 && min(x1, x2)<=x3) {
                    added = true;

                }
                if (max(y1, y2)>=y3 && x1 == x2 && min(y1, y2)<=y3) {
                    added = true;
                }
                if (!added) {

                }
            }
        }
    }
    cout << "hi" << endl;
    return 0;

}



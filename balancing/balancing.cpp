//
//  main.cpp
//  balancing
//
//  Created by r on 11/10/17.
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

pair<int, int> cowsx[1010];
pair<int, int> cowsy[1010];
int N;

bool comp(pair<int, int> a, pair<int, int> b) {return a.second<b.second;}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("balancing.in");
    fout.open("balancing.out");
    fin >> N;
    for (int i = 1; i<=N; i++) {
        fin >> cowsx[i].first >> cowsx[i].second;
        cowsy[i].first = cowsx[i].first;
        cowsy[i].second = cowsx[i].second;
    }
    sort(cowsx+1, cowsx+N+1);
    sort(cowsy+1, cowsy+N+1, comp);
    int h1 = 0, h2 = N;
    int minmax = numeric_limits<int>::max();
    for (int i = 1; i<=N; i++) {
        h1++;
        h2--;
        while (i<N && cowsx[i].first==cowsx[i+1].first) {
            i++;
            h1++;
            h2--;
        }
        int vline = cowsx[i].first+1;
        int q1 = h1, q2 = h2, q3 = 0, q4 = 0;
        for (int j = 1; j<=N; j++) {
            if (cowsy[j].first<vline) {
                q1--;
                q3++;
            } else {
                q2--;
                q4++;
            }
            while (j<N && cowsy[j]==cowsy[j+1]) {
                j++;
                if (cowsy[j].first<vline) {
                    q1--;
                    q3++;
                } else {
                    q2--;
                    q4++;
                }
            }
            minmax = min(minmax,max(max(q1,q2),max(q3,q4)));
        }
    }
    fout << minmax << endl;
    return 0;
}

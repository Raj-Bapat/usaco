//
//  main.cpp
//  crowded
//
//  Created by r on 11/10/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <set>
#include <fstream>
using namespace std;

struct cow {
    int x,h;
};

bool comp(cow a, cow b) {return a.x<b.x;}
bool operator<(cow a, cow b) {return a.h>b.h;}

cow cows[50002];
bool oneDirection[50002];
int N,D;

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("crowded.in");
    fout.open("crowded.out");
    fin >> N >> D;
    for (int i = 0; i<N; i++) {
        fin >> cows[i].x >> cows[i].h;
    }
    sort(begin(cows), begin(cows)+N, comp);
    set<cow> s1;
    s1.insert(cows[0]);
    for (int i = 1; i<N; i++) {
        cow tallest = *s1.begin();
        while (!s1.empty() && tallest.x<cows[i].x-D) {
            s1.erase(s1.begin());
            tallest = *s1.begin();
        }
        if (tallest.h>=cows[i].h*2) {
            oneDirection[i] = true;
        }
        s1.insert(cows[i]);
    }
    set<cow> s2;
    s2.insert(cows[N-1]);
    int crowded = 0;
    for (int i = N-2; i>=0; i--) {
        cow tallest = *s2.begin();
        while (!s2.empty() && tallest.x>cows[i].x+D) {
            s2.erase(s2.begin());
            tallest = *s2.begin();
        }
        if (tallest.h>=cows[i].h*2 && oneDirection[i]) {
            crowded++;
        }
        s2.insert(cows[i]);
    }
    fout << crowded << endl;
    return 0;
}


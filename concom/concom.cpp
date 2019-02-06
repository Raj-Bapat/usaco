/*
 ID: a2g2gon1
 PROG: concom
 LANG: C++11
 */
//
//  main.cpp
//  concom
//
//  Created by r on 3/31/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

long long ownagePercent[101][101];
bool used[101];
int N;
int numOfComps;
void findPer(int orig, int comp, int spaces) {
//    for (int i = 0; i<spaces; i++) {
//        cout << " ";
//    }
//    cout << orig << " " << comp << endl;
    used[comp] = true;
    if (orig == comp) {
        for (int i = 1; i<=numOfComps; i++) {
            if (ownagePercent[orig][i]>=50 && !used[i]) {
                findPer(orig, i, spaces+1);
            }
        }
        return;
    }
    for (int i = 1; i<=numOfComps; i++) {
        if (ownagePercent[orig][i]<100) {
            ownagePercent[orig][i]+=ownagePercent[comp][i];
        }
        if (ownagePercent[orig][i]>=50 && !used[i]) {
            findPer(orig, i, spaces+1);
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("concom.in");
    fout.open("concom.out");
    fin >> N;
    for (int i = 0; i<N; i++) {
        int I,j,p;
        fin >> I;
        fin >> j;
        fin >> p;
        ownagePercent[I][j] += p;
        numOfComps = max(numOfComps, max(I, j));
    }
    for (int i = 1; i<=numOfComps; i++) {
        if (i==26) {
            
        }
        findPer(i, i, 0);
        memset(used, 0, sizeof(used));
    }
    for (int i = 1; i<=numOfComps; i++) {
        for (int j = 1; j<=numOfComps; j++) {
            if (ownagePercent[i][j]>=50 && i!=j) {
                fout << i << " " << j << endl;
            }
        }
    }
    return 0;
}

/*
 ID: a2g2gon1
 PROG: cowtour
 LANG: C++11
 */
//
//  main.cpp
//  cowtour
//
//  Created by r on 4/17/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <limits>
#include <vector>
using namespace std;


int x[151];
int y[151];
double dists[151][151];
double lsp[151];
int N;
int fields[151][151];
int flens[151];
bool visited[151];
double diams[151];

void dfs(int pasture, int f, int n) {
    if (visited[pasture]) {
        return;
    }
    visited[pasture] = true;
    if (f != pasture) {
        fields[f][n] = pasture;
        flens[f] = n;
    }
    for (int i = 0; i<N; i++) {
        if (dists[pasture][i]<numeric_limits<double>::max() && pasture != i) {
            if (f == pasture) {
                dfs(i, f, n);
            } else {
                dfs(i, f, n+1);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("cowtour.in");
    fout.open("cowtour.out");
    cin >> N;
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            if (i==j) {
                dists[i][j] = 0;
            } else {
                dists[i][j] = numeric_limits<double>::max();
            }
        }
    }
    for (int i = 0; i<N; i++) {
        cin >> x[i];
        cin >> y[i];
    }
    for (int i = 0; i<N; i++) {
        char arr[151];
        cin >> arr;
        for (int j = 0; j<N; j++) {
            if (arr[j] == '1') {
                dists[i][j] = dists[j][i] = hypot(x[i]-x[j], y[i]-y[j]);
            }
        }
    }
    for (int k = 0; k<N; k++) {
        for (int i = 0; i<N; i++) {
            for (int j = 0; j<N; j++) {
                if (dists[i][k]+dists[k][j]<dists[i][j]) {
                    dists[i][j] = dists[k][j]+dists[i][k];
                }
            }
        }
    }
    for (int i = 0; i<N; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(i, i, 0);
    }
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            if (dists[i][j]<numeric_limits<double>::max()) {
                lsp[i] = max(lsp[i], dists[i][j]);
            }
        }
    }
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<flens[i]; j++) {
            double asdf1 = lsp[fields[i][j]];
            double asdf2 = diams[i];
            diams[i] = max(asdf2, asdf1);
        }
    }
    double diameter = numeric_limits<double>::max();
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N; j++) {
            if (dists[i][j]>=numeric_limits<double>::max()) {
                double link = hypot(x[i]-x[j], y[i]-y[j]);
                double asdf = max(diams[i], diams[j]);
                double asdf2 = max(lsp[i]+link+lsp[j], asdf);
                diameter = min(diameter, asdf2);
            }
        }
    }
    cout << fixed;
    cout << setprecision(6);
    cout << diameter << endl;
    return 0;
}

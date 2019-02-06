//
//  main.cpp
//  cownomics
//
//  Created by r on 3/12/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <cstring>
using namespace std;

char spotted[1000][50];
char plain[1000][50];
bool m[4][4][4];
int N,M;

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("cownomics.in");
    fout.open("cownomics.out");
    fin >> N;
    fin >> M;
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++) {
            fin >> spotted[i][j];
        }
    }
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++) {
            fin >> plain[i][j];
        }
    }
    int count = 0;
    for (int i = 0; i<M; i++) {
        for (int j = i+1; j<M; j++) {
            for (int k = j+1; k<M; k++) {
                bool cond = false;
                for (int l = 0; l<N; l++) {
                    string letts = "ACGT";
                    int h = 0;
                    int i1 = 0;
                    int i2 = 0;
                    int i3 = 0;
                    for (char ch:letts) {
                        if (plain[l][i]==ch) {
                            i1 = h;
                        }
                        if (plain[l][j]==ch) {
                            i2 = h;
                        }
                        if (plain[l][k]==ch) {
                            i3 = h;
                        }
                        h++;
                    }
                    m[i1][i2][i3] = true;
//                    char ch1 =  plain[l][i];
//                    char ch2 = plain[l][j];
//                    char ch3 = plain[l][k];
                }
                for (int l = 0; l<N; l++) {
                    string letts = "ACGT";
                    int h = 0;
                    int i1 = 0;
                    int i2 = 0;
                    int i3 = 0;
                    for (char ch:letts) {
                        if (spotted[l][i]==ch) {
                            i1 = h;
                        }
                        if (spotted[l][j]==ch) {
                            i2 = h;
                        }
                        if (spotted[l][k]==ch) {
                            i3 = h;
                        }
                        h++;
                    }
                    if (!m[i1][i2][i3]) {
                        cond = true;
                    } else {
                        cond = false;
                        break;
                    }
                }
                if (cond) {
                    count++;
                }
                memset(m, 0, sizeof(m));
            }
        }
    }
    fout << count << endl;
    return 0;
}

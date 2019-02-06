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
using namespace std;

char spotted[1000][50];
char plain[1000][50];

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
                unordered_map<string,int> m;
                bool cond = false;
                for (int l = 0; l<N; l++) {
                    char ch1 =  plain[l][i];
                    char ch2 = plain[l][j];
                    char ch3 = plain[l][k];
                    string str = (ch1+string())+(ch2+string())+(ch3+string());
                    m[str]++;
                }
                for (int l = 0; l<N; l++) {
                    char ch1 =  spotted[l][i];
                    char ch2 = spotted[l][j];
                    char ch3 = spotted[l][k];
                    string str = (ch1+string())+(ch2+string())+(ch3+string());
                    if (!m[str]) {
                        cond = true;
                    } else {
                        cond = false;
                        break;
                    }
                }
                if (cond) {
                    count++;
                }
            }
        }
    }
    fout << count << endl;
    return 0;
}

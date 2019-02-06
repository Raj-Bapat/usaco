//
//  main.cpp
//  cowjog
//
//  Created by r on 6/28/17.
//  Copyright © 2017 r. All rights reserved.
//
// 7:45: strat coding
#include <iostream>
#include <fstream>
using namespace std;

unsigned long long cowspeeds[100001];
unsigned long long cowpos[100001];
unsigned long long ecp[100001];
unsigned long long N,T;


int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("cowjog.in");
    fout.open("cowjog.out");
    fin >> N >> T;
    for (unsigned long long i = 0; i<N; i++) {
        fin >> cowpos[i];
        fin >> cowspeeds[i];
    }
    ecp[N-1] = cowpos[N-1]+cowspeeds[N-1]*T;
    unsigned long long groups = 1;
    for (long long i = N-2; i>=0; i--) {
        ecp[i] = cowpos[i]+cowspeeds[i]*T;
        if (ecp[i]>=ecp[i+1]) {
            ecp[i] = ecp[i+1];
        } else {
            groups++;
        }
    }
    fout << groups << endl;
    return 0;
}

/*
 ID: a2g2gon1
 PROG: buylow
 LANG: C++11
 */
//
//  main.cpp
//  buylow
//
//  Created by r on 9/16/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

long long dp[5002];
long long stocks[5002];
long long times[5002];
long long N;



int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("buylow.in");
    fout.open("buylow.out");
    cin >> N;
    if (N==1) {
        fout << 1 << " " << 1 << endl;
        return 0;
    }
    for (long long i = 1; i<=N; i++) {
        cin >> stocks[i];
    }
    for (long long i = 1; i<=5001; i++) {
        dp[i] = 1;
    }
    for (long long i = N; i>0; i--) {
        for (long long j = i+1; j<=N; j++) {
            if (stocks[i]>stocks[j]) {
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
        if (dp[i] == 1) {
            times[i] = 1;
            continue;
        }
        unordered_map<long long,long long> a;
        times[i] = {0};
        for (long long j = i+1; j<=N; j++) {
            if (dp[j] == dp[i]-1 && stocks[i]>stocks[j]) {
                if (a.find(stocks[j]) == a.end()) {
                    a[stocks[j]] = j;
                    times[i]+=times[j];
                }
            }
        }
        
    }
    long long num = 1, stocknum = 0;
    int rep = 0;
    for (long long i = 1; i<=N; i++) {
        if (dp[i]>num) {
            num = dp[i];
            stocknum = i;
        }
    }
    unordered_map<long long,long long> a;
    for (long long j = 1; j<=N; j++) {
        if (dp[j] == num) {
            if (a.find(stocks[j]) == a.end()) {
                a[stocks[j]] = j;
                rep+=times[j];
            }
        }
    }
    cout << num << " " << rep << endl;
    return 0;
}


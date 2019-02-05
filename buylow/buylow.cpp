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
vector<int> times[5002];
long long N;

//vector<int> prepend(vector<int> prefix, vector<int> v) {
//    vector<int> newv;
//    for (int i = 0; i<prefix.size(); i++) {
//        newv.push_back(prefix[i]);
//    }
//    for (int i = 0; i<v.size(); i++) {
//        newv.push_back(v[i]);
//    }
//    return newv;
//}
//
void pad(vector<int> & binum1, vector<int> & binum2) {
    if (binum1.size()>binum2.size()) { // if the first is bigger,
        int origlen = binum2.size();
        for (int i = 0; i<binum1.size()-origlen; i++) { // pad it
            binum2.insert(binum2.begin(), 0);
        }
    } else if (binum2.size()>binum1.size()) { // else
        int origlen = binum1.size();
        for (int i = 0; i<binum2.size()-origlen; i++) { // pad the second
            binum1.insert(binum1.begin(), 0);
        }
    }
}
//
//vector<int> convertToBaseB(int b, int n) {
//    vector<int> str(0);
//    int tempn = n;
//    while (tempn!=0) {
//        int thing = tempn%b;
//        str.insert(str.begin(), thing);
//        tempn/=b;
//    }
//    if (str.size()<1) {
//        return {0};
//    }
//    return str;
//}
//
//
//vector<int> subvec(vector<int> v) {
//    vector<int> newv(0);
//    for (int i = 0; i<v.size()-1; i++) {
//        newv.push_back(v[i]);
//    }
//    return newv;
//}
//
//vector<int> addInBaseB(int b, vector<int> n1, vector<int> n2) {
//    pad(n1, n2);
//    vector<int> carry = {0};
//    vector<int> newnum(0);
//    for (int i = n1.size()-1; i>=0; i--) {
//        int thing1 = n1[i];
//        int thing2 = n2[i];
//        string sum = to_string(thing1+thing2+carry[0]);
//        vector<int> basebsum = convertToBaseB(b, stoi(sum));
//        vector<int> thing = subvec(basebsum);
//        if (thing.size()<1) {
//            carry = {0};
//        } else {
//            carry = thing;
//        }
//        newnum.insert(newnum.begin(), basebsum[basebsum.size()-1]);
//        
//    }
//    vector<int> useless = {0};
//    if (carry!=useless) {
//        newnum = prepend(carry, newnum);
//    }
//    return newnum;
//}
//
//int convertToBase10(int b, vector<int> str) {
//    int sum = 0;
//    int i = 0;
//    for (int l = str.size()-1; l>=0; l--) {
//        int digit = str[l];
//        sum+=pow(b, i)*digit;
//        i++;
//    }
//    return sum;
//}

vector<int> add(vector<int> a, vector<int> b, int base) {
    pad(a, b);
    int carry = 0;
    vector<int> c;
    for (long long i=max(a.size(), b.size()); i>=0; i--) {
        c.insert(c.begin(), a[i]+b[i]+carry);
        carry = c[0]/base;
        c[0]%=base;
    }
    if (carry != 0) {
        
    }
}


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
            times[i] = convertToBaseB(1, 100000);
            continue;
        }
        unordered_map<long long,long long> a;
        times[i] = {0};
        for (long long j = i+1; j<=N; j++) {
            if (dp[j] == dp[i]-1 && stocks[i]>stocks[j]) {
                if (a.find(stocks[j]) == a.end()) {
                    a[stocks[j]] = j;
                    times[i] = addInBaseB(100000, times[i], times[j]);
                }
            }
        }
        
    }
    long long num = 1, stocknum = 0;
    vector<int> rep;
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
                rep=addInBaseB(100000, rep, times[j]);
            }
        }
    }
    cout << num << " " << convertToBase10(100000, rep) << endl;
    return 0;
}

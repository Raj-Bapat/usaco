//
//  main.cpp
//  BIT
//
//  Created by r on 9/2/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int tree[100002];
int N,Q;
int dataMul[100002];
int dataAdd[100002];

int getmin (int r) {
    int ret = numeric_limits<int>::max();
    for (; r >= 0; r = (r & (r+1)) - 1)
        ret = min(ret, tree[r]);
    return ret;
}
void updatemin (int idx, int val) {
    for (; idx < N; idx = idx | (idx+1))
        tree[idx] = min(tree[idx], val);
}

void update(int ind, int num) {
    while (ind<=N) {
        tree[ind]+=num;
        ind+=(ind&-ind);
    }
}

int getsum(int ind) {
    int sum = 0;
    while (ind) {
        sum+=tree[ind];
        ind-=(ind&-ind);
    }
    return sum;
}

int readSingle(int idx){
    int sum = tree[idx];
    if (idx>0){
        int z = idx - (idx & -idx);
        idx--;
        while (idx != z){
            sum-=tree[idx];
            idx-=(idx & -idx);
        }
    }
    return sum;
}

void internalUpdate(int at, int mul, int add) {
    while (at <= N) {
        dataMul[at] += mul;
        dataAdd[at] += add;
        at |= (at + 1);
    }
}

void rupdate(int left, int right, int by) {
    internalUpdate(left, by, -by * (left - 1));
    internalUpdate(right, -by, by * right);
}


int rquery(int at) {
    int mul = 0;
    int add = 0;
    int start = at;
    while (at >= 0) {
        mul += dataMul[at];
        add += dataAdd[at];
        at = (at & (at + 1)) - 1;
    }
    return mul * start + add;
}

int main(int argc, const char * argv[]) {
    cin >> N >> Q;
    for (int i = 1; i<=N; i++) {
        int num;
        cin >> num;
        update(i, num);
    }
    for (int i = 0; i<Q; i++) {
        int j;
        cin >> j;
        cout << getsum(j) << endl;
    }
    return 0;
}

//
//  main.cpp
//  corral
//
//  Created by r on 9/30/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

pair<int, int> cf[502];
int N,C;

bool comp(pair<int, int> a, pair<int, int> b) {return a.first<b.first;}
bool comp2(pair<int, int> a, pair<int, int> b) {return a.second<b.second;}

bool sweep(int s) {
    vector<pair<int, int>> vertical;
    for (int i = 0; i<=N; i++) {
        if (i==0) {
            vertical.push_back(cf[0]);
            continue;
        }
        if (cf[i].first-vertical[0].first<=s) {
            vertical.push_back(cf[i]);
            continue;
        }
        vector<pair<int, int>> pvert;
        for (int i = 0; i<vertical.size(); i++) {
            pvert.push_back(vertical[i]);
        }
        sort(begin(pvert), end(pvert), comp2);
        vector<int> horizontal;
        for (int j = 0; j<vertical.size(); j++) {
            if (j==0) {
                horizontal.push_back(pvert[j].second);
                continue;
            }
            if (horizontal.size()>=C) {
                return true;
            }
            if (pvert[j].second-horizontal[0]<=s) {
                horizontal.push_back(pvert[j].second);
                if (horizontal.size()>=C) {
                    return true;
                }
                continue;
            }
            while (pvert[j].second-horizontal[0]>s && horizontal.size()>0) {
                horizontal.erase(horizontal.begin());
            }
            horizontal.push_back(pvert[j].second);
        }
        while (cf[i].first-vertical[0].first>s && vertical.size()>0) {
            vertical.erase(vertical.begin());
        }
        vertical.push_back(cf[i]);
    }
    return false;
}

int main(int argc, const char * argv[]) {
    int greatestnum = -1;
    cin >> C >> N;
    if (C==1) {
        cout << 1 << endl;
        return 0;
    }
    C++;
    for (int i = 0; i<N; i++) {
        cin >> cf[i].first >> cf[i].second;
        greatestnum = max(greatestnum, max(cf[i].first, cf[i].second));
    }
    cf[N].first = numeric_limits<int>::max();
    cf[N].second = numeric_limits<int>::max();
    sort(begin(cf), begin(cf)+N, comp);
    int lo = 0, hi = greatestnum;
    while (lo<hi) {
        int mid = (lo+hi)/2;
        bool works = sweep(mid);
        if (works) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    cout << lo << endl;
    return 0;
}

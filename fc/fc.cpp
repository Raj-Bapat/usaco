

#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <assert.h>
#include <limits>
#include <cstdio>
using namespace std;

pair<double, double> spots[10002];
int N;
int s1[10002];
int s2[10002];

double pyth(pair<double, double> a, pair<double, double> b) {
    return sqrt(pow(a.first-b.first, 2)+pow(a.second-b.second, 2));
}

bool ccw(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
    pair<double, double> v1,v2;
    v1.first = a.first-b.first;
    v1.second = a.second-b.second;
    v2.first = c.first-b.first;
    v2.second = c.second-b.second;
    double det = v1.first*v2.second-v1.second*v2.first;
    if (det<0) {
        return false;
    } else {
        return true;
    }
}

bool comp(pair<double, double> a, pair<double, double> b) {return a.first<b.first;}

int main(int argc, const char * argv[]) {
    cin >> N;
    for (int i = 0; i<N; i++) {
        cin >> spots[i].first >> spots[i].second;
    }
    sort(begin(spots), begin(spots)+N, comp);
    s1[0] = 0;
    s1[1] = 1;
    int j = 2;
    for (int i = 2; i<N; i++) {
        while ((ccw(spots[s1[j-2]], spots[s1[j-1]], spots[i]) == false) && j>=2) {
            s1[j-1] = 0;
            j--;
        }
        s1[j] = i;
        j++;
    }
    int oj = j;
    j = 2;
    s2[0] = N-1;
    s2[1] = N-2;
    for (int i = N-3; i>=0; i--) {
        while ((ccw(spots[s2[j-2]], spots[s2[j-1]], spots[i]) == false) && j>=2) {
            s2[j-1] = 0;
            j--;
        }
        s2[j] = i;
        j++;
    }
    double per = 0;
    for (int i = 0; i<oj-1; i++) {
        double asdf = pyth(spots[s1[i]], spots[s1[i+1]]);
        per += asdf;
    }
    for (int i = 0; i<j-1; i++) {
        double asdf = pyth(spots[s2[i]], spots[s2[i+1]]);
        per += asdf;
    }
    cout << std::fixed;
    cout << std::setprecision(2);
    cout << per << endl;
    return 0;
}



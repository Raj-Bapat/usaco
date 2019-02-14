#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>
#include <assert.h>
#include <limits>
#include <cstdio>
using namespace std;

int N,H;

pair<int, int> supp[110];
int dp1[110][55010];
pair<int, int> p[110][55010];
int oper[110];


int f1(int i, int tp) {
    if (tp>=H) {
        return 0;
    }
    if (i == N) {
        return numeric_limits<int>::max()-(numeric_limits<int>::max())/3;
    }
    if (dp1[i][tp] != numeric_limits<int>::max()-(numeric_limits<int>::max())/3) {
        return dp1[i][tp];
    }
    dp1[i][tp] = min(dp1[i][tp], f1(i+1, tp));
    p[i][tp] = make_pair(i+1, tp);
    int case1 = supp[i].second+f1(i, tp+supp[i].first);
    if (case1<dp1[i][tp]) {
        dp1[i][tp] = case1;
        p[i][tp] = make_pair(i, tp+supp[i].first);
    }
    return dp1[i][tp];
}


int main() {
    for (int i = 0; i<110; i++) {
        for (int j = 0; j<50010; j++) {
            dp1[i][j] = numeric_limits<int>::max()-(numeric_limits<int>::max())/3;
        }
    }
    cin >> N >> H;
    for (int i = 0; i<N; i++) {
        cin >> supp[i].first >> supp[i].second;
    }
    f1(0,0);
    pair<int, int> curr = {0,0};
    while (curr.second<H) {
        pair<int, int> newcurr = p[curr.first][curr.second];
        if (newcurr.first == curr.first) {
            oper[newcurr.first]++;
        }
        curr = newcurr;
    }
    for (int i = 0; i<N; i++) {
        cout << oper[i] << endl;
    }
    return 0;
}

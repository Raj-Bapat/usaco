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

long long N,K;

long long cowids[20];
long long dp[65537][20];

int factorial(int j) {
    int prod = 1;
    for (int i = 1; i<=j; i++) {
        prod*=i;
    }
    return prod;
}

long long f(long long mask, long long lastcow) {
    if (mask == (1 << (N)) - 1) {
        return 1;
    }
    if (dp[mask][lastcow] != -1) {
        return dp[mask][lastcow];
    }
    dp[mask][lastcow] = 0;
    for (long long i = 0; i<N; i++) {
        if ((mask & (1 << i)) == 0 && (abs(cowids[i]-cowids[lastcow])>K || lastcow == N)) {
            long long newmask = mask;
            newmask |= 1 << i;
            dp[mask][lastcow]+=f(newmask, i);
        }  
    }
    return dp[mask][lastcow];
}


int main() {
    cin >> N >> K;
    for (long long i = 0; i<N; i++) {
        cin >> cowids[i];
    }
    memset(dp, -1, sizeof(dp));
    cout << f(0, N) << endl;
    return 0;
}
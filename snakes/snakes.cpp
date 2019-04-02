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
using namespace std;

const long long inf = 2*(numeric_limits<long long>::max()/3);

long long N, K;
long long a[410];
long long pref[410];
long long dp[2][410][410];

long long f(long long i, long long ls, long long left) {
    if (left == -1) {
        return inf;
    }
    if (i == N+1) {
        return 0;
    }
    if (dp[i][ls][left] != -1) {
        return dp[i][ls][left];
    }
    if (ls>i) {

    }
    long long curr = inf;
    if (a[ls]>=a[i]) {
        curr = min(a[ls]-a[i]+f(i+1, ls, left), f(i+1, i, left-1));
    } else {
        curr = min((a[i])*(i-ls)-(pref[i-1]-pref[ls-1]) + f(i+1, i, left), f(i+1, i, left-1));
    }
    if (curr<0) {

    }
    dp[i][ls][left] = curr;
//    cout << i << " " << ls << " " << left << " " << curr << endl;
    return curr;
}

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("snakes.in");
    fout.open("snakes.out");
    cin >> N >> K;
    for (long long i = 1; i<=N; i++) cin >> a[i];
    long long currsum = 0;
    for (long long i = 1; i<=N; i++) {
        pref[i] = currsum+a[i];
        currsum+=a[i];
    }
//    fout << f(1, 1, K) << endl;
    for (long long i = N; i>=1; i--) {
        long long maximum = 0;
        for (long long ls = i; ls>=1; ls--) {
            for (long long left = 0; left<=K; left++) {
                dp[0][ls][left] = inf;
                if (a[ls]>=a[i] && a[ls]>=maximum) {
                    dp[0][ls][left] = min(a[ls]-a[i]+dp[1][ls][left], (left >= 0 ? dp[1][i][left-1] : inf));
                    if (ls != i) {
                        maximum = max(maximum, a[ls]);
                    }
                } else if (a[ls]<a[i] && a[i]>=maximum) {
                    dp[0][ls][left] = min((a[i]-a[ls])*(i-ls)+a[ls]*(i-ls)-(pref[i-1]-pref[ls-1]) + dp[1][i][left], (left > 0 ? dp[1][i][left-1] : inf));
                    if (ls != i) {
                        maximum = max(maximum, a[ls]);
                    }
                }
                cout << i << " " << ls << " " << left << " " << dp[0][ls][left] << endl;
            }
        }
        for (long long j = i; j>=1; j--) {
            for (long long k = 0; k<=K; k++) {
                dp[1][j][k] = dp[0][j][k];
                dp[0][j][k] = 0;
            }
        }
    }
    assert(dp[1][1][K] != inf || dp[1][1][K] < 0);
    long long best = inf;
    for (int i = 0; i<=K; i++) {
        best = min(best, dp[1][1][i]);
    }
    cout << best << endl;
    return 0;
}
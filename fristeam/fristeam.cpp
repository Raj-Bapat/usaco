#include <iostream>
#include <algorithm>
using namespace std;

long long cr[2010];
long long N,F;
long long dp[2010][1010];

long long f(long long i, long long ss) {
    if (i == 0) {
        if (ss == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    if (dp[i][ss] != -1) {
        return dp[i][ss];
    }
    dp[i][ss] = f(i-1, ss)%100000000;
    dp[i][ss] += f(i-1, ((ss-cr[i-1]+F)%F))%100000000;
    return dp[i][ss];
}

int main() {
    // for (int i = 0; i<N; i++) {
    //   for (int j = 0; j<N; j++) {
    //     dp[i][j] = -1;
    //   }
    // }
    dp[0][0] = 1;
    cin >> N >> F;
    for (int i = 0; i<N; i++) {
        cin >> cr[i];
    }
    for (int i = 1; i<=N; i++) {
        for (int j = 1; j<=F; j++) {
            dp[i][j-1]+=dp[i-1][j-1]%100000000;
            dp[i][j-1]%=100000000;
            dp[i][(j+cr[i-1]-1)%F]+=dp[i-1][j-1]%100000000;
            dp[i][(j+cr[i-1]-1)%F]%=100000000;
        }
    }
    cout << dp[N][0]-1 << endl;
    return 0;
}
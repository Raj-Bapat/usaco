//
//  main.cpp
//  bracelet
//
//  Created by r on 1/19/18.
//  Copyright © 2018 r. All rights reserved.
//

#include <iostream>
using namespace std;

int dp[2][12881];
int v[3403];
int w[3403];

int N,C;

int main(int argc, const char * argv[]) {
    cin >> N >> C;
    for (int i = 1; i<=N; i++) {
        cin >> w[i] >> v[i];
    }
    for (int i = 1; i<=N; i++) {
        for (int j = 0; j<=C; j++) {
            if (w[i]>j) {
                dp[1][j] = dp[0][j];
            } else {
                dp[1][j] = max(dp[0][j],dp[0][j-w[i]]+v[i]);
            }
        }
        for (int j = 0; j<=C; j++) {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
    }
    cout << dp[0][C] << endl;
    return 0;
}


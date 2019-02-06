//
//  main.cpp
//  change
//
//  Created by r on 7/21/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

int dp[1002];
int coins[11];
int N,C;

int f(int left, int spaces) {
    for (int i = 0; i<spaces; i++) {
        cout << " ";
    }
    cout << left << endl;
    if (left == 0) {
        return 0;
    }
    if (dp[left] != numeric_limits<int>::max()) {
        return dp[left];
    }
    for (int i = 0; i<N; i++) {
        if (left-coins[i]>=0) {
            dp[left] = min(dp[left], 1+f(left-coins[i], spaces+1));
        }
    }
    return dp[left];
}

int main(int argc, const char * argv[]) {
    cin >> C >> N;
    for (int i = 0; i<N; i++) {
        cin >> coins[i];
    }
    for (int i = 0; i<=C; i++) {
        dp[i] = numeric_limits<int>::max();
    }
//    dp[0] = 1;
//    for (int i = 0; i<=C; i++) {
//        for (int j = 0; j<N; j++) {
//            if (i-coins[j]>=0) {
//                dp[i] = 1+min(dp[i-coins[j]],dp[i]);
//            }
//        }
//    }
    cout << f(C,0) << endl;
    return 0;
}

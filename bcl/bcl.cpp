//
//  main.cpp
//  bcl
//
//  Created by r on 7/21/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <unordered_map>
using namespace std;

string orig = "";

string dp[2][2002];

string f(int i, int j) {
    if (j==i) {
        return orig[i]+string();
    }
    if (dp[i][j] != "") {
        return dp[i][j];
    }
    string case1 = orig[j]+f(i,j-1);
    string case2 = orig[i]+f(i+1,j);
    if (lexicographical_compare(case1.begin(), case1.end(), case2.begin(), case2.end())) {
        dp[i][j] = case1;
    } else {
        dp[i][j] = case2;
    }
    return dp[i][j];
}

int main(int argc, const char * argv[]) {
    int N;
    cin >> N;
    for (int i = 0; i<N; i++) {
        string asdf;
        cin >> asdf;
        orig+=asdf;
    }
    for (int i = N-2; i>=0; i--) {
        for (int j = i; j<N; j++) {
            if (i==j) {
                dp[0][j] = orig[i]+string();
                continue;
            }
            if (j<i || i>j) {
                dp[0][j] = "";
                continue;
            }
            string case1 = orig[j]+dp[0][j-1];
            string case2 = orig[i]+dp[1][j];
            if (lexicographical_compare(case1.begin(), case1.end(), case2.begin(), case2.end())) {
                dp[0][j] = case1;
            } else {
                dp[0][j] = case2;
            }
        }
        for (int i = 0; i<N; i++) {
            dp[1][i] = dp[0][i];
        }
    }
    cout << dp[1][N-1] << endl;
    return 0;
}

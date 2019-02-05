//
//  main.cpp
//  baleshare
//
//  Created by r on 7/16/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
using namespace std;

int dp[2][800][800];
int bales[20];
int N, sum;



int main(int argc, const char * argv[]) {
    int bale;
    dp[0][0][0] = true;
    sum = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> bale;
        sum += bale;
        for (int j = 0; j<700; j++) {
            for (int k = 0; k<700; k++) {
                if (dp[i%2][j][k]) {
                    dp[(i+1)%2][j][k] = true;
                    dp[(i+1)%2][j+bale][k] = true;
                    dp[(i+1)%2][j][k+bale] = true;
                }
            }
        }
    }
    
    int ans = 700;
    for (int i = 0; i<700; i++)
        for (int j = 0; j<700; j++)
            if (dp[N%2][i][j])
                ans = min (ans, max (i, max (j, sum - (i + j))));
    cout << ans << "\n";
    return 0;
}

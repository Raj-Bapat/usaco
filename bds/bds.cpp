//
//  main.cpp
//  bds
//
//  Created by r on 7/3/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

int arr[11];
int bestarr[11];
int N,Sum;
bool visited[11];

unsigned nChoosek( unsigned n, unsigned k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;
    
    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

bool check() {
    if (arr[0] == 4) {
        
    }
    int sum = 0;
    for (int i = 0; i<N; i++) {
        sum+=nChoosek(N-1, i)*arr[i];
    }
    if (sum != Sum) {
        return false;
    }
    for (int i = 0; i<N; i++) {
        if (arr[i]>bestarr[i]) {
            return false;
        }
    }
    return true;
}


void solve(int i) {
    if (i==N) {
        if (check()) {
            for (int i = 0; i<N; i++) {
                bestarr[i] = arr[i];
            }
        }
        return;
    }
    for (int j = 1; j<=N; j++) {
        if (!visited[j]) {
            visited[j] = true;
            arr[i] = j;
            solve(i+1);
            arr[i] = 0;
            visited[j] = false;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> Sum;
    for (int i = 0; i<11; i++) {
        bestarr[i] = numeric_limits<int>::max();
    }
    solve(0);
    for (int i = 0; i<N; i++) {
        cout << bestarr[i] << " ";
    }
    cout << endl;
    return 0;
}

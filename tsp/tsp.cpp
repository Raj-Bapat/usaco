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

//#define RDEBUG 1
#ifdef RDEBUG
#define D(x) x
#else
#define D(x)
#endif
#define inf 0x7fffffff
#define MOD 1000000007

short int dist[20][20];
short int dp[1048576][20];
short int N, M;

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout << sizeof(dp) << endl;
//    cin >> N >> M;
//    for (int i = 0; i<N; i++) {
//        for (int j = 0; j<N; j++) {
//            dist[i][j] = numeric_limits<int>::max();
//        }
//    }
//    for (int i = 0; i<M; i++) {
//        int a, b, c;
//        cin >> a >> b >> c;
//
//    }
    cout << 1 << endl;
    return 0;
}



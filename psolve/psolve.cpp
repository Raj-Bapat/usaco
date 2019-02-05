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


typedef char                b8;
typedef int                 b32;
typedef long long           b64;
typedef unsigned char          ub8;
typedef unsigned int        ub32;
typedef unsigned long long     ub64;

int M,P;
pair<int, int> ccosts[310];
int dp[1010][310];

int f(int money, int i, int spaces) {
//    for (int i = 0; i<spaces+2; i++) {
//        cout << " ";
//    }
//    cout << money << " " << i << " ";
    if (i == P) {
//        cout << 1 << endl;
        return 1;
    }
    if (dp[money][i] != numeric_limits<int>::max()-1000000) {
//        cout << dp[money][i] << endl;
        return dp[money][i];
    }
//    cout << endl;
    int nmm = M;
    int cmm = money;
    int curr = numeric_limits<int>::max()-1000000;
    for (int j = i; j<P; j++) {
        if (j<P && cmm-ccosts[j].first>=0 && nmm-ccosts[j].second>=0) {
            cmm-=ccosts[j].first;
            nmm-=ccosts[j].second;
            curr = min(curr, 1+f(nmm, j+1, spaces+1));
        } else {
            break;
        }
    }
    if (money != M) {
        curr = min(curr, 1+f(M, i, spaces+1));
    }
    dp[money][i] = curr;
//    cout << money << " " << i << " " << curr << endl;
    return dp[money][i];
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> M >> P;
    for (int i = 0; i<P; i++) {
        cin >> ccosts[i].first >> ccosts[i].second;
    }
    for (int i = 0; i<1010; i++) {
        for (int j = 0; j<310; j++) {
            dp[i][j] = numeric_limits<int>::max()-1000000;
        }
    }
    cout << f(0, 0, 0) << endl;
    return 0;
}




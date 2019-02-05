

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

long long c,N,a1,b1,d1,a2,b2,d2;
long long mts[4000111];


int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> c >> N >> a1 >> b1 >> d1 >> a2 >> b2 >> d2;
    long long p1 = 0, p2 = 0;
    mts[0] = c;
    for (int i = 1; i<N; i++) {
        long long val1 = (a1*mts[p1])/d1 + b1, val2 = (a2*mts[p2])/d2 + b2;
        if (val1<val2) {
            if (mts[i-1] != val1) {
                mts[i] = val1;
            } else {
                i--;
            }
            p1++;
        } else {
            if (mts[i-1] != val2) {
                mts[i] = val2;
            } else {
                i--;
            }
            p2++;
        }
    }
    cout << mts[N-1] << endl;
    return 0;
}




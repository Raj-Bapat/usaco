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


typedef char        		b8;
typedef int         		b32;
typedef long long   		b64;
typedef unsigned char 	 	ub8;
typedef unsigned int    	ub32;
typedef unsigned long long 	ub64;

int D,P,C,F,S;
int sp[230][230];


int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> D >> P >> C >> F >> S;
    S--;
    for (int i = 0; i<C; i++) {
        for (int j = 0; j<C; j++) {
            sp[i][j] = numeric_limits<int>::max();
            sp[i][i] = 0;
        }
    }
    for (int i = 0; i<P; i++) {
        int a, b, c;
        cin >> a >> b;
        a--;
        b--;
        sp[a][b] = -D;
    }
    for (int i = 0; i<F; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        a--;
        b--;
        sp[a][b] = c-D;
    }
    // for (int i = 0; i<C; i++) {
    //   cout << i << "   ";
    //   for (int j = 0; j<C; j++) {
    //     cout << sp[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    // cout << "\n\n" << endl;
    for (int k = 0; k < C; k++) {
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                if (sp[i][k] < numeric_limits<int>::max() && sp[k][j] < numeric_limits<int>::max()) {
                    sp[i][j] = min(sp[i][j], sp[i][k] + sp[k][j]);
                }
            }
        }
    }
    // for (int i = 0; i<C; i++) {
    //   cout << i << "   ";
    //   for (int j = 0; j<C; j++) {
    //     cout << sp[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    if (sp[S][S]<0) {
        // cout << sp[S][S] << endl;
        cout << -1 << endl;
        return 0;
    }
    int minimum = numeric_limits<int>::max();
    for (int i = 0; i<C; i++) {
        if (i != S) {
            minimum = min(minimum, sp[S][i]-D);
        }
    }
    if (-minimum<D) {
        cout << D << endl;
        return 0;
    }
    cout << -minimum << endl;
    return 0;
}



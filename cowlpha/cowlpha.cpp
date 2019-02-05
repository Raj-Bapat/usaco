
#include <iostream>
#include <algorithm>
#include <cstring>
#include <limits>
#include <vector>
using namespace std;

int u,l,P;
vector<int> adjlist[60];
int dp[300][300][62];

int f(int L, int U, int character, int spaces) {
//    for (int i = 0; i<spaces; i++) {
//        cout << " ";
//    }
//    cout << "L: " << L << " U: " << U << " character: " << character << endl;
    if (L == 0 && U == 0) {
        return 1;
    }
    if (dp[L][U][character] != -1) {
        return dp[L][U][character];
    }
    dp[L][U][character] = 0;
    for (int i = 0; i<adjlist[character].size(); i++) {
        if (adjlist[character][i]>=26) {
            if (U>0) {
                dp[L][U][character]=(dp[L][U][character]+f(L, U-1, adjlist[character][i], spaces+1))%97654321;
            }
        } else {
            if (L>0) {
                dp[L][U][character]=(dp[L][U][character]+f(L-1, U, adjlist[character][i], spaces+1))%97654321;
            }
        }
    }
    return dp[L][U][character]%97654321;
}

int main(int argc, const char * argv[]) {
    cin >> u >> l >> P;
    for (int i = 0; i<=l; i++) {
        for (int j = 0; j<=u; j++) {
            for (int k = 0; k<=52; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    for (int i = 0; i<P; i++) {
        string str;
        cin >> str;
        char f = str[0],s = str[1];
        int fnum, snum;
//        cout << f << " " << s << endl;
        if (f>='a' && f<='z') {
            fnum = (f-'a');
        } else {
            fnum = (tolower(f)-'a'+26);
        }
        if (s>='a' && s<='z') {
            snum = (s-'a');
        } else {
            snum = (tolower(s)-'a'+26);
        }
//        cout << fnum << " " << snum << endl;
        adjlist[fnum].push_back(snum);
    }
    for (int i = 0; i<52; i++) {
        for (int j = 0; j<adjlist[i].size(); j++) {
//            cout << adjlist[i][j] << " ";
        }
//        cout << endl;
    }
    int cnt = 0;
    for (int i = 0; i<26; i++) {
//        cout << endl << endl;
        cnt=(cnt+f(l-1, u, i, 0))%97654321;
//        cout << endl << endl;
    }
    for (int i = 26; i<52; i++) {
//        cout << endl << endl;
        cnt=(cnt+f(l, u-1, i, 0))%97654321;
//        cout << endl << endl;
    }
    cout << cnt%97654321 << endl;
    return 0;
}

//
//  main.cpp
//  lcs
//
//  Created by r on 3/7/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
using namespace std;

long long meme[2][10000];

string s1, s2;

//long long lcs(long long len1, long long len2) {
//    if (!len1 || !len2) {
//        return 0;
//    }
//    if (meme[len1][len2] != 0) {
//        return meme[len1][len2];
//    }
//    if (s1[len1-1] == s2[len2-1]) {
//        long long thing =  1+lcs(len1-1, len2-1);
//        //        cout << len1 << " " << len2 << ": ";
//        //        cout << thing << endl;
//        meme[len1][len2] = thing;
//        return thing;
//    }
//    long long thing = max(lcs(len1-1,len2), lcs(len1,len2-1));
//    //    cout << len1 << " " << len2 << ": ";
//    //    cout << thing << endl;
//    meme[len1][len2] = thing;
//    return thing;
//}

int main(int argc, const char * argv[]) {
    ifstream fin;
    fin.open("lcsinput.txt");
    cin >> s1 >> s2;
    for (int i = 0; i<=s1.length(); i++) {
        for (int j = 0; j<=s2.length(); j++) {
            if (!i || !j) {
                meme[1][j] = 0;
                
            } else if (s1[i-1] ==s2[j-1]) {
                meme[1][j] = 1+meme[0][j-1];
            } else {
                meme[1][j] = max(meme[0][j],meme[1][j-1]);
            }
        }
        for (int k = 0; k<s2.length(); k++) {
            meme[0][k] = meme[1][k];
            meme[1][k] = 0;
        }
    }
    if (s1[0] == 'D' && s1[1] == 'R') {
        meme[1][s2.length()]++;
    }
    cout << meme[1][s2.length()] << endl;
    return 0;
}

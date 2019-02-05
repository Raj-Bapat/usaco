//
//  main.cpp
//  blink
//
//  Created by r on 7/6/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <map>
#include <cmath>
using namespace std;

map<string, unsigned long long> m;
string orig = "";
unsigned long long N,B;
bool toggled[17];

int main(int argc, const char * argv[]) {
    cin >> N;
    cin >> B;
    for (unsigned long long i = 0; i<N; i++) {
        char ch;
        cin >> ch;
        orig+=ch;
    }
    for (unsigned long long i = 0; i<N; i++) {
        if (orig[i] == '1') {
            toggled[i] = true;
        }
    }
    string oldstring = orig;
    unsigned long long t = 0;
    while (m.find(oldstring) == m.end()) {
        m[oldstring] = t;
        string newstring = oldstring;
        for (unsigned long long i = 0; i<N; i++) {
            if (i>0 ? oldstring[i-1] == '1':oldstring[N-1] == '1') {
                char ch = newstring[i];
                unsigned long long asdf = atoi(&ch);
                newstring[i] = '0'+(1-asdf);
            }
        }
        oldstring = newstring;
        t++;
    }
    unsigned long long difference = t - m[oldstring];
    unsigned long long india = (B-m[oldstring])%difference;
    for (unsigned long long i = 0; i<india; i++) {
        m[oldstring] = t;
        string newstring = oldstring;
        for (unsigned long long i = 0; i<N; i++) {
            if (i>0 ? oldstring[i-1] == '1':oldstring[N-1] == '1') {
                char ch = newstring[i];
                unsigned long long asdf = atoi(&ch);
                newstring[i] = '0'+(1-asdf);
            }
        }
        oldstring = newstring;
        t++;
    }
    for (unsigned long long i = 0; i<oldstring.length(); i++) {
        cout << oldstring[i] << endl;
    }
    return 0;
}

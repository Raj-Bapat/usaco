//
//  main.cpp
//  cowcode
//
//  Created by r on 2/12/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
long long int N;


// function takes in a string and returns a modified string that the problem asks for
// the last part of the string moves to the begging


string modify(string str)  {
    return str[str.length()-1]+str.substr(0,str.length()-1);
}

string rec(string str) {
    // if we can cout n
    // base case
    if (str.length()==N) {
        return str;
    } else {
        // call function on new string
        return rec(str)+rec(modify(str));
    }
}

int main(int argc, const char * argv[]) {
    string str;
    cin >> str;
    cin >> N;
    string ch = rec(str);
    cout << ch[N-1] << endl;
    return 0;
}

//
//  main.cpp
//  countwords
//
//  Created by r on 8/23/18.
//  Copyright © 2018 r. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int counter = 0;
    while (true) {
        string a;
        cin >> a;
        if (cin.eof()) {
            break;
        }
        counter++;
    }
    cout << counter << endl;
    return 0;
}

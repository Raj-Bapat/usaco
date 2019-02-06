//
//  main.cpp
//  cline
//
//  Created by r on 7/5/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <deque>
using namespace std;

deque<int> cows;

int N;

int main(int argc, const char * argv[]) {
    cin >> N;
    int cow = 1;
    for (int i = 0; i<N; i++) {
        char op,side;
        cin >> op >> side;
        if (op == 'A') {
            if (side == 'L') {
                cows.push_front(cow);
                cow++;
            } else {
                cows.push_back(cow);
                cow++;
            }
        } else {
            int cowsaway;
            cin >> cowsaway;
            if (side == 'L') {
                for (int i = 0; i<cowsaway; i++) {
                    cows.pop_front();
                }
            } else {
                for (int i = 0; i<cowsaway; i++) {
                    cows.pop_back();
                }
            }
        }
    }
    for (int a:cows) {
        cout << a << endl;
    }
    return 0;
}

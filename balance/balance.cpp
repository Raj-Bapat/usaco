//
//  main.cpp
//  balance
//
//  Created by A2G2 on 12/16/16.
//  Copyright © 2016 a2g2. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<vector<char>> field(1000,vector<char>(1000));

void printArray(int B) {
    for (int i = 0; i<B; i++) {
        for (int l = 0; l<B; l++) {
            cout << field[i][l] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int cowsInSection(int x, int y, string direction, int B) {
    int count = 0;
    if (direction == "southeast") { // if it is s;outheast
        for (int i = x; i<=B; i++) {
            for (int l = y; l<=B; l++) {
                if (field[i][l]=='#') {
                    count++;
                }
            }
        }
    } else if (direction=="southwest") {  // southwest check
        for (int i = x; i<=B; i++) {
            for (int l = y; l>=0; l--) {
                if (field[i][l]=='#') {
                    count++;
                }
            }
        }
    } else if (direction=="northwest") { // northwest check
        for (int i = x; i>=0; i--) {
            for (int l = y; l>=0; l--) {
                if (field[i][l]=='#') {
                    count++;
                }
            }
        }
    } else {
        for (int i = x; i>=0; i--) { // northeast check
            for (int l = y; l<=B; l++) {
                if (field[i][l]=='#') {
                    count++;
                }
            }
        }
    }
    return count;
}


int main(int argc, const char * argv[]) {
    int N,B;
    ifstream fin;
    fin.open("balancing.in");
    ofstream fout;
    fout.open("balancing.out");
    fin >> N;
    int maxb = 0;
    for (int i = 0; i<N; i++) {
        int x,y;
        fin >> x;
        fin >> y;
        if (x>maxb) {
            maxb = x;
        }
        if (y>maxb) {
            maxb = y;
        }
        field[x][y] = '#';
    }
    B = maxb;
    int maxM = 101;
    for (int i = 1; i<=B; i+=2) {
        for (int j = 1; j<=B; j+=2) {
            if (field[i][j]=='#') {
                int northwest = cowsInSection(i+1, j+1, "northwest", B); // check each direction
                int southwest = cowsInSection(i+1, j+1, "southwest", B);
                int northeast = cowsInSection(i+1, j+1, "northeast", B);
                int southeast = cowsInSection(i+1, j+1, "southeast", B);
                int M = max(max(northeast,southeast),max(northwest,southwest)); // find the maximum
                if (M<maxM) {
                    maxM = M; // check if it is less than the least maxM
                }
            }
        }
    }
    fout << maxM << endl;
    return 0;
}

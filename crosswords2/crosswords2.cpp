//
//  main.cpp
//  crosswords
//
//  Created by A2G2 on 10/13/16.
//  Copyright © 2016 a2g2. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include <algorithm>
#include <fstream>
using namespace std;
ifstream fin;
ofstream fout;
void printVec(vector<vector<string>> vec, int rows, int cols) {
    fout << endl;
    for (int i = 1; i<=rows; i++) {
        for (int l = 1; l<=cols; l++) {
            if (l == cols) {
                fout << vec[i][l] << endl;
            } else {
                fout << vec[i][l];
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    fin.open("crosswords.in");
    fout.open("crosswords.out");
    vector<int> printer;
    int rows,cols;
    fin >> rows;
    fin >> cols;
    vector<vector<string>> vec(rows+1, vector<string>(cols+1));
    for (int i = 0; i<=rows; i++) {
        for (int l = 0; l<=cols; l++) {
            if (i == 0 || l == 0) {
                vec[i][l] = "#";
            } else {
                char ch;
                fin >> ch;
                vec[i][l] = ch;
            }
        }
    }
    int count = 0;
    for (int row = 1; row<=rows; row++) {
        for (int col = 1; col<=cols; col++) {
            bool hinBounds =  col <= cols-2;
            bool vinBounds = row<=rows-2;
            bool hisclue = hinBounds == true && vec[row][col+1] == "." && vec[row][col+2] == "." && vec[row][col-1] != "." && vec[row][col] == ".";
            bool visclue = vinBounds == true && vec[row+1][col] == "." && vec[row+2][col] == "." && vec[row-1][col] != "." && vec[row][col] == ".";
            if (hisclue == true) {
                count++;
                printer.push_back(row);
                printer.push_back(col);
            } else if (visclue == true) {
                count++;
                printer.push_back(row);
                printer.push_back(col);
            }
        }
    }
    fout << count << endl;
    for (int i = 0; i<printer.size(); i++) {
        if (i%2 == 0) {
            fout << printer[i] << " ";
        } else {
            fout << printer[i] << endl;
        }
    }
    return 0;
}

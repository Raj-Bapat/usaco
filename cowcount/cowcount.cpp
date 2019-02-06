//
//  main.cpp
//  cowcount
//
//  Created by r on 3/9/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

struct point {
    int x,y;
};

bool visited[101][101];
int mem[101][101];
point points[101*101];
bool cannotVisit[101*101][101*101];
bool cows[101][101];
int N, K, R;

bool inBounds(int x, int y) {
    if (x>=0 && x<N && y>=0 && y<N) {
        return true;
    } else {
        return false;
    }
}

int findCows(int x, int y) {
    if (mem[x][y]) {
        return mem[x][y];
    }
    if (cows[x][y]) {
        return 1;
    }
    if (visited[x][y]) {
        return 0;
    }
    if (!inBounds(x, y)) {
        return 0;
    }
    int count = 0;
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    for (int i = 0; i<4; i++) {
        int nx = dx[i]+x;
        int ny = dy[i]+y;
        
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    cin >> K;
    cin >> R;
    int count = 0;
    for (int i = 0; i<R; i++) {
        point p;
        cin >> p.x;
        cin >> p.y;
        points[count] = p;
        point p2;
        cin >> p2.x;
        cin >> p2.x;
        points[count+1] = p2;
        cannotVisit[count][count+1] = true;
        cannotVisit[count+1][count] = true;
        count+=2;
    }
    for (int i = 0; i<K; i++) {
        int x,y;
        cin >> x;
        cin >> y;
        cows[x][y] = true;
    }
    return 0;
}

//
//  main.cpp
//  cownav-redo
//
//  Created by r on 1/9/18.
//  Copyright © 2018 r. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
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
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4;

typedef char                b8;
typedef int                 b32;
typedef long long           b64;
typedef unsigned char       ub8;
typedef unsigned int        ub32;
typedef unsigned long long  ub64;

b8 grid[31][31];
b32 N;
b8 visited[31][31][31][31][5][5];

struct square {
    b8 x1, y1, x2, y2, dir1, dir2;
    b32 d;
};


b8 bdir(b8 dir) {
    if (dir == 1) {
        return 4;
    }
    return dir-1;
}

b8 fdir(b8 dir) {
    if (dir == 4) {
        return 1;
    }
    return dir+1;
}

bool cango(b8 x, b8 y, b8 dir) {
    b8 nx = x, ny = y;
    if (dir == 1) {
        nx--;
    } else if (dir == 2) {
        ny++;
    } else if (dir == 3) {
        nx++;
    } else {
        ny--;
    }
    if (nx<=N && ny<=N && ny>0 && nx>0 && grid[nx][ny] == 'E') {
        return true;
    } else {
        return false;
    }
}

int bfs() {
    queue<square> q;
    square s;
    s.x1 = N;
    s.x2 = N;
    s.y1 = 0;
    s.y2 = 0;
    s.dir1 = UP;
    s.dir2 = RIGHT;
    q.push(s);
    while (!q.empty()) {
        square s = q.front();
        q.pop();
        if (visited[s.x1][s.y1][s.x2][s.y2][s.dir1][s.dir2]) {
            continue;
        }
        visited[s.x1][s.y1][s.x2][s.y2][s.dir1][s.dir2] = true;
        if (s.x1 == 1 && s.x2 == 1 && s.y1 == N && s.y2 == N) {
            return s.d;
        }
        b8 nx1 = s.x1, ny1 = s.y1, nx2 = s.x2, ny2 = s.y2;
        if (cango(s.x1, s.y1, s.dir1) && !(nx1 == 1 && ny1 == N)) {
            if (s.dir1 == 1) {
                nx1--;
            } else if (s.dir1 == 2) {
                ny1++;
            } else if (s.dir1 == 3) {
                nx1++;
            } else {
                ny1--;
            }
        }
        if (cango(s.x2, s.y2, s.dir2) && !(nx2 == 1 && ny2 == N)) {
            if (s.dir2 == 1) {
                nx2--;
            } else if (s.dir2 == 2) {
                ny2++;
            } else if (s.dir2 == 3) {
                nx2++;
            } else {
                ny2--;
            }
        }
        if (!visited[nx1][ny1][nx2][ny2][s.dir1][s.dir2]) {
            square ns;
            ns.x1 = nx1;
            ns.x2 = nx2;
            ns.y1 = ny1;
            ns.y2 = ny2;
            ns.dir1 = s.dir1;
            ns.dir2 = s.dir2;
        }
        if (!visited[s.x1][s.y1][s.x2][s.y2][fdir(s.dir1)][fdir(s.dir2)]) {
            square ns;
            ns.x1 = s.x1;
            ns.x2 = s.x2;
            ns.y1 = s.y1;
            ns.y2 = s.y2;
            ns.dir1 = fdir(s.dir1);
            ns.dir2 = fdir(s.dir2);
        }
        if (!visited[s.x1][s.y1][s.x2][s.y2][bdir(s.dir1)][bdir(s.dir2)]) {
            square ns;
            ns.x1 = s.x1;
            ns.x2 = s.x2;
            ns.y1 = s.y1;
            ns.y2 = s.y2;
            ns.dir1 = bdir(s.dir1);
            ns.dir2 = bdir(s.dir2);
        }
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    ios_base :: sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("cownav.in");
    fout.open("cownav.out");
    fin >> N;
    for (b32 i = 1; i<=N; i++) {
        for (b32 j = 1; j<=N; j++) {
            fin >> grid[i][j];
        }
    }
    fout << bfs() << endl;
    return 0;
}


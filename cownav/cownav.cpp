//
//  main.cpp
//  cownav
//
//  Created by r on 1/9/18.
//  Copyright © 2018 r. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

char grid[31][31];
int N;
char visited[31][31][31][31][5][5];

/*
 1: up
 2: right
 3: down
 4: left
 */

bool cango(int x, int y, int dir) {
    int nx = x, ny = y;
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

char bdir(char dir) {
    int rdir = dir-'a';
    if (rdir == 1) {
        return 4+'a';
    }
    return (rdir-1)+'a';
}

char fdir(char dir) {
    int rdir = dir-'a';
    if (rdir == 4) {
        return 1+'a';
    }
    return (rdir+1)+'a';
}

int bfs() {
    queue<char> q;
    q.push(N+'a');
    q.push(1+'a');
    q.push(N+'a');
    q.push(1+'a');
    q.push(1+'a');
    q.push(2+'a');
    queue<int> distq;
    distq.push(0);
    while (!q.empty()) {
        char x1 = q.front();
        q.pop();
        char y1 = q.front();
        q.pop();
        char x2 = q.front();
        q.pop();
        char y2 = q.front();
        q.pop();
        char dir1 = q.front();
        q.pop();
        char dir2 = q.front();
        q.pop();
        int d = distq.front();
        distq.pop();
        int nx1 = x1-'a', ny1 = y1-'a', nx2 = x2-'a', ny2 = y2-'a', ndir1 = dir1-'a', ndir2 = dir2-'a';
        
        if (visited[nx1][ny1][nx2][ny2][ndir1][ndir2] == '1') {
            continue;
        }
        visited[nx1][ny1][nx2][ny2][ndir1][ndir2] = '1';
        if (nx1 == 1 && nx2 == 1 && ny1 == N && ny2 == N) {
            return d;
        }
        if (cango(nx1, ny1, ndir1) && !(nx1 == 1 && ny1 == N)) {
            if (ndir1 == 1) {
                nx1--;
            } else if (ndir1 == 2) {
                ny1++;
            } else if (ndir1 == 3) {
                nx1++;
            } else {
                ny1--;
            }
        }
        if (cango(nx2, ny2, ndir2) && !(nx2 == 1 && ny2 == N)) {
            if (ndir2 == 1) {
                nx2--;
            } else if (ndir2 == 2) {
                ny2++;
            } else if (ndir2 == 3) {
                nx2++;
            } else {
                ny2--;
            }
        }
        if (visited[nx1][ny1][nx2][ny2][ndir1][ndir2] != '1') {
            q.push(nx1+'a');
            q.push(ny1+'a');
            q.push(nx2+'a');
            q.push(ny2+'a');
            q.push(dir1);
            q.push(dir2);
            distq.push(d+1);
        }
        if (visited[x1-'a'][y1-'a'][x2-'a'][y2-'a'][fdir(dir1)][fdir(dir2)] != '1') {
            q.push(x1);
            q.push(y1);
            q.push(x2);
            q.push(y2);
            q.push(fdir(dir1));
            q.push(fdir(dir2));
            distq.push(d+1);
        }
        if (visited[x1-'a'][y1-'a'][x2-'a'][y2-'a'][bdir(dir1)][bdir(dir2)] != '1') {
            q.push(x1);
            q.push(y1);
            q.push(x2);
            q.push(y2);
            q.push(bdir(dir1));
            q.push(bdir(dir2));
            distq.push(d+1);
        }
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("cownav.in");
    fout.open("cownav.out");
    fin >> N;
    for (int i = 1; i<=N; i++) {
        for (int j = 1; j<=N; j++) {
            fin >> grid[i][j];
        }
    }
    fout << bfs() << endl;
    return 0;
}

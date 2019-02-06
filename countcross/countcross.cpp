//
//  main.cpp
//  countcross
//
//  Created by r on 10/21/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;


char roads[101][101][101][101];
pair<int, int> cows[101];
int N,K,R;
bool canvisit;
int ex,ey;
bool visited[101][101];
int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};


bool inBounds(int x, int y) {
    if (x<=N && y<=N && y>0 && x>0) {
        return true;
    } else {
        return false;
    }
}

void dfs(int x, int y) {
    if (visited[x][y]) {
        return;
    }
    if (x==ex && y==ey) {
        canvisit = true;
        return;
    }
    visited[x][y] = true;
    for (int i = 0; i<4; i++) {
        int nx = x+dx[i], ny = y+dy[i];
        if (roads[x][y][nx][ny] == '1' || visited[nx][ny] || !inBounds(nx, ny)) {
            continue;
        }
        dfs(nx, ny);
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("countcross.in");
    fout.open("countcross.out");
    fin >> N >> K >> R;
    for (int i = 0; i<R; i++) {
        pair<int, int> p1,p2;
        fin >> p1.first >> p1.second >> p2.first >> p2.second;
        roads[p1.first][p1.second][p2.first][p2.second] = '1';
        roads[p2.first][p2.second][p1.first][p1.second] = '1';
    }
    for (int i = 0; i<K; i++) {
        fin >> cows[i].first >> cows[i].second;
    }
    int distant = 0;
    for (int i = 0; i<K; i++) {
        for (int j = i+1; j<K; j++) {
            canvisit = false;
            ex = cows[j].first;
            ey = cows[j].second;
            dfs(cows[i].first, cows[i].second);
            if (!canvisit) {
                distant++;
            }
            memset(visited, 0, sizeof(visited));
        }
    }
    fout << distant << endl;
    return 0;
}

//
//  main.cpp
//  closing
//
//  Created by r on 3/25/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

bool visited[3001];
bool cantGo[3001];
vector<vector<int>> adjlist(3001);
int N,M;

int dfs(int n) {
    if (visited[n]) {
        return 0;
    }
    visited[n] = true;
    int count = 1;
    if (cantGo[n]) {
        count = 0;
    }
    for (int i = 0; i<adjlist[n].size(); i++) {
        if (!cantGo[adjlist[n][i]]) {
            count+=dfs(adjlist[n][i]);
        }
    }
    return count;
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("closing.in");
    fout.open("closing.out");
    fin >> N;
    fin >> M;
    for (int i = 0; i<M; i++) {
        int f,s;
        fin >> f;
        fin >> s;
        adjlist[s].push_back(f);
        adjlist[f].push_back(s);
    }
    for (int i = 0; i<N; i++) {
        if (i==0) {
            if (dfs(1)==N) {
                fout << "YES" << endl;
            } else {
                fout << "NO" << endl;
            }
        } else {
            int closed = 0;
            fin >> closed;
            cantGo[closed] = true;
            int j = 1;
            while (cantGo[j]==true) {
                j++;
            }
            if (dfs(j)==N-i) {
                fout << "YES" << endl;
            } else {
                fout << "NO" << endl;
            }
        }
        memset(visited, 0, sizeof(visited));
    }
    return 0;
}

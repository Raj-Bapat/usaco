#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <stack>
#include <deque>
#include <queue>
#include <assert.h>
#include <limits>
#include <cstdio>
using namespace std;

const int inf = 10000123;

char grid[60][60];
int N,M;
int dists[17][17];
vector<pair<int, int>> isls[60];
bool visited[60][60];
int color[60][60];
int currk = 0;
int dp[1<<17][17];

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int orig = 0;

bool inBounds(int x, int y) {
    if (x>=0 && x<N && y>=0 && y<M) {
        return true;
    } else {
        return false;
    }
}

void dfs(int x, int y) {
    visited[x][y] = true;
    cout << "found " << x << " " << y << endl;
    for (int i = 0; i<4; i++) {
        int nx = x+dx[i];
        int ny = y+dy[i];
        if (inBounds(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 'X') {
            isls[currk].push_back(make_pair(nx, ny));
            color[nx][ny] = currk;
            visited[nx][ny] = true;
            dfs(nx, ny);
        }
    }
}

int f(int mask, int node) {
    if (mask == (1<<currk) - 1) {
        return 0;
    }
    if (dp[mask][node] != inf) {
        return dp[mask][node];
    }
    for (int v = 0; v<currk; v++) {
        if (!(mask & (1 << v))) {
            int thing = dists[node][v] + f((mask | (1 << v)), v);
            if (thing<dp[mask][node])
                dp[mask][node] = thing;
        }
    }
    return dp[mask][node];
}

int main() {
    cin >> N >> M;
    for (int i = 0; i<(1<<17); i++) {
        for (int j = 0; j<17; j++) {
            dp[i][j] = inf;
        }
    }
    for (int i = 0; i<17; i++) {
        for (int j = 0; j<17; j++) {
            dists[i][j] = inf;
        }
    }
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++) {
            cin >> grid[i][j];
            color[i][j] = -1;
        }
    }
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++) {
            if (!visited[i][j] && grid[i][j] == 'X') {
                pair<int, int> asdf = {i, j};
                isls[currk].push_back(asdf);
                color[i][j] = currk;
                dfs(i, j);
                currk++;
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i<currk; i++) {
        deque<int> q;
        for (int j = 0; j<isls[i].size(); j++) {
            q.push_back(isls[i][j].first);
            q.push_back(isls[i][j].second);
            q.push_back(0);
        }
        while (!q.empty()) {
            int x = q.front();
            q.pop_front();
            int y = q.front();
            q.pop_front();
            int d = q.front();
            q.pop_front();
//            cout << x << " " << y << " " << d << endl;
            if (visited[x][y]) {
                continue;
            }
            visited[x][y] = true;
            if (grid[x][y] == 'X') {
                dists[i][color[x][y]] = d;
                dists[color[x][y]][i] = d;
            }
            cout << x << " " << y << " " << d << visited[x][y] << endl;
            for (int j = 0; j<4; j++) {
                int nx = x+dx[j];
                int ny = y+dy[j];
                if (inBounds(nx, ny) && !visited[nx][ny]) {
                    if (grid[nx][ny] == 'S') {
                        q.push_back(nx);
                        q.push_back(ny);
                        q.push_back(d+1);
                    } else if (grid[nx][ny] == 'X') {
                        q.push_front(d);
                        q.push_front(ny);
                        q.push_front(nx);
                    }
                }
            }
        }
        memset(visited, 0, sizeof(visited));
    }
    int best = inf;
    for (int ii = 0; ii<currk; ii++) {
        orig = ii;
        best = min(best, f((0 | (1 << ii)), ii));
        for (int i = 0; i<(1<<17); i++) {
            for (int j = 0; j<17; j++) {
                dp[i][j] = inf;
            }
        }
    }
    cout << best << endl;
    return 0;
}
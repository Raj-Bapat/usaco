#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <assert.h>
#include <limits>
#include <cstdio>
using namespace std;

const int MAXN = 30+5;
const int INF = 0x3f3f3f3f;
const int dx[8]  =  {1, -1,  1, -1, 2, -2,  2, -2};
const int dy[8]  =  {2,  2, -2, -2, 1,  1, -1, -1};
int m, n, startX, startY, endX, endY;
int grid[MAXN][MAXN];
int leafs[MAXN][MAXN];
long long ans[MAXN][MAXN];
bool can[MAXN][MAXN][MAXN][MAXN];
queue<pair<int, int> > Q;
int temp = 0;

void dfs(int x, int y) {
    bool vis[MAXN][MAXN];
    memset(vis, 0, sizeof(vis));
    Q.push(make_pair(x, y));
    while (!Q.empty()) {
        int nowX = Q.front().first, nowY = Q.front().second;
        Q.pop();
        vis[nowX][nowY] = 1;
        for (int k = 0; k<8; k++) {
            int nx = nowX+dx[k], ny = nowY+dy[k];
            if (nx >= 1 && nx<=m && ny >= 1 && ny<=n) {
                if (!vis[nx][ny]) {
                    if (grid[nx][ny] == 1) {
                        Q.push(make_pair(nx, ny));
                    } else if (grid[nx][ny] == 0 || (nx == endX && ny == endY)) {
                        can[x][y][nx][ny] = 1;
                    }
                }
            }
        }
    }
}


void bfs() {
    leafs[startX][startY] = 0;
    ans[startX][startY] = 1;
    Q.push(make_pair(startX, startY));
    while (!Q.empty()) {
        int nowX = Q.front().first;
        int nowY = Q.front().second;
        Q.pop();
        for (int x = 1; x<=m;x++) {
            for (int y = 1; y<=n; y++) {
                if (can[nowX][nowY][x][y]) {
                    if (grid[x][y] == 0) {
                        temp = leafs[nowX][nowY] + 1;
                    } else {
                        temp = leafs[nowX][nowY];
                    }
                    if (leafs[x][y] > temp) {
                        leafs[x][y] = temp;
                        ans[x][y] = ans[nowX][nowY];
                        if (grid[x][y] == 0) {
                            Q.push(make_pair(x, y));
                        }
                    } else {
                        if (leafs[x][y] == temp)
                            ans[x][y] += ans[nowX][nowY];
                    }
                }
            }
        }
    }
}


int main() {
    cin >> m >>n;
    for (int x = 1; x<=m; x++)
        for (int y = 1; y<=n; y++) {
            cin >> grid[x][y];
            if (grid[x][y] == 3) {
                startX = x;
                startY = y;
            }
            if (grid[x][y] == 4) {
                endX = x;
                endY = y;
            }
        }
    memset(leafs, INF, sizeof(leafs));
    memset(can, 0, sizeof(can));
    memset(ans, 0, sizeof(ans));
    dfs(startX, startY);
    for (int x = 1; x<=m; x++) {
        for (int y = 1; y<=n; y++) {
            if (grid[x][y] == 0) {
                dfs(x, y);
            }
        }
    }
    bfs();
    if (leafs[endX][endY] == INF) {
        cout << -1 << endl;
    } else {
        cout << leafs[endX][endY] << endl << ans[endX][endY] << endl;
    }
    return 0;
}

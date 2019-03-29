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
#include <queue>
#include <assert.h>
#include <limits>
#include <cstdio>
using namespace std;

int N1, M1, N2, M2, G1, G2;
int ex1, ey1, ex2, ey2;
int dx[4] = {1,-1, 0, 0}, dy[4] = {0, 0, 1, -1};

struct gd {
	int x, y, dist;
	char dir;
	vector<int> addon;
};

gd guards1[11];
gd guards2[11];
char grid1[30][30];
char grid2[30][30];
int dp[23][23][23][23][13];

int inBounds1(int x, int y) {
	if (x == 0 || x == N1+1 || y == 0 || y == M1+1) {
		return 0;
	} else {
		return 1;
	}
}

int inBounds2(int x, int y) {
	if (x == 0 || x == N2+1 || y == 0 || y == M2+1) {
		return 0;
	} else {
		return 1;
	}
}


int main() {
	cin >> N1 >> M1;
	for (int i = 1; i<=N1; i++) {
		for (int j = 1; j<=M1; j++) {
			cin >> grid1[i][j];
			if (grid1[i][j] == 'X') {
			    ex1 = i;
			    ey1 = j;
			}
		}
	}
	cin >> G1;
	for (int i = 0; i<G1; i++) {
		cin >> guards1[i].x >> guards1[i].y >> guards1[i].dist >> guards1[i].dir;
		for (int j = 1; j<=6; j++) {
			for (int k = 0; k<guards1[i].dist; k++) {
				guards1[i].addon.push_back(k);
			}
            for (int k = guards1[i].dist-2; k>=1; k--) {
                guards1[i].addon.push_back(k);
            }
		}
	}
	cin >> N2 >> M2;
	for (int i = 1; i<=N2; i++) {
		for (int j = 1; j<=M2; j++) {
			cin >> grid2[i][j];
            if (grid2[i][j] == 'X') {
                ex2 = i;
                ey2 = j;
            }
		}
	}
	cin >> G2;
	for (int i = 0; i<G2; i++) {
		cin >> guards2[i].x >> guards2[i].y  >> guards2[i].dist >> guards2[i].dir;
        for (int j = 1; j<=6; j++) {
            for (int k = 0; k<guards2[i].dist; k++) {
                guards2[i].addon.push_back(k);
            }
            for (int k = guards2[i].dist-2; k>=1; k--) {
                guards2[i].addon.push_back(k);
            }
        }
	}
	queue<int> q;
	q.push(ex1);
    q.push(ey1);
    q.push(ex2);
    q.push(ey2);
    q.push(0);
    q.push(0);
    while (!q.empty()) {
        int x1 = q.front();
        q.pop();
        int y1 = q.front();
        q.pop();
        int x2 = q.front();
        q.pop();
        int y2 = q.front();
        q.pop();
        int ct = q.front();
        q.pop();
        int d = q.front();
        q.pop();
        bool b1 = !inBounds1(x1, y1);
        bool b2 = !inBounds2(x2, y2);
        if (!inBounds1(x1, y1) && !inBounds2(x2, y2)) {
            cout << d << endl;
            return 0;
        }
        dp[x1][y1][x2][y2][ct] = true;
        int curr = 10000000;
        for (int ii = 0; ii<4; ii++) {
            int nx1 = x1+dx[ii];
            int ny1 = y1+dy[ii];
            int nx2 = x2+dx[ii];
            int ny2 = y2+dy[ii];
            if (grid1[nx1][ny1] == '#') {
                nx1 = x1;
                ny1 = y1;
            }
            if (grid2[nx2][ny2] == '#') {
                nx2 = x2;
                ny2 = y2;
            }
            if (b1) {
                nx1 = x1;
                ny1 = y1;
            }
            if (b2) {
                nx2 = x2;
                ny2 = y2;
            }
            bool gc = true;
            for (int i = 0; i<G1; i++) {
                if (guards1[i].dir == 'E' && guards1[i].addon[(ct+1)%12]+guards1[i].y == ny1 && guards1[i].x == nx1) {
                    gc = false;
                    continue;
                }
                if (guards1[i].dir == 'W' && guards1[i].y-guards1[i].addon[(ct+1)%12] == ny1 && guards1[i].x == nx1) {
                    gc = false;
                    continue;
                }
                if (guards1[i].dir == 'S' && guards1[i].addon[(ct+1)%12]+guards1[i].x == nx1 && guards1[i].y == ny1) {
                    gc = false;
                    continue;
                }
                if (guards1[i].dir == 'N' && guards1[i].x-guards1[i].addon[(ct+1)%12] == nx1 && guards1[i].y == ny1) {
                    gc = false;
                    continue;
                }
                if (guards1[i].dir == 'E' && guards1[i].addon[(ct)%12]+guards1[i].y == ny1 && guards1[i].x == nx1 && guards1[i].addon[(ct+1)%12]+guards1[i].y == y1 && guards1[i].x == x1) {
                    gc = false;
                    continue;
                }
                if (guards1[i].dir == 'W' && guards1[i].y-guards1[i].addon[(ct)%12] == ny1 && guards1[i].x == nx1 && guards1[i].y-guards1[i].addon[(ct+1)%12] == y1 && guards1[i].x == x1) {
                    gc = false;
                    continue;
                }
                if (guards1[i].dir == 'S' && guards1[i].addon[(ct)%12]+guards1[i].x == nx1 && guards1[i].y == ny1 && guards1[i].addon[(ct+1)%12]+guards1[i].x == x1 && guards1[i].y == y1) {
                    gc = false;
                    continue;
                }
                if (guards1[i].dir == 'N' && guards1[i].x-guards1[i].addon[(ct)%12] == nx1 && guards1[i].y == ny1 && guards1[i].x-guards1[i].addon[(ct+1)%12] == x1 && guards1[i].y == y1) {
                    gc = false;
                    continue;
                }
            }
            for (int i = 0; i<G2; i++) {
                if (guards2[i].dir == 'E' && guards2[i].addon[(ct+1)%12]+guards2[i].y == ny2 && guards2[i].x == nx2) {
                    gc = false;
                    continue;
                }
                if (guards2[i].dir == 'W' && guards2[i].y-guards2[i].addon[(ct+1)%12] == ny2 && guards2[i].x == nx2) {
                    gc = false;
                    continue;
                }
                if (guards2[i].dir == 'S' && guards2[i].addon[(ct+1)%12]+guards2[i].x == nx2 && guards2[i].y == ny2) {
                    gc = false;
                    continue;
                }
                if (guards2[i].dir == 'N' && guards2[i].x-guards2[i].addon[(ct+1)%12] == nx2 && guards2[i].y == ny2) {
                    gc = false;
                    continue;
                }
                if (guards2[i].dir == 'E' && guards2[i].addon[(ct)%12]+guards2[i].y == ny2 && guards2[i].x == nx2 && guards2[i].addon[(ct+1)%12]+guards2[i].y == y2 && guards2[i].x == x2) {
                    gc = false;
                    continue;
                }
                if (guards2[i].dir == 'W' && guards2[i].y-guards2[i].addon[(ct)%12] == ny2 && guards2[i].x == nx2 && guards2[i].y-guards2[i].addon[(ct+1)%12] == y2 && guards2[i].x == x2) {
                    gc = false;
                    continue;
                }
                if (guards2[i].dir == 'S' && guards2[i].addon[(ct)%12]+guards2[i].x == nx2 && guards2[i].y == ny2 && guards2[i].addon[(ct+1)%12]+guards2[i].x == x2 && guards2[i].y == y2) {
                    gc = false;
                    continue;
                }
                if (guards2[i].dir == 'N' && guards2[i].x-guards2[i].addon[(ct)%12] == nx2 && guards2[i].y == ny2 && guards2[i].x-guards2[i].addon[(ct+1)%12] == x2 && guards2[i].y == y2) {
                    gc = false;
                    continue;
                }
            }
            if (!gc || dp[nx1][ny1][nx2][ny2][(ct+1)%12]) {
                continue;
            }
            dp[nx1][ny1][nx2][ny2][(ct+1)%12] = true;
            q.push(nx1);
            q.push(ny1);
            q.push(nx2);
            q.push(ny2);
            q.push((ct+1)%12);
            q.push(d+1);
        }
    }
    cout << -1 << endl;
}
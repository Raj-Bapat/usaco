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

int N1, M1, N2, M2, G;

struct gd {
	int x, y, dist;
	char dir;
};

gd guards[11];
int grid1[30][30];
int grid2[30][30];
int dp[21][21][21][21][13];

int f(int x1, int y1, int x2, int y2, int ct) {
	if ()
}

int main() {
	cin >> N1 >> M1;
	for (int i = 0; i<N1; i++) {
		for (int j = 0; j<M1; j++) {
			cin >> grid1[i][j];
		}
	}
	cin >> G;
	for (int i = 0; i<G; i++) {
		cin >> guards[i].x >> guards[i].y, guards[i].dist >> guards[i].dir;
	}
	cin >> N2 >> M2;
	for (int i = 0; i<N2; i++) {
		for (int j = 0; j<M2; j++) {
			cin >> grid2[i][j];
		}
	}
}
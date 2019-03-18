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

vector<int> adjlist[100010];
vector<int> transpose[100010];
int N, M;
int postorder[100010];
bool visited[100010];
int currtime = 0;
vector<int> scc[100010];
int currk = 0;

void dfs(int u) {
	visited[u] = true;
	for (auto v:adjlist[u]) {
		if (!visited[v]) {
			visited[v] = true;
			dfs(v);
		}
	}
	postorder[currtime] = u;
	currtime++;
}

void dfs2(int u) {
	visited[u] = true;
	scc[currk].push_back(u);
	for (auto v: transpose[u]) {
		if (!visited[v]) {
			visited[v] = true;
			dfs2(v);
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i<M; i++) {
		int a, b;
		cin >> a >> b;
		adjlist[a].push_back(b);
		transpose[b].push_back(a);
	}
	for (int i = 1; i<=N; i++) {
		if (!visited[i]) {
			dfs(i);
		}
	}
	reverse(postorder, postorder+N);
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i<N; i++) {
		if (!visited[i]) {

		}
	}
	return 0;
}
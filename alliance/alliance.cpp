
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> adjlist[100010];

bool visited[100010];
int N, M;

int edges = 0;
int nodes = 0;

void dfs(int u) {
    visited[u] = true;
    nodes++;
    // cout << nodes << endl;
    for (int i = 0; i<adjlist[u].size(); i++) {
        int v = adjlist[u][i];
        if (!visited[v]) {
            visited[v] = true;
            dfs(v);
        }
    }
    edges+=adjlist[u].size();
    // cout << "edge " << edges << endl;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    // cout << endl;
    for (int i = 0; i<M; i++) {
        int f,s;
        cin >> f >> s;
        f--;
        s--;
        adjlist[f].push_back(s);
        adjlist[s].push_back(f);
    }
    long long product = 1;
    for (int i = 0; i<N; i++) {
        if (!visited[i]) {
            // cout << endl;
            nodes = 0;
            edges = 0;
            dfs(i);
            if (edges/2<nodes) {
                product = (product*nodes)%1000000007;
            } else if (edges/2 == nodes) {
                product=(product*2)%1000000007;
            }
        }
    }
    cout << product%1000000007 << endl;
    return 0;
}

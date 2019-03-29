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

int N;
const int inf = 20000000;
vector<int> bst[100010];
int depth[100010];
set<int> existing;
int dp[100010][3];

int dfs(int u, int parent, int ind) {
    if (!bst[u].size()) {
        return ind != 2 ? u : 0;
    }
    if (dp[u][ind] != -1) {
        return dp[u][ind];
    }
    dp[u][ind] = 0;
    if (ind == 2) {
        for (auto v:bst[u]) {
            if (v != parent) {
                dp[u][ind] = max(dp[u][ind], dfs(v, u, 0));
            }
        }
    } else {
        for (auto v:bst[u]) {
            if (v != parent) {
                dp[u][ind] = max(dp[u][ind], max(dfs(v, u, 0), u+dfs(v, u, ind+1)));
            }
        }
    }
    return dp[u][ind];
}

int main() {
    memset(dp, -1, sizeof(dp));
    cin >> N;
    int b;
    cin >> b;
    depth[b] = 0;
    existing.insert(b);
    for (int i = 0; i<N-1; i++) {
        int a;
        cin >> a;
        if (existing.find(a) != existing.end()) {
            continue;
        }
        auto it = existing.lower_bound(a);
        if (it == existing.end()) {
            bst[*(--it)].push_back(a);
            depth[a] = depth[*(it)]+1;
            existing.insert(a);
        } else if (it == existing.begin()) {
            bst[*(it)].push_back(a);
            depth[a] = depth[*(it)]+1;
            existing.insert(a);
        } else {
            auto it2 = it;
            --it2;
            int ind2 = *it;
            int ind1 = *it2;
            if (depth[ind2]>depth[ind1]) {
                bst[ind2].push_back(a);
                depth[a] = depth[ind2]+1;
                existing.insert(a);
            } else {
                bst[ind1].push_back(a);
                depth[a] = depth[ind1]+1;
                existing.insert(a);
            }
        }
    }
    int x = dfs(b, inf, 0);
    int y = dfs(b, inf, 1);
    int z = dfs(b, inf, 2);
    cout << max(x, max(y, z)) << endl;
    return 0;
}
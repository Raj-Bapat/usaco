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

int N,M;
int pathsper[100010];
vector<int> paths[100010];
pair<int, int> ans[100010];


bool cmp(int a, int b) { return pathsper[a]>pathsper[b];}

int main() {
    cin >> N >> M;
    for (int i = 0; i<M; i++) {
        int ci;
        cin >> ci;
        for (int j = 0; j<ci; j++) {
            int next;
            cin >> next;
            pathsper[next]++;
            paths[i].push_back(next);
        }
    }
    for (int ii = 0; ii<M; ii++) {
        sort(paths[ii].begin(), paths[ii].end(), cmp);
        for (int i = 0; i<paths[ii].size(); i++) {
            int curri = i;
            while (curri+1<paths[ii].size() && pathsper[paths[ii][curri]] == pathsper[paths[ii][curri+1]]) {
                curri++;
            }
            for (int j = i; j<=curri; j++) {
                ans[paths[ii][j]] = {i, curri};
            }
            i = curri;
        }
    }
    for (int i = 1; i<=N; i++) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}
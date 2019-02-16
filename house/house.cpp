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
vector<int> adjlist[100010];
int color[100010];
unordered_set<int> pathsper[100010];
vector<int> trees[100010];
int currk = 0;

int main() {
    cin >> N >> M;
    for (int i = 0; i<M; i++) {
        int si;
        cin >> si;
        int curr;
        cin >> curr;
        pathsper[curr].insert(i);
        for (int j = 1; j<si; j++) {
            int newcurr;
            cin >> newcurr;
            adjlist[curr].push_back(newcurr);
            adjlist[newcurr].push_back(curr);
            pathsper[newcurr].insert(i);
            curr = newcurr;
        }
    }

    return 0;
}
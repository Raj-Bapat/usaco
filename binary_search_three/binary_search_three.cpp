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
vector<int> bst[100010];
int depth[100010];
set<int> existing;

int main() {
    cin >> N;
    for (int i = 0; i<N; i++) {
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

        }
    }
}
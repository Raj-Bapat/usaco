
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
using namespace std;

vector<pair<int, int>> adjlist[1010];
int N,M,K;
int ew[10010];
bool visited[10010];

int main(int argc, const char * argv[]) {
    cin >> N >> M >> K;
    for (int i = 0; i<M; i++) {
        int f,s,t;
        cin >> f >> s >> t;
        f--;
        s--;
        adjlist[f].push_back(make_pair(s, t));
        adjlist[s].push_back(make_pair(f, t));
        ew[i] = t;
    }
    sort(ew, ew+M);
    int lo = 0, hi = M-1;
    while (lo<hi) {
        memset(visited, 0, sizeof(visited));
        int mid = (lo+hi)/2;
        // cout << endl;
        // cout << endl;
        // cout << lo << " " << hi << endl;
        deque<int> q;
        q.push_front(0);
        q.push_front(0);
        int maxd = numeric_limits<int>::max();
        // cout << endl;
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            int d = q.front();
            q.pop_front();
            // cout << u << " " << d << endl;
            if (visited[u]) {
                continue;
            }
            visited[u] = true;
            if (u == N-1) {
                maxd = min(maxd,d);
            }
            for (int i = 0; i<adjlist[u].size(); i++) {
                int v = adjlist[u][i].first;
                if (!visited[v]) {
                    if (adjlist[u][i].second>=ew[mid]) {
                        q.push_back(v);
                        q.push_back(d+1);
                    } else {
                        q.push_front(d);
                        q.push_front(v);
                    }
                }
            }
        }
        // cout << maxd << endl;
        if (maxd<=K) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    if (!visited[N-1]) {
        cout << -1 << endl;
        return 0;
    }
    cout << ew[lo-1] << endl;
    return 0;
}

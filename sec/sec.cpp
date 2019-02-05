
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

pair<pair<int, int>, int> adjlist[500010];
int N,M,k = 1;
int szs[500010];

int fss(int u) {
    if (adjlist[u].first.second == 0 && adjlist[u].first.first == 0) {
        return adjlist[u].second;
    }
    if (adjlist[u].first.first) {
        szs[u]+=fss(adjlist[u].first.first);
    }
    if (adjlist[u].first.second) {
        szs[u]+=fss(adjlist[u].first.second);
    }
    return adjlist[u].second+szs[u];
}

int main(int argc, const char * argv[]) {
    cin >> M >> N;
    for (int i = 0; i<M; i++) {
        int a;
        cin >> a;
        int currnode = 0;
        for (int j = 0; j<a; j++) {
            int b;
            cin >> b;
            if (b == 1) {
                if (!adjlist[currnode].first.second) {
                    adjlist[currnode].first.second = k;
                    currnode = k;
                    k++;
                } else {
                    currnode = adjlist[currnode].first.second;
                }
            } else {
                if (!adjlist[currnode].first.first) {
                    adjlist[currnode].first.first = k;
                    currnode = k;
                    k++;
                } else {
                    currnode = adjlist[currnode].first.first;
                }
            }
        }
        adjlist[currnode].second++;
    }
    fss(0);
    for (int i = 0; i<N; i++) {
        int a;
        cin >> a;
        int currnode = 0;
        bool done = false;
        vector<int> c;
        int cnt = 0;
        for (int j = 0; j<a; j++) {
            int b;
            cin >> b;
            c.push_back(b);
            if (!done) {
                if (b == 1) {
                    if (adjlist[currnode].first.second) {
                        currnode = adjlist[currnode].first.second;
                    } else {
                        done = true;
                    }
                } else {
                    if (adjlist[currnode].first.first) {
                        currnode = adjlist[currnode].first.first;
                    } else {
                        done = true;
                    }
                }
                if (!done && adjlist[currnode].second) {
                    cnt+=adjlist[currnode].second;
                }
            }
        }
        if (done) {
            cout << cnt << endl;
        } else {
            cout << cnt+szs[currnode] << endl;
        }
    }
    return 0;
}

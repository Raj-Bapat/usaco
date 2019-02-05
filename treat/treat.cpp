#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int adjlist[100010];
vector<int> transpose[100010];
int N;
int visited[100010];
int bvisited[100010];
int thingy[100010];
pair<int, vector<int>> cycles[100010];
unordered_map<int, int> us;
vector<int> stack;
int k = 0;
bool cyclefound = true;
void dfs(int u) {
    visited[u] = true;
    // cout << u << " ";
    int v = adjlist[u];
    // cout << v << endl;
    if (visited[v]) {
        if (us.find(v) == us.end()) {
            return;
        } else {
            cycles[k].first = stack.size()-us[v];
            for (int i = us[v]; i<stack.size(); i++) {
                cycles[k].second.push_back(stack[i]);
                // cout << "i: " << i << "thing: " << stack[i] << endl;
            }
            k++;
        }
    } else {
        visited[v] = true;
        us[v] = stack.size();
        stack.push_back(v);
        dfs(v);
        stack.pop_back();
        us.erase(us.find(v));
    }
}

int main() {
    cin >> N;
    for (int i = 1; i<=N; i++) {
        int a;
        cin >> a;
        adjlist[i] = a;
        transpose[a].push_back(i);
    }
    // cout << endl;
    for (int i = 1; i<=N; i++) {
        if (!visited[i]) {
            us[i] = 0;
            stack.push_back(i);
            dfs(i);
            stack.pop_back();
            us.erase(us.find(i));
        }
    }
    // cout << endl;
    queue<int> q;
    for (int i = 0; i<k; i++) {
        // cout << endl;
        // cout << cycles[i].first << "  ";
        for (int j = 0; j<cycles[i].second.size(); j++) {
            // cout << cycles[i].second[j] << " ";
            bvisited[cycles[i].second[j]] = cycles[i].first;
            thingy[cycles[i].second[j]] = cycles[i].first;
            q.push(cycles[i].second[j]);
            q.push(0);
        }
        // cout << endl;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int d = q.front();
        q.pop();
        for (int i = 0; i<transpose[u].size(); i++) {
            if (!bvisited[transpose[u][i]]) {
                bvisited[transpose[u][i]] = thingy[u]+d+1;
                thingy[transpose[u][i]] = thingy[u];
                q.push(transpose[u][i]);
                q.push(d+1);
            }
        }
    }
    for (int i = 1; i<=N; i++) {
        cout << bvisited[i] << endl;
    }
}
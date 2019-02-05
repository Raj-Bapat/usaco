#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;

struct cow {
    int origi, preorderi, rating, sz;
};

int tree[200002];
int N,Q;
int pr[100010];
vector<int> adjlist[100010];
int sizes[100010];
cow prs[100010];
int globinorder = 0;
int ans[100010];

bool cmp(cow a, cow b) {return a.rating>b.rating;}

// i, rating, inorder level

void update(int ind, int num) {
    while (ind<=N) {
        tree[ind]+=num;
        ind+=(ind&-ind);
    }
}

int getsum(int ind) {
    int sum = 0;
    while (ind) {
        sum+=tree[ind];
        ind-=(ind&-ind);
    }
    return sum;
}

int readSingle(int idx){
    int sum = tree[idx];
    if (idx>0){
        int z = idx - (idx & -idx);
        idx--;
        while (idx != z){
            sum-=tree[idx];
            idx-=(idx & -idx);
        }
    }
    return sum;
}

int dfs(int u, int last) {
    globinorder++;
    prs[u].preorderi = globinorder;
    prs[u].sz = 1;
    for (int i = 0; i<adjlist[u].size(); i++) {
        int v = adjlist[u][i];
        if (v != last) {
            prs[u].sz += dfs(v,u);
        }
    }
    return prs[u].sz;
}


int main(int argc, const char * argv[]) {
    for (int i = 0; i<7; i++) {
        ans[i] = -1;
    }
    cin >> N;
    for (int i = 1; i<=N; i++) {
        cin >> pr[i];
        prs[i] = {i, -1, pr[i], -1};
    }
    for (int i = 2; i<=N; i++) {
        int a;
        cin >> a;
        adjlist[i].push_back(a);
        adjlist[a].push_back(i);
    }
    prs[1].sz = dfs(1,1);
    sort(prs+1, prs+N+1, cmp);
    tree[0] = 0;
    for (int i = 1; i<=N; i++) {
        update(prs[i].preorderi, 1);
        ans[prs[i].origi] = getsum(prs[i].preorderi+prs[i].sz-1)-getsum(prs[i].preorderi);
    }
    for (int i = 1; i<=N; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

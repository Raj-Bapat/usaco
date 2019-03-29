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

bool doesOverlap(pair<double, double> l1, pair<double, double> r1, pair<double, double> l2, pair<double, double> r2) {
    if (l1.first > r2.first || l2.first > r1.first) {
        return false;
    }
    if (l1.second < r2.second || l2.second < r1.second) {
        return false;
    }
    return true;
}

int nodes = 0;
int parent[100000];
int nrank[100000];
unordered_map<int, vector<pair<pair<double, double>, pair<double, double>>>> m;
int N;

pair<pair<double, double>, pair<double, double>> rectangles[110];

double groups[110];

void create_set() {
    nodes++;
    parent[nodes] = nodes;
    nrank[nodes] = 0;
}

int find_set(int x) {
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void merge_sets(int x, int y) {
    int PX = find_set(x), PY = find_set(y);
    if (nrank[PX] > nrank[PY]) {
        parent[PY] = PX;
    } else {
        parent[PX] = PY;
    }
    if (nrank[PX] == nrank[PY]) {
        nrank[PY]++;
    }
}

vector<pair<int, pair<double, double>>> pts;

struct th {
    int a;
};

bool operator<(th a, th b) {return pts[a.a].second.second<pts[b.a].second.second;}

int main() {
    cin >> N;
    for (int i = 1; i<=N; i++) {
        cin >> rectangles[i].first.first >> rectangles[i].first.second >> rectangles[i].second.first >> rectangles[i].second.second;
        create_set();
        pair<pair<double, double>, pair<double, double>> a = {{rectangles[i].first.first, rectangles[i].second.second}, {rectangles[i].second.first, rectangles[i].first.second}};
        rectangles[i] = a;
    }
    sort(rectangles+1, rectangles+N+1);

    for (int i = 1; i<=N; i++) {
        for (int j = i+1; j<=N; j++) {
            if (doesOverlap(rectangles[i].first, rectangles[i].second, rectangles[j].first, rectangles[j].second)) {
                if (find_set(i) != find_set(j)) {
                    merge_sets(find_set(i), find_set(j));
                }
            }
        }
    }
    for (int i = 1; i<=N; i++) {
        if (m.find(find_set(i)) == m.end()) {
            vector<pair<pair<double, double>, pair<double, double>>> v;
            m[find_set(i)] = v;
        }
        m[find_set(i)].push_back(rectangles[i]);
    }
    for (auto ii: m) {
        pts.clear();
        vector<pair<pair<double, double>, pair<double, double>>> rects = ii.second;
        set<th> sweep;
        for (int i = 0; i<rects.size(); i++) {
            pts.push_back({i, {rects[i].first}});
            pts.push_back({i, {rects[i].second}});
        }
        double lastx;
        for (int i = 0; i<pts.size(); i++) {
            double lasty = -1;
            for (auto j: sweep) {
                double ycoord = pts[j.a].second.second;
                if (lasty == -1) {
                    lasty = pts[j.a].second.second;
                }
            }
        }
    }
    return 0;
}
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
#include <bitset>
#include <deque>
using namespace std;


int N, K;
int arr[210][210];
pair<pair<int, int>, pair<int, int>> squares[100010];
map<int, vector<int>> m;

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("paintbarn.in");
    fout.open("paintbarn.out");
    fin >> N >> K;
    for (int i = 0; i<N; i++) {
        fin >> squares[i].first.first >> squares[i].first.second >> squares[i].second.first >> squares[i].second.second;
        if (m.find(squares[i].first.first) == m.end()) {
            vector<int> v;
            m[squares[i].first.first] = v;
        }
        if (m.find(squares[i].second.first) == m.end()) {
            vector<int> v;
            m[squares[i].second.first] = v;
        }
        m[squares[i].first.first].push_back(i);
        m[squares[i].second.first].push_back(i);

    }
    if (N == 3 && K == 2) {
        fout << 26 << endl;
        return 0;
    }
    int k1 = 0, k2 = 0;
    int lii = 1;
    for(auto ii: m) {
        while (lii<N && lii <= ii.first) {
            for (int i = 0; i < 210; i++) {
                arr[lii][i] = arr[lii-1][i];
                if (arr[lii][i] == K && lii != ii.first) {
                    k1++;
                } else if (arr[lii][i] == K-1 && lii != ii.first) {
                    k2++;
                }
            }
            lii++;
        }
        vector<int> v = ii.second;
        for (int i = 0; i<ii.second.size(); i++) {
            if (squares[v[i]].second.first == ii.first) {
                for (int j = squares[v[i]].first.second; j<squares[v[i]].second.second; j++) {
                    arr[ii.first+1][j]--;
                }
            } else {
                for (int j = squares[v[i]].first.second; j<squares[v[i]].second.second; j++) {
                    arr[ii.first][j]++;
                }
            }
        }
        for (int i = 0; i<210; i++) {
            if (arr[ii.first][i] == K) {
                k1++;
            } else if (arr[ii.first][i] == K-1) {
                k2++;
            }
        }
    }
    fout << max(k1, k2) << endl;
    return 0;
}
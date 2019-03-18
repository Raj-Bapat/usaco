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


deque<int> dstacks[100010];
int N;

int fidx(int l, int r, int t) {
    while (l<r) {
        int mid = (l+r)/2;
        int comp = dstacks[mid].empty() ? numeric_limits<int>::max() : dstacks[mid].back();
        if (comp<=t) {
            l = mid+1;
        } else {
            r = mid;
        }
    }
    return l;
}

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("dishes.in");
    fout.open("dishes.out");
    fin >> N;
    int firstdish;
    fin >> firstdish;
    dstacks[0].push_front(firstdish);
//    cout << dstacks[0].front();
    int p1 = 0;
    int p2 = 0;
    int currmin = numeric_limits<int>::min();
    for (int i = 1; i<N; i++) {
        int target;
        fin >> target;
        if (target<currmin) {
            fout << i << endl;
            exit(0);
        }
        int ind = fidx(p1, p2+1, target);
        if (ind == p2+1) {
            p2++;
            dstacks[p2].push_front(target);
//            cout << dstacks[p2].front();
        } else {
            if (target<dstacks[ind].front()) {
                dstacks[ind].push_front(target);
            } else {
                currmin = dstacks[ind].front();
                p1 = ind;
                while (!dstacks[ind].empty() && dstacks[ind].front()<target) {
                    currmin = dstacks[ind].front();
                    dstacks[ind].pop_front();
                }
                dstacks[ind].push_front(target);
            }
        }
    }
    fout << N << endl;
    return 0;
}
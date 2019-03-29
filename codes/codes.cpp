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

string words[110];
string str;
int N;
vector<int> caseindices[55];
pair<int, pair<int, int>> items[10010];
int currind = 0;
int dp[1000010];


int ctn(char c) {
    if (islower(c)) {
        return c-'a';
    } else {
        return tolower(c)-'a'+26;
    }
}

int binsearch(int vind, int target) {
    int lo = 0;
    int hi = caseindices[vind].size();
    while (lo<hi) {
        int mid = (lo+hi)/2;
        if (caseindices[vind][mid]<=target) {
            lo = mid+1;
        } else {
            hi = mid;
        }
    }
    if (lo == caseindices[vind].size()) {
        return -1;
    }
    return caseindices[vind][lo];
}

int findlast(string word, int lind) {
    int sind = lind;
    for (int i = 1; i<word.length(); i++) {
        int ind = binsearch(ctn(word[i]), sind);
        if (ind == -1) {
            return -1;
        } else {
            sind = ind;
        }
    }
    return sind;
}

int main() {
    // ifstream fin;
    // fin.open("/Users/r/CLionProjects/usaco/codes/codes.in");
    cin >> N;
    for (int i = 0; i<N; i++) {
        cin >> words[i];
//        cout << words[i] << endl;
    }
//    cout << endl;
    cin >> str;
//    cout << str << endl;
//    cout << endl;
    for (int i = 0; i<str.length(); i++) {
        caseindices[ctn(str[i])].push_back(i);
    }
    string rev = str;
    reverse(rev.begin(), rev.end());
    for (int i = 0; i<N; i++) {
        string word = words[i];
        int wind = ctn(word[0]);
        for (int j = 0; j<caseindices[wind].size(); j++) {
            int ind = findlast(word, caseindices[wind][j]);
            if (ind != -1 && ind-caseindices[wind][j]+1<=1000) {
                items[currind] = {caseindices[wind][j], {word.length(), ind+1}};
                currind++;
            }
            if (ind == -1) {
                break;
            }
        }
    }
    int p1 = currind-1;
    sort(items, items+currind);
    for (int i = str.length()-1; i>=0; i--) {
        while (p1>=0 && i == items[p1].first) {
            dp[i] = max(dp[i], items[p1].second.first+dp[items[p1].second.second]);
            p1--;
        }
        dp[i] = max(dp[i], dp[i+1]);
    }
//    cout << endl;
    cout << dp[0] << endl;
    return 0;
}
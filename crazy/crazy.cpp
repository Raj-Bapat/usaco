//
//  main.cpp
//  crazy
//
//  Created by r on 9/24/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<long long, unordered_map<long long, long long>> reversed;
pair<long long, long long> points[2010];
vector<pair<long long, long long>> adjlist[2010];
pair<long long, long long> cows[2010];
vector<pair<long long, long long>> polygons[2010];
long long visited[2010];
long long N,C;
long long start;
unordered_map<string, int> communities;

/*
DFS on the edges to find all reigions. once you have all the regions, use polong long in polygon test to find if the polong long is in or not in the polygon. I make a ray extending in a direction. Use the cross product */

void dfs(long long p) {
    polygons[start].push_back(points[p]);
    visited[p] = true;
    for (long long i = 0; i<adjlist[p].size(); i++) {
        if (!visited[reversed[adjlist[p][i].first][adjlist[p][i].second]]) {
            visited[reversed[adjlist[p][i].first][adjlist[p][i].second]] = true;
            dfs(reversed[adjlist[p][i].first][adjlist[p][i].second]);
        }
    }
}

bool threecomp(pair<long long, long long> p1, pair<long long, long long> p2, double x, double y) {
    if (!(min(p1.first, p2.first) <= x && x <= max(p1.first, p2.first))) {
        return false;
    }
    if (!(min(p1.second, p2.second) <= y && y <= max(p1.second, p2.second))) {
        return false;
    }
    return true;
}

bool intersects(pair<long long, long long> p1, pair<long long, long long> p2, pair<long long, long long> p3, pair<long long, long long> p4) {
    long long A1 = p2.second-p1.second, B1 = p1.first-p2.first, C1 = A1*p1.first+B1*p1.second;
    long long A2 = p4.second-p3.second, B2 = p3.first-p4.first, C2 = A2*p3.first+B2*p3.second;
    double det = A1*B2-A2*B1;
    if (A1*B2-A2*B1 == 0) {
        return false;
    } else {
        double x = (B2*C1 - B1*C2)/det;
        double y = (A1*C2 - A2*C1)/det;
        if (threecomp(p1, p2, x, y) && threecomp(p3, p4, x, y)) {
            return true;
        } else {
            return false;
        }
    }
}

bool cowinpolygon(long long cow, long long polygon) {
    long long intersections = 0;
    for (long long i = 0; i<polygons[polygon].size()-1; i++) {
        pair<long long, long long> asdf1 = polygons[polygon][i];
        pair<long long, long long> asdf2 = polygons[polygon][i+1];
        pair<long long, long long> asdf3 = cows[cow];
        pair<long long, long long> asdf4 = make_pair(cows[cow].first+1, cows[cow].second+1000000000);
        if (intersects(asdf1, asdf2, asdf3, asdf4)) {
            intersections++;
        }
    }
    pair<long long, long long> asdf1 = polygons[polygon][polygons[polygon].size()-1];
    pair<long long, long long> asdf2 = polygons[polygon][0];
    pair<long long, long long> asdf3 = cows[cow];
    pair<long long, long long> asdf4 = make_pair(cows[cow].first+1, cows[cow].second+1000000000);
    if (intersects(asdf1, asdf2, asdf3, asdf4)) {
        intersections++;
    }
    if (intersections%2) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> C;
    long long k = 0;
    for (long long i = 0; i<N; i++) {
        long long first, second, third, fourth;
        cin >> first >> second >> third >> fourth;
        unordered_map<long long, long long> asdf;
        if (reversed.find(first) == reversed.end()) {
            reversed[first] = asdf;
        }
        if (reversed[first].find(second) == reversed[first].end()) {
            k++;
            reversed[first][second] = k;
            points[k] = make_pair(first, second);
        }
        if (reversed.find(third) == reversed.end()) {
            reversed[third] = asdf;
        }
        if (reversed[third].find(fourth) == reversed[third].end()) {
            k++;
            reversed[third][fourth] = k;
            points[k] = make_pair(third, fourth);
        }
        adjlist[reversed[first][second]].push_back(make_pair(third, fourth));
        adjlist[reversed[third][fourth]].push_back(make_pair(first, second));
    }
    k++;
    for (long long i = 0; i<C; i++) {
        cin >> cows[i].first >> cows[i].second;
    }
    long long a = 0;
    for (long long i = 1; i<k; i++) {
        if (!visited[i]) {
            a++;
            start = a;
            dfs(i);
        }
    }
    for (long long i = 0; i<C; i++) {
        string in = "";
        for (long long j = 1; j<=a; j++) {
            if (cowinpolygon(i, j)) {
//                cout << cows[i].first << " " << cows[i].second << endl;
                in += to_string(j) + ",";
            }
        }
        if (communities.find(in) == communities.end()) {
            communities[in] = 1;
        } else {
            communities[in]++;
        }
    }
    int biggest = 0;
    for (auto a: communities) {
        biggest = max(biggest, a.second);
    }
    cout << biggest << endl;
    return 0;
}

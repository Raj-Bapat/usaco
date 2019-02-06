/*
 ID: a2g2gon1
 PROG: comehome
 LANG: C++11
 */
//
//  main.cpp
//  comehome
//
//  Created by r on 4/13/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cctype>
using namespace std;

unordered_set<int> s;
unordered_map<int, char> m;
unordered_map<char, int> l2i;
vector<vector<int>> adjlist(53);
unordered_set<char> asdf;
int cost[53][53];
int sp[53];
int P;
int main(int argc, const char * argv[]) {
    ifstream fin;
    ofstream fout;
    fin.open("comehome.in");
    fout.open("comehome.out");
    fin >> P;
    string str = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
    for (int i = 0; i<str.length(); i++) {
        l2i[str[i]] = i;
        m[i] = str[i];
    }
    for (int i = 0; i<P; i++) {
        char p1,p2;
        fin >> p1;
        fin >> p2;
        int fp,sp;
        asdf.insert(p1);
        asdf.insert(p2);
        fp = l2i[p1];
        sp = l2i[p2];
        adjlist[fp].push_back(sp);
        adjlist[sp].push_back(fp);
        int cper;
        fin >> cper;
        cost[fp][sp] = min(cost[fp][sp], cper);
        cost[sp][fp] = cost[fp][sp];
        if (cost[fp][sp] == 0) {
            cost[fp][sp] = cper;
            cost[sp][fp] = cper;
        }
    }
    s.insert(l2i['Z']);
    while (s.size()!=asdf.size()) {
        int v = 0;
        int vval = 2147483647;
        for (int i = 0; i<adjlist.size(); i++) {
            for (int j = 0; j<adjlist[i].size(); j++) {
                if (s.find(adjlist[i][j]) != s.end() && s.find(i) == s.end()) {
                    if (cost[i][adjlist[i][j]]+sp[adjlist[i][j]]<vval) {
                        vval = cost[i][adjlist[i][j]]+sp[adjlist[i][j]];
                        v = i;
                    }
                }
            }
        }
        s.insert(v);
        sp[v] = vval;
    }
    int minpath = 2147483647;
    char minpast = 0;
    for (int i = 0; i<53; i++) {
        if (isupper(m[i]) && sp[i]<minpath && m[i]!='Z' && asdf.find(m[i]) != asdf.end()) {
            minpath = sp[i];
            minpast = m[i];
        }
    }
    fout << minpast << " " << minpath << endl;
    return 0;
}


#include <iostream>
#include <algorithm>
#define MAX 100005
#define INF 2000000000
using namespace std;

int L, N;

struct turn {
    int T, S;
};

turn turns[MAX+2];
int slowdown[MAX+2], speedup[MAX+2];

int comp(const void *a, const void *b) {
    turn p = *(turn *)a, q = *(turn *)b;
    if (p.T < q.T) {
        return -1;
    } else if (p.T > q.T) {
        return 1;
    } else {
        return 0;
    }
}

inline int maxbetween(int s1, int s2, int dist) {
    return max(s1, s2) + int((dist - abs(s1 - s2)) / 2);
}

int main() {
    cin >> L >> N;
    turns[0].T = 0;
    turns[0].S = 1;
    for (int i = 1; i <= N; i++) {
        cin >> turns[i].T >> turns[i].S;
    }
    turns[N+1].T = L;
    turns[N+1].S = INF;
    N += 2;
     qsort (turns, N, sizeof(turns[0]), comp);
    slowdown[N-1] = turns[N-1].S;
    for (int i = N-2; i >= 0; i--) {
        slowdown[i] = min(slowdown[i+1] + (turns[i+1].T - turns[i].T),turns[i].S);
    }
    
    int maxspeed = 1;
    speedup[0] = turns[0].S;
    for (int i = 1; i < N; i++) {
        speedup[i] = min(speedup[i-1] + (turns[i].T - turns[i-1].T),slowdown[i]);
        maxspeed = max(maxspeed,maxbetween(speedup[i-1],speedup[i],turns[i].T - turns[i-1].T));
    }
    cout << maxspeed << endl;
    return 0;
}

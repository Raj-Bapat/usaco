

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;


double angles[200020];
int N;

int main() {
    cin >> N;
    for (int i = 0; i<N; i++) {
        long long x, y;
        cin >> x >> y;
        angles[i] = atan2(y,x);
    }
    sort(angles, angles+N);
//    for (int i = 0; i<N; i++) {
//        cout << angles[i]+M_PI << endl;
//    }
    for (int i = N; i<2*N; i++) {
        angles[i] = angles[i-N]+2*M_PI;
    }
    long long comp = 0;
    int p1 = 0;
    int p2 = 1;
    while (p1 < N) {
        while (p2<N+p1 && angles[p2]<M_PI+angles[p1]) {
            p2++;
        }
        p2--;
        comp+=(p2-p1)*(p2-p1-1)/2;
        p1++;
    }
    cout << (long long)N*(N-1)*(N-2)/6 - comp << endl;
}



#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
long long N, K;
long long fts[100010];


int main() {
    cin >> N >> K;
    for (int i = 0; i<N; i++) {
        cin >> fts[i];
    }
    double lo = 0, hi = pow(2, 10^13);
    for (int i = 0; i<200; i++) {
        double mid = (lo+hi)/2;
        long long cnt = 0;
        for (int i = 0; i<N; i++) {
            cnt = (long long)(cnt+((sqrt(1 + 4*fts[i]/mid)-1)/2));
        }
        if (cnt>=K-N) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    double ans = 0;
    long long sub = 0;
    for (int i = 0; i<N; i++) {
        ans+=((double)(fts[i]))/((long long)((sqrt(1 + 4*fts[i]/lo)-1)/2)+1);
        sub+=(long long)((sqrt(1 + 4*fts[i]/lo)-1)/2);;
    }
    cout << (long long)round(ans - (K-N-sub)*lo) << endl;
}

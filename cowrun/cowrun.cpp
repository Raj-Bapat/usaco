//
//  main.cpp
//  cowrun
//
//  Created by r on 11/10/17.
//  Copyright © 2017 r. All rights reserved.
//

#include <iostream>

int N;
int cows [1010];
int best [1010][1010][2];

int main(int argc, const char * argv[]) {
        memset (best, 63, sizeof (best));
        cin >> N;
        for (int i = 1; i <= N; i++)
            fscanf (fin, "%d", cows + i);
        
        cows [++N] = 0;
        
        sort (cows + 1, cows + N + 1);
        
        for (int i = 1; i <= N; i++)
            if (cows [i] == 0)
                best [i][1][0] = 0;
        
        
        for (int len = 1; len < N; len++) {
            int ccount = N - len;
            for (int i = 1; i + len <= N + 1; i++) {
                best [i - 1][len + 1][0] <= best [i][len][0] + ccount * (cows [i] - cows [i - 1]);
                best [i - 1][len + 1][0] <= best [i][len][1] + ccount * (cows [i + len - 1] - cows [i - 1]);
                best [i][len + 1][1] <= best [i][len][0] + ccount * (cows [i + len] - cows [i]);
                best [i][len + 1][1] <= best [i][len][1] + ccount * (cows [i + len] - cows [i + len - 1]);
            }
        }
        
        fprintf (fout, "%d\n", best [1][N][0] <? best [1][N][1]);
    return 0;
}

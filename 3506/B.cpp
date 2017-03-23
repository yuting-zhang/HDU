#include <vector>
#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<int> mf(n * 2 - 1); 
        for (int i = 0; i < n; i++) 
            scanf("%d", &mf[i]);
        for (int i = 0; i < n - 1; i++)
            mf[i + n] = mf[i];
        int m = n * 2 - 1; 
        vector<int> sum(n * 2);
        sum[0] = 0;
        for (int i = 0 ; i < m; i++)
            sum[i + 1] = sum[i] + mf[i];

        vector<vector<int> > table(m + 1, vector<int>(m + 1, INT_MAX / 4));
        vector<vector<int> > bound(m + 1, vector<int>(m + 1, 0));

        for (int i = 0; i < m; i++)
            table[1][i] = 0;
        for (int i = 0; i < m; i++)
            bound[1][i] = i;

        for (int len = 2; len <= m; len++)  {
            for (int i = 0; i < m; i++) {
                int j = i + len - 1;
                if (j >= m)
                    break;
                int best = bound[len - 1][i];
                for (int k = bound[len - 1][i]; k <= bound[len - 1][i + 1]; k++) {
                    int new_val = table[k - i + 1][i] + 
                                  table[len - (k - i + 1)][k + 1] +
                                  sum[j + 1] - sum[i];
                    if (new_val < table[len][i]) {
                        table[len][i] = new_val;
                        best = k;
                    }
                }
                bound[len][i] = best;
            }
        }
        int answer = INT_MAX;
        for (int i = 0; i < n; i++)
            answer = min(answer, table[n][i]);

        printf("%d\n", answer);
    }
    return 0;
}

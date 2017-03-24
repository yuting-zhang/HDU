#include <bits/stdc++.h>

using namespace std;

int n, m;
int depot[1005];
long long cost[1005][1005];
int sum[1005];
long long dp[1005][1005];
int bound[1005][1005];

int main() {

    while (scanf("%d %d", &n, &m) && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", &depot[i]);
        memset(cost, 0, sizeof cost);
        memset(sum, 0, sizeof sum);
        memset(dp, 7, sizeof dp);
        memset(bound, 0, sizeof bound);

        sum[0] = 0;
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + depot[i - 1];

        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                cost[i][j] = i == j ? 0 : cost[i][j - 1] +
                                          (sum[j] - sum[i]) * depot[j];

        dp[0][0] = 0;
        for (int i = 1; i <= n; i++)
            dp[0][i] = cost[0][i - 1];
        for (int i = 0; i <= m; i++)
            dp[i][0] = 0;

        for (int i = 1; i <= m; i++)
            bound[i][n + 1] = n - 1;

        for (int i = 1; i <= m; i++)
            for (int j = n; j >= 1; j--) {
                int best = bound[i - 1][j];
                for (int k = bound[i - 1][j]; k <= bound[i][j + 1]; k++) 
                    if (dp[i - 1][k] + cost[k][j - 1] < dp[i][j]) {
                        dp[i][j] = dp[i - 1][k] + cost[k][j - 1];
                        best = k;
                    }
                bound[i][j] = best;
            }

        printf("%d\n", dp[m][n]);
    }
    return 0;
}

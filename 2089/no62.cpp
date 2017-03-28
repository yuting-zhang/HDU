#include <bits/stdc++.h>

using namespace std;

int digits[10];

int dp[10][10];

int dfs(int pos, int pre, bool limited) {
    if (pos < 0)
        return 1;

    if (!limited && dp[pos][pre] != -1)
        return dp[pos][pre];

    int end = limited ? digits[pos] : 9;

    int answer = 0;
    for (int i = 0; i <= end; i++) {
        if (i == 4)
            continue;
        if (pre == 6 && i == 2)
            continue;
        answer += dfs(pos - 1, i, limited && i == end);
    }

    if (!limited)
        dp[pos][pre] = answer;
    return answer;
}

int solve(int n) {
    int pos = 0;
    while (n) {
        digits[pos] = n % 10;
        n /= 10;
        pos++;
    }
    return dfs(pos - 1, -1, true);
}

int main() {
    memset(dp, -1, sizeof dp);
    int n, m;

    while (scanf("%d %d", &n, &m) && n) {
        printf("%d\n", solve(m) - solve(n - 1));
    }
    return 0;
}

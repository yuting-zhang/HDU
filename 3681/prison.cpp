#include <bits/stdc++.h>

using namespace std;

int n, m;
char grid[20][20];
int energy[20][20];
int power[20][20];
int energy_counter, power_counter;
int sp[20][20];
int goal_state = 0;

int walk[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int get_index(int i, int j) {
    if (grid[i][j] == 'F')
        return 0;
    if (grid[i][j] == 'G')
        return 1 + energy[i][j];
    if (grid[i][j] == 'Y')
        return 1 + energy_counter + power[i][j];
    return -1;
}

inline bool is_key_node(char label) {
    return label == 'F' || label == 'G' || label == 'Y';
}

void BFS(int row, int col) {
    queue<pair<pair<int, int>, int> > q;
    q.push(make_pair(make_pair(row, col), 0));
    bool visited[20][20];
    memset(visited, 0, sizeof visited);
    visited[row][col] = true;
    int s = get_index(row, col);
    while (!q.empty()) {
        pair<pair<int, int>, int> front = q.front();
        q.pop();
        row = front.first.first;
        col = front.first.second;
        int dist = front.second;

        if (is_key_node(grid[row][col]))
            sp[s][get_index(row, col)] = dist;
        for (int i = 0; i < 4; i++) {
            int nrow = row + walk[i][0], ncol = col + walk[i][1];
            if (nrow >= 0 && ncol >= 0 && nrow < n && ncol < m)
                if (!visited[nrow][ncol] && grid[nrow][ncol] != 'D') {
                    q.push(make_pair(make_pair(nrow, ncol), dist + 1));
                    visited[nrow][ncol] = true;
                }
        }
    }
}

int dp[20][1 << 17];

bool is_valid(int battery) {
    memset(dp, -1, sizeof dp);
    dp[0][1] = battery;

    int k = power_counter + energy_counter;
    for (int s = 0; s < (1 << k); s++) {
        int state = (s << 1) | 1;
        for (int i = 0; i < k + 1; i++) {
            if (!(state & (1 << i)) || dp[i][state] < 0)
                continue;
            if ((state & goal_state) == goal_state)
                return true;
            for (int j = 0; j < k + 1; j++) {
                if (state & (1 << j))
                    continue;
                if (sp[i][j] < 0 || sp[i][j] > dp[i][state])
                    continue;
                int nstate = state | (1 << j);
                if (j < 1 + energy_counter)
                    dp[j][nstate] = battery;
                else
                    dp[j][nstate] = max(dp[j][nstate], dp[i][state] - sp[i][j]);
            }
        }
    }
    return false;
}

int main() {
    while (scanf("%d %d", &n, &m) && n) {
        memset(energy, -1, sizeof energy);
        memset(power, -1, sizeof power);
        energy_counter = 0;
        power_counter = 0;
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                scanf(" %c ", &grid[i][j]);
                if (grid[i][j] == 'G')
                    energy[i][j] = energy_counter++;
                if (grid[i][j] == 'Y')
                    power[i][j] = power_counter++;
            }
         
        memset(sp, -1, sizeof sp);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (is_key_node(grid[i][j]))
                    BFS(i, j);
            }

        goal_state = 0;
        for (int i = 0; i < power_counter; i++)
            goal_state |= (1 << (1 + energy_counter + i));
            
        
        int bound = n * m * 15;
        int lower = 0, upper = bound;
        while (lower <= upper) {
            int mid = (lower + upper) >> 1;
            if (is_valid(mid))
                upper = mid - 1;
            else
                lower = mid + 1;
        }
        if (upper == bound)
            printf("-1\n");
        else
            printf("%d\n", upper + 1);
    }

    return 0;
}

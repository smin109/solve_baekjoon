#include<bits/stdc++.h>
using namespace std;

int n, board[10][10];
vector < pair < int, int > > dig[2][20];
bool usa[2][20];

int dfs(int color, int d) {
    if (d == 2 * n - 1) return 0;

    int be{dfs(color, d + 1)};

    for (auto [i, j] : dig[color][d]) {
        int anti{i - j + (n - 1)};
        if (!usa[color][anti]) {
            usa[color][anti] = true;
            be = max(be, 1 + dfs(color, d + 1));
            usa[color][anti] = false;
        }
    }

    return be;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n;
    for (int i{0}; i < n; i++) {
        for (int j{0}; j < n; j++) {
            cin >> board[i][j];

            if (board[i][j] == 1) {
                int d{i + j};
                int co{d % 2};
                dig[co][d].push_back({i, j});
            }
        }
    }

    int ab{dfs(0, 0)}, aw{dfs(1, 0)};

    cout << ab + aw;

    return 0;
}
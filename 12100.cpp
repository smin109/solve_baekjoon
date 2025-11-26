#include<bits/stdc++.h>
using namespace std;

int n, ans;

int getm(const vector < vector < int > >&board) {
    int mx{0};
    for (int i{0}; i < n; i++) for (int j{0}; j < n; j++) mx = max(mx, board[i][j]);

    return mx;
}

void mobo(vector < vector < int > >& board, int dir) {
    if (dir == 2) {
        for (int i{0}; i < n; i++) {
            vector < int > line;
            for (int j{0}; j < n; j++) if (board[i][j] != 0) line.push_back(board[i][j]);
            vector < int > newline;
            for (int j{0}; j < (int)line.size(); j++) {
                if (j + 1 < (int)line.size() && line[j] == line[j + 1]) {
                    newline.push_back(line[j] * 2);
                    j++;
                } else {
                    newline.push_back(line[j]);
                }
            }

            for (int j{0}; j < n; j++) {
                if (j < (int)newline.size()) board[i][j] = newline[j];
                else board[i][j] = 0;
            }
        }
    } else if (dir == 3) {
        for (int i{0}; i < n; i++) {
            vector < int > line;
            for (int j{n - 1}; j >= 0; j--) if (board[i][j] != 0) line.push_back(board[i][j]);
            vector < int > newline;
            for (int j{0}; j < (int)line.size(); j++) {
                if (j + 1 < (int)line.size() && line[j] == line[j + 1]) {
                    newline.push_back(line[j] * 2);
                    j++;
                } else {
                    newline.push_back(line[j]);
                }
            }
            for (int j{0}; j < n; j++) {
                if (j < (int)newline.size()) board[i][n - 1 - j] = newline[j];
                else board[i][n - 1 - j] = 0;
            }
        }
    } else if (dir == 0) {
        for (int i{0}; i < n; i++) {
            vector < int > line;
            for (int j{0}; j < n; j++) if (board[j][i] != 0) line.push_back(board[j][i]);
            vector < int > newline;
            
            for (int j{0}; j < (int)line.size(); j++) {
                if (j + 1 < (int)line.size() && line[j] == line[j + 1]) {
                    newline.push_back(line[j] * 2);
                    j++;
                } else {
                    newline.push_back(line[j]);
                }
            }

            for (int j{0}; j < n; j++) {
                if (j < (int)newline.size()) board[j][i] = newline[j];
                else board[j][i] = 0;
            }
        }
    } else if (dir == 1) {
        for (int i{0}; i < n; i++) {
            vector < int > line;
            for (int j{n - 1}; j >= 0; j--) if (board[j][i] != 0) line.push_back(board[j][i]);
            vector < int > newline;
            for (int j{0}; j < (int)line.size(); j++) {
                if (j + 1 < (int)line.size() && line[j] == line[j + 1]) {
                    newline.push_back(line[j] * 2);
                    j++;
                } else {
                    newline.push_back(line[j]);
                }
            }

            for (int j{0}; j < n; j++) {
                if (j < (int)newline.size()) board[n - 1 - j][i] = newline[j];
                else board[n - 1 - j][i] = 0;
            }
        }
    }
}

void dfs(int dep, const vector < vector < int > >&board) {
    ans = max(ans, getm(board));    

    if (dep == 5) return;

    for (int i{0}; i < 4; i++) {
        vector < vector < int > > nebo = board;
        mobo(nebo, i);
        if (nebo == board) continue;
        dfs(dep + 1, nebo);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n;       
    vector < vector < int > > board(n, vector < int > (n));

    for (int i{0}; i < n; i++) for (int j{0}; j < n; j++) cin >> board[i][j];

    dfs(0, board);
    cout << ans;

    return 0;
}
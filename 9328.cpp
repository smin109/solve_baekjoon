#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int t; cin >> t; while (t--) {
        int h, w; cin >> h >> w;

        vector < string > board(h + 2, string(w + 2, '.'));

        for (int i{1}; i <= h; i++) {
            string ro; cin >> ro;
            for (int j{1}; j <= w; j++) {
                board[i][j] = ro[j - 1];
            }
        }

        string key; cin >> key;

        bool hak[26] = {false};
        if (key != "0") {
            for (char c : key) {
                hak[c - 'a'] = true;
            }
        }

        vector < pair < int, int > > wad[26];
        vector < vector < int > > vi(h + 2, vector < int > (w + 2, 0));

        queue < pair < int, int > > q;
        q.push({0, 0});
        vi[0][0] = 1;
        int ans{0};
        int dx[]{-1, 1, 0, 0};
        int dy[]{0, 0, 1, -1};

        while (!q.empty()) {
            auto [x, y]{q.front()}; q.pop();

            for (int i{0}; i < 4; i++) {
                int nx{x + dx[i]}, ny{y + dy[i]};
                if (nx < 0 || ny < 0 || nx > h + 1 || ny > w + 1) continue;
                if (vi[nx][ny]) continue;

                char c{board[nx][ny]};

                if (c == '*') continue;

                if ('A' <= c && c <= 'Z') {
                    int idx{c - 'A'};
                    if (!hak[idx]) {
                        wad[idx].push_back({nx, ny});
                        continue;
                    }
                }

                if ('a' <= c && c <= 'z') {
                    int idx{c - 'a'};
                    if (!hak[idx]) {
                        hak[idx] = true;

                        for (auto &p : wad[idx]) {
                            int wx{p.first}, wy{p.second};
                            if (!vi[wx][wy]) {
                                vi[wx][wy] = 1;
                                q.push(p);
                            }
                        }

                        wad[idx].clear();
                    }

                    board[nx][ny] = '.';
                }

                if (c == '$') {
                    ans ++;
                    board[nx][ny] = '.';
                }

                vi[nx][ny] = 1;
                q.push({nx, ny});
            }
        }

        cout << ans << '\n';
    }       

    return 0;
}
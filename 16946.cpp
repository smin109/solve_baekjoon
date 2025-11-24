#include <bits/stdc++.h>
using namespace std;

int dx[]{-1, 1, 0, 0};
int dy[]{0, 0, 1, -1};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector < string > grid(n);
    for (int i{0}; i < n; i++) cin >> grid[i];

    vector < vector < int > > comp(n, vector < int > (m, -1));
    vector < int > comps;
    comps.push_back(0);

    int id{0};

    for (int i{0}; i < n; i++) {
        for (int j{0}; j < m; j++) {
            if (grid[i][j] == '0' && comp[i][j] == -1) {
                id++;
                int cnt{0};
                queue < pair < int, int > > q;
                q.push({i, j});
                comp[i][j] = id;

                while (!q.empty()) {
                    auto [x, y]{q.front()}; q.pop();
                    cnt++;

                    for (int k{0}; k < 4; k++) {
                        int nx{x + dx[k]}, ny{y + dy[k]};
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                        if (grid[nx][ny] == '0' && comp[nx][ny] == -1) {
                            comp[nx][ny] = id;
                            q.push({nx, ny});
                        }
                    }
                }

                comps.push_back(cnt);
            }
        }
    }

    string outp;
    outp.reserve(m);
    for (int i{0}; i < n; i++) {
        outp.clear();
        for (int j{0}; j < m; j++) {
            if (grid[i][j] == '0') {
                outp.push_back('0');
            } else {
                int ids[4], cn{0}, su{1};

                for (int k{0}; k < 4; k++) {
                    int nx{i + dx[k]}, ny{j + dy[k]};
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

                    if (grid[nx][ny] == '0') {
                        int cid{comp[nx][ny]};
                        bool du{false};
                        for (int l{0}; l < cn; l++) {
                            if (ids[l] == cid) { du = true; break; }
                        }
                        if (!du) {
                            ids[cn++] = cid;
                            su += comps[cid];
                        }
                    }
                }

                outp.push_back(char('0' + (su % 10)));
            }
        }
        cout << outp << '\n';
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct shark {
    int r, c, s, d, z;
    bool alive;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int r, c, m;
    cin >> r >> c >> m;

    vector < shark > sha(m + 1);
    vector < vector < int > > grid(r + 1, vector < int >(c + 1, 0));

    for (int i{1}; i <= m; i++) {
        int r, c, s, d, z; cin >> r >> c >> s >> d >> z;
        sha[i] = {r, c, s, d, z, true};
        grid[r][c] = i;
    }

    int ans{0};

    for (int col{1}; col <= c; col++) {
        for (int row{1}; row <= r; row++) {
            int idx{grid[row][col]};
            if (idx != 0 && sha[idx].alive) {
                sha[idx].alive = false;
                ans += sha[idx].z;
                grid[row][col] = 0;
                break;
            }
        }

        vector < vector < int > > newg(r + 1, vector < int > (c + 1, 0));

        for (int i{1}; i <= m; i++) {
            if (!sha[i].alive) continue;

            int r{sha[i].r}, c{sha[i].c}, s{sha[i].s}, d{sha[i].d}, z{sha[i].z};

            int nr{r}, nc{c}, nd{d};

            if (d == 1 || d == 2) {
                int cy{2 * (r - 1)};
                int move{(cy == 0 ? 0 : s % cy)};
                for (int j{0}; j < move; j++) {
                    if (nr == 1 && nd == 1) nd = 2;
                    else if (nr == r && nd == 2) nd = 1;

                    if (nd == 1) nr--;
                    else nr++;
                }
            } else {
                int cy{2 * (c - 1)};
                int move{(cy == 0 ? 0 : s % cy)};
                for (int j{0}; j < move; j++) {
                    if (nc == 1 && nd == 4) nd = 3;
                    else if (nc == c && nd == 3) nd = 4;

                    if (nd == 3) nc++;
                    else nc--;
                }
            }

            sha[i].r = nr;
            sha[i].c = nc;
            sha[i].d = nd;

            if (newg[nr][nc] == 0) {
                newg[nr][nc] = i;
            } else {
                int ot{newg[nr][nc]};
                if (sha[ot].z < z) {
                    sha[ot].alive = false;
                    newg[nr][nc] = i;
                } else {
                    sha[i].alive = false;
                }
            }
        }

        grid.swap(newg);
    }

    cout << ans;
    return 0;
}

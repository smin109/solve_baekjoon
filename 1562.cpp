#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1'000'000'000;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    static int dp[101][10][1 << 10];

    if (n < 10) {
        cout << 0;
        return 0;
    }

    for (int i{1}; i <= 9; i++) {
        int mas{1 << i};
        dp[1][i][mas] = 1;
    }

    for (int i{1}; i < n; i++) {
        for (int j{0}; j <= 9; j++) {
            for (int mas{0}; mas < (1 << 10); mas++) {
                int cur{dp[i][j][mas]};
                if (!cur) continue;

                if (j > 0) {
                    int nd{j - 1};
                    int nm{mas | (1 << nd)};
                    ll val{dp[i + 1][nd][mas] + cur};
                    if (val >= MOD) val -= MOD;
                    dp[i + 1][nd][nm] = (int)val;
                }

                if (j < 9) {
                    int nd{j + 1};
                    int nm{mas | (1 << nd)};
                    ll val {dp[i + 1][nd][nm] + cur};
                    if (val >= MOD) val -= MOD;
                    dp[i + 1][nd][nm] = (int)val;
                }
            }
        }
    }

    int f{(1 << 10) - 1};
    int ans{0};
    for (int i{0}; i <= 9; i++) {
        ans += dp[n][i][f];
        if (ans >= MOD) ans -= MOD;
    }
    
    cout << ans;

    return 0;
}
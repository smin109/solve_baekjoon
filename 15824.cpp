#include<bits/stdc++.h>
using namespace std;
static const long long MOD = 1'000'000'007LL;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector < long long > a(n);
    for (int i{0}; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    vector < long long > pow2(n + 1, 1);
    for (int i{1}; i <= n; i++) pow2[i] = (pow2[i - 1] * 2) % MOD;

    long long ans{0};

    for (int i{0}; i < n; i++) {
        long long macnt{pow2[i]};
        long long micnt{pow2[n - 1 - i]};
        long long coef{(macnt - micnt) % MOD};

        long long val{a[i] % MOD};
        ans = (ans + val * coef) % MOD;
    }

    if (ans < 0) ans += MOD;
    cout << ans;

    return 0;
}
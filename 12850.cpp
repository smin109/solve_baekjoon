#include<bits/stdc++.h>
using namespace std;

static const long long MOD = 1'000'000'007;
static const int n = 8;

using Mat = array < array < long long, n >, n >;

Mat mul(const Mat& a, const Mat& b) {
    Mat c{};
    for (int i{0}; i < n; i++) {
        for (int j{0}; j < n; j++) {
            if (a[i][j] == 0) continue;
            long long aij{a[i][j]};
            for (int k{0}; k < n; k++) {
                c[i][k] = (c[i][k] + aij * b[j][k]) % MOD;
            }
        }
    }

    return c;
}

Mat mpow(Mat base, long long exp) {
    Mat res{};

    for (int i{0}; i < n; i++) res[i][i] = 1;

    while (exp > 0) {
        if (exp & 1) res = mul(res, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    long long d; cin >> d;       

    Mat a = {{
        {{0, 1, 1, 0, 0, 0, 0, 0}},
        {{1, 0, 1, 1, 0, 0, 0, 0}},
        {{1, 1, 0, 1, 1, 0, 0, 0}},
        {{0, 1, 1, 0, 1, 1, 0, 0}},
        {{0, 0, 1, 1, 0, 1, 1, 0}},
        {{0, 0, 0, 1, 1, 0, 0, 1}},
        {{0, 0, 0, 0, 1, 0, 0, 1}},
        {{0, 0, 0, 0, 0, 1, 1, 0}}
    }};

    Mat ad{mpow(a, d)};
    cout << ad[0][0] % MOD;

    return 0;
}
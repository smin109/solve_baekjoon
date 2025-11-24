#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;

    vector < int > A(M + 1), B(M + 1);
    for (int j{1}; j <= M; j++) cin >> A[j] >> B[j];

    vector < int > ground_h(M + 1);
    for (int j{1}; j <= M; j++) {
        if (A[j] > 0 && B[j] == N) ground_h[j] = N - A[j] + 1;
        else ground_h[j] = 0;
    }

    vector < int > lmax(M + 1), rmax(M + 2);
    int cur{0};
    for (int j{1}; j <= M; j++) {
        cur = max(cur, ground_h[j]);
        lmax[j] = cur;
    }

    cur = 0;
    
    for (int j{M}; j >= 1; j--) {
        cur = max(cur, ground_h[j]);
        rmax[j] = cur;
    }

    vector <int > w_base(M + 1);
    ll base_sum{0};
    for (int j{1}; j <= M; j++) {
        int w{min(lmax[j], rmax[j]) - ground_h[j]};
        if (w < 0) w = 0;
        w_base[j] = w;
        base_sum += w;
    }

    vector < char > isFloat(M + 1, 0);
    for (int j = 1; j <= M; j++) if (A[j] > 0 && B[j] > 0 && B[j] < N) isFloat[j] = 1;

    vector < int > parent(M + 1), rnk(M + 1, 0);
    iota(parent.begin(), parent.end(), 0);

    function < int(int) > findp = [&](int x) {
        if (parent[x] == x) return x;
        return parent[x] = findp(parent[x]);
    };

    auto unite = [&](int x, int y) {
        x = findp(x);
        y = findp(y);
        if (x == y) return;
        if (rnk[x] < rnk[y]) swap(x, y);
        parent[y] = x;
        if (rnk[x] == rnk[y]) rnk[x]++;
    };

    for (int j{1}; j < M; j++) {
        if (isFloat[j] && isFloat[j + 1]) {
            int L = max(A[j], A[j + 1]);
            int R = min(B[j], B[j + 1]);
            if (L <= R) unite(j, j + 1);
        }
    }

    vector < vector < int > > comp(M + 1);
    for (int j{1}; j <= M; j++) {
        if (isFloat[j]) {
            int rt = findp(j);
            comp[rt].push_back(j);
        }
    }

    vector < int > w_top(M + 1, 0);
    ll float_sum{0};

    for (int rt{1}; rt <= M; rt++) {
        auto &cols = comp[rt];
        if (cols.empty()) continue;

        sort(cols.begin(), cols.end());
        int k{(int)cols.size()};
        vector < int > h(k), lm(k), rm(k);

        for (int i{0}; i < k; i++) {
            int j{cols[i]};
            int z_top{N - A[j] + 1};
            h[i] = z_top;
        }

        int c{0};
        for (int i{0}; i < k; i++) {
            c = max(c, h[i]);
            lm[i] = c;
        }

        c = 0;
        
        for (int i{k - 1}; i >= 0; i--) {
            c = max(c, h[i]);
            rm[i] = c;
        }

        for (int i{0}; i < k; i++) {
            int j{cols[i]};
            int w{min(lm[i], rm[i]) - h[i]};
            if (w < 0) w = 0;
            w_top[j] = w;
            float_sum += w;
        }
    }

    ll inter{0};
    for (int j{1}; j <= M; j++) {
        if (!isFloat[j]) continue;
        if (w_base[j] == 0) continue;

        int g = ground_h[j];
        int z1 = g + 1;
        int z2 = g + w_base[j];

        int z_bot = N - B[j] + 1;
        int z_top = N - A[j] + 1;
        int z_occ_hi = z_top + w_top[j];

        int lo = max(z1, z_bot);
        int hi = min(z2, z_occ_hi);
        if (lo <= hi) inter += (ll)(hi - lo + 1);
    }

    ll ans = base_sum - inter + float_sum;
    cout << ans;

    return 0;
}

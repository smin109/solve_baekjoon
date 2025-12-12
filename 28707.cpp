#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 60);

struct Op {
    int l, r, c;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector < int > a(n), b;
    for (int i{0}; i < n; i++) cin >> a[i];
    b = a;
    sort(b.begin(), b.end());

    int m; cin >> m;
    vector < Op > ops(m);
    for (int i{0}; i < m; i++) {
        int l, r, c; cin >> l >> r >> c;
        --l; --r;
        ops[i] = {l, r, c};
    }

    vector < int > pow11(n + 1, 1);
    for (int i{1}; i <= n; i++) pow11[i] = pow11[i - 1] * 11;

    auto encode = [&](const vector < int >& v) -> int {
        int code{0};
        for (int i{0}; i < n; i++) code += v[i] * pow11[i];
        return code;
    };

    auto digit = [&](int code, int idx) -> int {
        return (code / pow11[idx]) % 11;
    };

    int st{encode(a)}, ed{encode(b)};
    
    if (st == ed) {
        cout << 0 << '\n';
        return 0;
    }

    unordered_map < int, ll > dist;
    dist.reserve(60000);

    priority_queue < pair < ll, int >, vector < pair < ll, int > >, greater < pair < ll, int > > > pq;
    dist[st] = 0;
    pq.push({0, st});

    while (!pq.empty()) {
        auto [d, co]{pq.top()}; pq.pop();
        auto it{dist.find(co)};

        if (it == dist.end() || it -> second != d) continue;

        if (co == ed) {
            cout << d << '\n';
            return 0;
        }

        for (const auto& e : ops) {
            int dl{digit(co, e.l)}, dr{digit(co, e.r)};
            if (dl == dr) continue;

            int nco{co + (dr - dl) * pow11[e.l] + (dl - dr) * pow11[e.r]};
            ll nd{d + e.c};
            auto jt{dist.find(nco)};

            if (jt == dist.end() || nd < jt->second) {
                dist[nco] = nd;
                pq.push({nd, nco});
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}

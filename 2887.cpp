#include<bits/stdc++.h>
using namespace std;

struct DSU {
    vector < int > p, r;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }
    int fi(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    bool uni(int a, int b) {
        a = fi(a); b = fi(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

struct Planet {
    int id;
    long long x, y, z;
};

struct Edge {
    int u, v;
    long long w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector < Planet > a(n);
    for (int i{0}; i < n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].z;
        a[i].id = i;
    }

    vector < Edge > ed;
    ed.reserve(max(0, 3 * (n - 1)));

    auto added = [&](auto keyg) {
        vector < Planet > v = a;
        sort(v.begin(), v.end(), [&](const Planet& p1, const Planet& p2) {
            return keyg(p1) < keyg(p2);
        });
        for (int i{0}; i + 1 < n; i++) {
            const auto &p{v[i]}, &q{v[i + 1]};
            long long dx = llabs(p.x - q.x);
            long long dy = llabs(p.y - q.y);
            long long dz = llabs(p.z - q.z);
            long long w = min({dx, dy, dz});
            ed.push_back({p.id, q.id, w});
        }
    };

    added([](const Planet &p) {return p.x; });
    added([](const Planet &p) {return p.y; });
    added([](const Planet &p) {return p.z; });

    sort(ed.begin(), ed.end());

    DSU dsu(n);
    long long ans{0};
    int cnt{0};

    for (const auto &e : ed) {
        if (dsu.uni(e.u, e.v)) {
            ans += e.w;
            if (++cnt == n - 1) break;
        }
    }

    cout << ans;

    return 0;
}
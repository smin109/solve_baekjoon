#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;
    
    vector < int > cand(n + 1);

    for (int i{0}; i < n; i++) cin >> cand[i + 1];

    vector < vector < int > > adj(n + 1);
    for (int i{0}; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector < int > comps, compc;
    vector < int > vi(n + 1, 0);

    for (int i{1}; i <= n; i++) {
        if (vi[i]) continue;
        queue < int > q;
        q.push(i);
        vi[i] = 1;
        int si{0}, sc{0};

        while (!q.empty()) {
            int u{q.front()}; q.pop();
            si++;
            sc += cand[u];
            for (int v : adj[u]) if (!vi[v]) {
                vi[v] = 1;
                q.push(v);
            }
        }

        comps.push_back(si);
        compc.push_back(sc);
    }

    int cap{k - 1};
    if (cap < 0) cap = 0;

    vector < int > dp(cap + 1, 0);

    int g{comps.size()};
    for (int i{0}; i < g; i++) {
        int si{comps[i]}, val{compc[i]};

        if (si > cap) continue;

        for (int j{cap}; j >= si; j--) {
            dp[j] = max(dp[j], dp[j - si] + val);
        }
    }

    cout << dp[cap];

    return 0;
}
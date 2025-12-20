#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;

    vector < int > card(m);
    for (int i{0}; i < m; i++) cin >> card[i];
    sort (card.begin(), card.end());

    vector < int > pa(m + 1);
    for (int i{0}; i <= m; i++) pa[i] = i;

    auto findp = [&](int x) {
        while (pa[x] != x) {
            pa[x] = pa[pa[x]];
            x = pa[x];
        }
        return x;
    };

    string out;
    out.reserve(k * 8);

    for (int t{0}; t < k; t++) {
        int x; cin >> x;

        int idx{upper_bound(card.begin(), card.end(), x) - card.begin()};
        int use{findp(idx)};

        out += to_string(card[use]);
        out += '\n';

        pa[use] = findp(use + 1);
    }

    cout << out;

    return 0;
}
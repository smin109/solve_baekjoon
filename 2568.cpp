#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector < pair < int, int > > li(n);

    for (int i{0}; i < n; i++) cin >> li[i].first >> li[i].second;
    
    sort(li.begin(), li.end());

    vector < int > lis, lis_ind, pa(n, -1);

    lis.reserve(n);
    lis_ind.reserve(n);

    for (int i{0}; i < n; i++) {
        int b{li[i].second};
        int pos{lower_bound(lis.begin(), lis.end(), b) - lis.begin()};

        if (pos > 0) pa[i] = lis_ind[pos - 1];

        if (pos == (int)lis.size()) {
            lis.push_back(b);
            lis_ind.push_back(i);
        } else {
            lis[pos] = b;
            lis_ind[pos] = i;
        }
    }

    int l{(int)lis.size()};
    int rem{n - l};
    cout << rem << '\n';

    vector < char > ke(n, 0);
    int cur{lis_ind.back()};
    while (cur != -1) {
        ke[cur] = 1;
        cur = pa[cur];
    }

    for (int i{0}; i < n; i++) if (!ke[i]) cout << li[i].first << '\n';

    return 0;
}
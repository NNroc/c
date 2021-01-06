#include <bits/stdc++.h>

#define ll long long
using namespace std;
ll mp[1010][1010];
struct node {
    ll ox, oy, oox, ooy;
} square[1010];
ll repeat[1000010];

int main() {
    int n, num = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> square[i].ox >> square[i].oy >> square[i].oox >> square[i].ooy;
    }
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            node a = square[i];
            node b = square[j];
            if (a.ooy <= b.oy || a.oy >= b.ooy
                || a.oox <= b.ox || a.ox >= b.oox) {
                repeat[++num] = 0;
                continue;
            }
            ll h, w;
            ll use[5];
            use[1] = a.oy, use[2] = a.ooy, use[3] = b.oy, use[4] = b.ooy;
            sort(use + 1, use + 5);
            h = use[3] - use[2];
            use[1] = a.ox, use[2] = a.oox, use[3] = b.ox, use[4] = b.oox;
            sort(use + 1, use + 5);
            w = use[3] - use[2];
            repeat[++num] = h * w;
        }
    }
    sort(repeat + 1, repeat + 1 + num);
    cout << "------\n";
    for (int i = 1; i <= num; i++) {
        cout << repeat[i] << endl;
    }
    cout << "------\n";
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        int l = 1, r = num;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (repeat[mid] <= k) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        cout << num - l << endl;
    }
}
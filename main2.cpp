#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int maxN = 1e7 + 5;
int dp[maxN];

int main() {
    ll n, k, T, a, b, c, p;
    cin >> n >> k >> T >> a >> b >> c >> p;
    for (int i = 1; i <= n; ++i) {
        a = (a * b + c) % p;
        dp[i] = dp[i - 1];
        if (a >= T) {
            dp[i] += 1;
        }
    }

    ll l = 1, r = k, ans = 0;
    while (1) {
        while (r <= n && dp[r] - dp[l - 1] < k) {
            ++r;
        }
        if (r > n) {
            break;
        }
        ans += n - r + 1;
        ++l;
    }
    cout << ans << "\n";
    return 0;
}
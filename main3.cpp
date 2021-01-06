#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;
const int N = 5e5 + 7;
int dfn[N], low[N], indegree[N], tot, cnt, val[N], cost[N], dp[N];
bool bar[N], ok[N];
vector<int> mp[N], strongly_connected[N], mp1[N];
stack<int> sta;

void dfs(int u) {
    dfn[u] = low[u] = ++tot;
    sta.push(u);
    for (int i = 0; i < mp[u].size(); i++) {
        int v = mp[u][i];
        if (!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (!indegree[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ++cnt;
        while (1) {
            int x = sta.top();
            sta.pop();
            indegree[x] = cnt;
            strongly_connected[cnt].push_back(x);
            if (u == x)break;
        }
    }
}

void dfs1(int u) {
    if (dp[u] != -1)return;
    int ans = cost[u];
    for (int i = 0; i < mp1[u].size(); i++) {
        int v = mp1[u][i];
        dfs1(v);
        if (ok[v]) {
            ans = max(ans, dp[v] + cost[u]);
            ok[u] = 1;
        }
    }
    dp[u] = ans;
}

int main() {
    int n, m, s, p;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        mp[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)scanf("%d", &val[i]);
    scanf("%d %d", &s, &p);
    for (int i = 0; i < p; i++) {
        int v;
        scanf("%d", &v);
        bar[v] = 1;
    }
    dfs(s);
    for (int i = 1; i <= cnt; i++) {
        for (int j = 0; j < strongly_connected[i].size(); j++) {
            int u = strongly_connected[i][j];
            cost[i] += val[u];
            if (bar[u])ok[i] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < mp[i].size(); j++) {
            int v = mp[i][j];
            if (indegree[v] != indegree[i])mp1[indegree[i]].push_back(indegree[v]);
        }
    }
    memset(dp, -1, sizeof(dp));
    dfs1(indegree[s]);
    printf("%d\n", dp[indegree[s]]);
}

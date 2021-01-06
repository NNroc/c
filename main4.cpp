#include <bits/stdc++.h>

#define maxn 100010
using namespace std;
int n, m;
int cnt;// 记录强连通分量的个数
int vis_num;// 遍历的步数
int dfn[maxn];// 记录元素第一次被访问的步数
int low[maxn];// 包含i的强连通分量最早被访问的步数
int indegree[maxn];// i从属的强连通分量，不同的强连通分量值不同，缩点使用
stack<int> s;
int val[maxn];// 第i个位置的钱数
int st;// 起点
int bar_num;// 酒吧数量
int bar[maxn];// 酒吧位置
int cost[maxn], ok[maxn], dp[maxn];
// 存边
vector<int> mp[maxn], mp1[maxn];
// 记录强连通分量里的点及个数
vector<int> strongly_connected[maxn];

void tarjan(int u) {
    int v;
    dfn[u] = low[u] = ++vis_num;
    // 入栈
    s.push(u);
    for (int i = 0; i < mp[u].size(); i++) {
        // 下一个访问的点
        v = mp[u][i];
        if (!dfn[v]) {
            tarjan(v);
            // 判断u是否为v的子节点
            low[u] = min(low[u], low[v]);
        } else if (!indegree[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    // u为强连通分量的根
    if (dfn[u] == low[u]) {
        // 强连通分量的个数+1
        cnt++;
        // 退栈
        while (1) {
            // v 该强连通分量成员
            v = s.top();
            s.pop();
            indegree[v] = cnt;
            strongly_connected[cnt].push_back(v);
            if (u == v) {
                break;
            }
        }
    }
}

int main() {
    int u, v;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        mp[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        //i没被访问过了
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    int ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (strongly_connected[i].size() > 1) {
            ans++;
        }
    }
    // ans 组强连通分量（至少两个点）
    printf("%d\n", ans);
    return 0;
}
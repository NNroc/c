#include <bits/stdc++.h>

#define maxn 100010
using namespace std;
int n, m;
int cnt;// ��¼ǿ��ͨ�����ĸ���
int vis_num;// �����Ĳ���
int dfn[maxn];// ��¼Ԫ�ص�һ�α����ʵĲ���
int low[maxn];// ����i��ǿ��ͨ�������类���ʵĲ���
int indegree[maxn];// i������ǿ��ͨ��������ͬ��ǿ��ͨ����ֵ��ͬ������ʹ��
stack<int> s;
int val[maxn];// ��i��λ�õ�Ǯ��
int st;// ���
int bar_num;// �ư�����
int bar[maxn];// �ư�λ��
int cost[maxn], ok[maxn], dp[maxn];
// ���
vector<int> mp[maxn], mp1[maxn];
// ��¼ǿ��ͨ������ĵ㼰����
vector<int> strongly_connected[maxn];

void tarjan(int u) {
    int v;
    dfn[u] = low[u] = ++vis_num;
    // ��ջ
    s.push(u);
    for (int i = 0; i < mp[u].size(); i++) {
        // ��һ�����ʵĵ�
        v = mp[u][i];
        if (!dfn[v]) {
            tarjan(v);
            // �ж�u�Ƿ�Ϊv���ӽڵ�
            low[u] = min(low[u], low[v]);
        } else if (!indegree[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    // uΪǿ��ͨ�����ĸ�
    if (dfn[u] == low[u]) {
        // ǿ��ͨ�����ĸ���+1
        cnt++;
        // ��ջ
        while (1) {
            // v ��ǿ��ͨ������Ա
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
        //iû�����ʹ���
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
    // ans ��ǿ��ͨ���������������㣩
    printf("%d\n", ans);
    return 0;
}
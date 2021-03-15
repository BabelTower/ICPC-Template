/*
树上查询问题，满足两个特征：
1. 只有对子树的查询
2. 没有修改
模版: CF-600E 统计子树中个数最多的颜色
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int c[maxn], sz[maxn], son[maxn];
ll ans[maxn], now;
int cnt[maxn], mx, Son;
vector<int> g[maxn];
void add(int u, int f, int val) {
    cnt[c[u]] += val;
    if(mx < cnt[c[u]]) mx = cnt[c[u]], now = c[u];
    else if(mx == cnt[c[u]]) now += (ll)c[u];
    for (auto v : g[u]) {
        if(v == f || v == Son) continue;
        add(v, u, val);
    }
}
void dfs1(int u, int f) {
    sz[u] = 1;
    for (auto v : g[u]) {
        if(v == f) continue;
        dfs1(v, u);
        if(sz[son[u]] < sz[v]) son[u] = v;
        sz[u] += sz[v];
    }
}
void dfs2(int u, int f, int opt) {
    for (auto v : g[u]) {
        if(v == f || v == son[u]) continue;
        dfs2(v, u, 0);
    }
    if(son[u]) dfs2(son[u], u, 1), Son = son[u];
    add(u, f, 1); Son = 0;
    ans[u] = now;
    if(!opt) add(u, f, -1), mx = 0, now = 0;
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0, 0);
    for (int i = 1; i <= n; i++) printf("%lld%c", ans[i], i<n?' ':'\n');
}

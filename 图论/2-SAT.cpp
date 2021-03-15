/*
2-SAT，简单的说就是给出n个集合，每个集合有两个元素，已知若干个<a,b>，表示a与b矛盾（其中a与b属于不同的集合）。然后从每个集合选择一个元素，判断能否一共选n个两两不矛盾的元素。
*/
const int N = 2e6 + 5;
int low[N], dfn[N], ins[N], color[N];
stack<int> stk;
vector<int> g[N];
int sccCnt, dfsClock, n, m;
// 注意所有东西都要开两倍空间，因为每个变量存了两次
void tarjan(int u) {
    low[u] = dfn[u] = ++dfsClock;
    stk.push(u); ins[u] = true;
    for (const auto &v : g[u]) {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++sccCnt;
        do {
            color[u] = sccCnt;
            u = stk.top(); stk.pop(); ins[u] = false;
        } while (low[u] != dfn[u]);
    }
}
int main() {
	n = read(), m = read();
	for (int i = 0; i < m; ++i) {
	    int a = read(), va = read(), b = read(), vb = read();
	    g[a + n * (va & 1)].push_back(b + n * (vb ^ 1));
	    g[b + n * (vb & 1)].push_back(a + n * (va ^ 1));
	}
	// Tarjan 找环，得到的 color[x] 是 x 所在的 scc 的拓扑逆序。
	for (int i = 1; i <= (n << 1); ++i) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; ++i)
    if (color[i] == color[i + n]) { // x 与 -x 在同一强连通分量内，一定无解
        puts("IMPOSSIBLE");
        exit(0);
    }
	puts("POSSIBLE");
	for (int i = 1; i <= n; ++i)
	    printf("%d%c",(color[i] < color[i + n]),i<n?' ':'\n'); 
        // 如果不使用 Tarjan 找环，请改成大于号
}
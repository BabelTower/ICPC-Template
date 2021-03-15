/*
* 题目: [POI2008]STA-Station
* URL: https://www.luogu.com.cn/problem/P3478
* 树形 DP 中的换根 DP 问题又被称为二次扫描，通常不会指定根结点，并且根结点的变化会对一些值，例如子结点深度和、点权和等产生影响。
* 通常需要两次 DFS，第一次 DFS 预处理诸如深度，点权和之类的信息，在第二次 DFS 开始运行换根动态规划。
* 换根解决的是“不定根”的树形dp问题。该类题目的特点是：给定一个树形结构，需要以每个节点为根进行一系列统计。
* 方法为两次扫描来求解：
* 第一次扫描时，任选一个点为根，在“有根树”上执行一次树形dp，在回溯时，自底向上的状态转移。
* 第二次扫描时，从第一次选的根出发，对整根树执行一个dfs，在每次递归前进行自顶向下的转移，计算出换根后的解。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
vector<int> e[N];
ll sz[N], sum[N], f[N];
int n;
void dfs1(int u, int fa) {
	sz[u] = 1; sum[u] = 0;
	for (auto v : e[u]) {
		if(v == fa) continue;
		dfs1(v, u);
		sz[u] += sz[v];
		sum[u] += sum[v] + sz[v];
	}
}
void dfs2(int u, int fa) {
	for (auto v : e[u]) {
		if(v == fa) continue;
		f[v] = f[u] + n - 2 * sz[v];
		dfs2(v, u);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1, 0);
	f[1] = sum[1];
	dfs2(1, 0);
	int ans = 1;
	for (int i = 1; i <= n; i++) if(f[i] > f[ans]) ans = i;
	printf("%d\n", ans);
}
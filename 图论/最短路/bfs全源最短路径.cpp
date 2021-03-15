/*
* 模版: bfs全源最短路径（边权为1）
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5; // 节点个数
const int M = 1e5 + 5; // 边的个数
const int inf = 0x3f3f3f3f;

int head[N], to[M], nex[M], val[M], cnt; // 链式前向星
inline void add(int u, int v, int w) {
	to[++cnt] = v;
	val[cnt] = w;
	nex[cnt] = head[u];
	head[u] = cnt;
}

int Dis[N][N], n, m, q;
bool vis[N];

void bfs(int S) {
	int *dis = Dis[S];
	for (int i = 1; i <= n; i++) vis[i] = 0, dis[i] = inf;
	queue<int> Q;
	Q.push(S);
	vis[S] = 1;
	dis[S] = 0;
	while(!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (int i = head[now]; i; i = nex[i]) {
			int v = to[i];
			if(vis[v]) continue;
			vis[v] = 1;
			Q.push(v);
			dis[v] = dis[now] + 1;
		}
	}
}

const int Q = 1e6 + 5;
int c[Q], d[Q], t[Q];
int main() {
	freopen("ysys.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v, 1);
		add(v, u, 1);
	}

	for (int i = 1; i <= n; i++) {
		bfs(i);
	}

	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= n; j++) {
	// 		printf("%d-%d:%d\n", i, j, Dis[i][j]);
	// 	}
	// }
}
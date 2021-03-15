/*
* 题目: Monster Hunter
* URL: https://ac.nowcoder.com/acm/contest/10272/M
* 说明: 填表TLE，刷表AC
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e3 + 5;
int pa[N], hp[N], sz[N];
vector<int> g[N];
ll dp[N][N][2], tmp[N][2];
template<typename T>
void Min(T &x, T y) {
	if(x > y) {
		x = y;
	}
}

void dfs(int u) {
	sz[u] = 1;
	
	dp[u][0][1] = hp[u]; dp[u][1][0] = 0;

	for (auto v : g[u]) {
		dfs(v);
		
		for (int i = 0; i <= sz[u] + sz[v]; i++) {
			tmp[i][0] = tmp[i][1] = 1e15;
		}

		for (int i = 0; i <= sz[u]; i++) {
			for (int j = 0; j <= sz[v]; j++) {
				Min(tmp[i+j][0], dp[u][i][0] + min(dp[v][j][0], dp[v][j][1]));
				Min(tmp[i+j][1], dp[u][i][1] + dp[v][j][0]);
				Min(tmp[i+j][1], dp[u][i][1] + dp[v][j][1] + hp[v]);
			}
		}
		
		sz[u] += sz[v];

		for (int i = 0;  i <= sz[u]; i++) {
			dp[u][i][0] = tmp[i][0];
			dp[u][i][1] = tmp[i][1];
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {

		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			g[i].clear();
			sz[i] = 0;
			for (int j = 0; j <= n; j++) dp[i][j][0] = dp[i][j][1] = 1e15;
		}

		for (int i = 2; i <= n; i++) {
			scanf("%d", &pa[i]);
			g[pa[i]].push_back(i);
		}

		for (int i = 1; i <= n; i++) {
			scanf("%d", &hp[i]);
		}

		dfs(1);

		for (int i = 0; i <= n; i++) {
			printf("%lld%c", min(dp[1][i][0], dp[1][i][1]), i==n?'\n':' ');
		}
	} 
}
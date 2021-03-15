/*
* 题目: P1725 琪露诺
* URL: https://www.luogu.com.cn/problem/P1725
* 状态转移公式: f[i] = max{f[j] + a[i]} (i-r <= j <= i-l)
*/
#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 2e5 + 5;
int a[N], dp[N];
int Q[N], h, t; // 队列, head, tail
int main() {
	fill(dp, dp+N, -inf);
	int n, l, r;
	scanf("%d%d%d", &n, &l, &r);
	for (int i = 0; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	h = 0, t = -1;
	Q[++t] = 0; dp[0] = a[0];
	for (int i = l; i <= n; i++) {
		while(h <= t && dp[Q[t]] <= dp[i-l]) t--;
		Q[++t] = i-l;
		while(h <= t && Q[h] < i-r) h++;
		dp[i] = dp[Q[h]] + a[i];
	}
	int mx = -inf;
	for (int i = n-r+1; i <= n; i++) mx = max(mx, dp[i]);
	printf("%d\n", mx);
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e4 + 5;
int c[N];
ll sum[N], f[N];
int n, L;
struct node {
	int l, r, x;
} stk[N];
int stk_top;
inline ll w(int i, int j) {
	ll res = j - i - 1 - L; 
	res += sum[j] - sum[i];
	return res * res;
}
inline ll calc(int i, int j) {
	return f[i] + w(i, j);
}
inline int find(int i) {
	int l = stk[stk_top].l, r = stk[stk_top].r;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(calc(i, mid) < calc(stk[stk_top].x, mid)) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return l;
}
int main() {
	scanf("%d%d", &n, &L);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
		sum[i] = sum[i-1] + c[i];
	}
	int cur = 0;
	stk[cur] = {1, n, 0};
	for (int i = 1; i <= n; i++) {
		f[i] = calc(stk[cur].x, i);
		while(i < stk[stk_top].l && calc(i, stk[stk_top].l) < calc(stk[stk_top].x , stk[stk_top].l)) stk_top--;
		int l = find(i); stk[stk_top].r = l - 1;
		if(l <= n) stk[++stk_top] = {l, n, i};
		if(i == stk[cur].r) cur++;
	}
	printf("%lld\n", f[n]);
}
/* 
* 题目: [POI2011]Lightning Conductor
* URL: https://www.luogu.com.cn/problem/P3515
* 说明: 此题中没有限制决策点j的范围，故需正反都来一遍
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
int a[N];
double sq[N], f[N], g[N];
double w(int l, int r) {
    return a[l] + sq[r-l] - a[r];
}
void solve(int l, int r, int kl, int kr, double dp[]) {
    int mid = (l+r) >> 1, k = kl;
    for (int i = kl; i <= min(kr, mid); i++) {
        if(w(i, mid) > w(k, mid)) k = i;
    }
    dp[mid] = w(k, mid);
    if(l < mid) solve(l, mid-1, kl, k, dp);
    if(r > mid) solve(mid+1, r, k, kr, dp);
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 0; i <= n; i++) sq[i] = sqrt(i);
    solve(1, n, 1, n, f);
    reverse(a+1, a+n+1);
    solve(1, n, 1, n, g);
    for (int i = 1; i <= n; i++) {
        printf("%lld\n", (ll)ceil(max(f[i], g[n-i+1])));
    }
}
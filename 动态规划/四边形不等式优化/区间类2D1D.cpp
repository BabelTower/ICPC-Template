/*
* 题目: [NOI1995] 石子合并
* URL: https://www.luogu.com.cn/problem/P1880
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
const int inf = 0x3f3f3f3f;
int a[N], sum[N], f[N][N], m[N][N], g[N][N];
int w(int l, int r) {
    return sum[r] - sum[l-1];
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[i] = sum[i-1] + a[i];
        m[i][i] = i;
    }

    for (int i = n+1; i <= 2*n; i++) {
        a[i] = a[i-n];
        sum[i] = sum[i-1] + a[i];
        m[i][i] = i;
    }
    for (int len = 2; len <= n; ++len) {
        for (int l = 1, r = len; r <= 2*n; l++, r++) {
            f[l][r] = inf;
            g[l][r] = max(g[l+1][r], g[l][r-1]) + w(l, r);
            for (int k = m[l][r-1]; k <= m[l+1][r]; ++k) {
                int tmp = f[l][k] + f[k+1][r] + w(l, r);
                if(f[l][r] > tmp) {
                    f[l][r] = tmp;
                    m[l][r] = k;
                }
            }
        }
    }
    int mx = 0, mn = inf;
    for (int i = 1; i <= n; i++) {
        mn = min(mn, f[i][i+n-1]);
        mx = max(mx, g[i][i+n-1]);
    }
    printf("%d\n", mn);
    printf("%d\n", mx);

}
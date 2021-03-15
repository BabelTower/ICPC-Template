/*
* 模版：dp值从（大小固定的）二维区间的最大值转移过来
* 适用：只要转移的区间满足双指针的性质，都可以用单调队列优化
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 5;
int a[N][N];
int head[N], tail[N], head2, tail2;
struct {
    ll data;
    int id;
}row[N], col[N][N];

ll dp[N][N];
void Max(ll &x, ll y) {
    if(x < y) x = y;
}
int main() {
    memset(dp, -1, sizeof dp);
    int n, m, k, u;
    while(~scanf("%d%d%d%d", &n, &m, &k, &u)) {

        for (int i = 1; i <= m; i++) head[i] = tail[i] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
                dp[i][j] = -1;
            }
        }

        dp[1][1] = a[1][1];

        for (int i = 1; i <= n; i++) {
            head2 = tail2 = 0;
            for (int j = 1; j <= m; j++) {
                while(head[j] < tail[j] && col[j][head[j]].id < i - k) head[j]++;
                while(head2 < tail2 && row[head2].id < j - k) head2++;
                if(a[i][j] > 0) {
                    if(dp[i-1][j-1]!=-1) Max(dp[i][j], dp[i-1][j-1] + a[i][j]);
                    if(dp[i][j-1]!=-1) Max(dp[i][j], dp[i][j-1] + a[i][j]);
                    if(dp[i-1][j]!=-1) Max(dp[i][j], dp[i-1][j] + a[i][j]);
                    if(head[j] < tail[j]) {
                        ll now = col[j][head[j]].data;
                        while(head2 < tail2 && row[tail2-1].data <= now) tail2--;
                        row[tail2++] = {now, j};
                    }
                    if(head2 < tail2) {
                        Max(dp[i][j], row[head2].data + a[i][j] - u);
                    }
                    if(head[j] < tail[j]) {
                        tail2--;
                    }
                }
                if(dp[i][j] >= u) {
                    while(head[j] < tail[j] && dp[i][j] >= col[j][tail[j]-1].data)
                        tail[j]--;
                    col[j][tail[j]++] = {dp[i][j], i};
                }
                if(head[j] < tail[j]) {
                    ll now = col[j][head[j]].data;
                    while(head2 < tail2 && row[tail2-1].data <= now) tail2--;
                    row[tail2++] = {now, j};
                }
            }
        }
        printf("%lld\n", dp[n][m]);
    }
}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int h[N], a[N], b[N], aid, bid;
ll ans = 0;
ll calc(int i, int j) {
    return 1ll  * (h[i] + h[j]) * (j - i);
}
void solve(int l1, int r1, int l2, int r2) {
    if(l1 > r1 || l2 > r2) return ;
    int mid = (l1+r1) >> 1, pos = 0;
    for (int i = l2; i <= r2; i++) {
        if(!pos) pos = i;
        else {
            ll cur1 = calc(a[mid], b[pos]);
            ll cur2 = calc(a[mid], b[i]);
            if(cur2 > cur1) {
                pos = i;
            }
        }
    }
    ans = max(ans, calc(a[mid], b[pos]));
    if(l1 != r1) solve(l1, mid, l2, pos);
    solve(mid+1, r1, pos, r2);
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    for (int i = 1; i <= n; i++) {
        if(!aid || h[i] > h[a[aid]]) {
            a[++aid] = i;
        }
    }
    for (int i = n; i > 0; i--) {
        if(!bid || h[i] > h[b[bid]]) {
            b[++bid] = i;
        }
    }
    reverse(b+1, b+bid+1);
    solve(1, aid, 1, bid);
    printf("%lld\n", ans);
}
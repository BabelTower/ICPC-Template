#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct node {
    int a, b, c, w, ans;
    bool operator < (const node& rhs) const {
        if(a != rhs.a) return a < rhs.a;
        if(b != rhs.b) return b < rhs.b;
        return c < rhs.c;
    }
    bool operator != (const node& rhs) const {
        return (a != rhs.a) || (b != rhs.b) || (c != rhs.c);
    }
}p[N];
bool cmp(const node& x, const node& y) {
    if(x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}
int cnt[N], tr[2*N], n, k, ans[N];
void add(int i, int x) {
    while(i <= k) {
        tr[i] += x;
        i += i & (-i);
    }
}
int query(int i) {
    int res = 0;
    while(i > 0) {
        res += tr[i];
        i -= i & (-i);
    }
    return res;
}
void cdq(int l, int r) {
    if(l == r) return ;
    int m = (l + r) >> 1;
    cdq(l, m); cdq(m+1, r);
    sort(p+l, p+m+1, cmp);
    sort(p+m+1, p+r+1, cmp);
    int i = l, j = m+1;
    for (; j <= r; j++) {
        while (i <= m && p[i].b <= p[j].b) {
            add(p[i].c, p[i].w);
            i++;
        }
        p[j].ans += query(p[j].c);
    }
//    memset(tr, 0, sizeof tr);
    for (--i; i >= l; i--) add(p[i].c, -p[i].w);
}
int main() {
//    freopen("/Users/fangzeyu/Downloads/P3810_2.in", "r", stdin);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
        p[i].w = 1; p[i].ans = 0;
    }
    sort(p+1, p+n+1);
  
    int sz = 1;
    for (int i = 2; i <= n; i++) {
        if(p[i]!= p[sz]) p[++sz] = p[i];
        else p[sz].w++;
    }
//    for (int i = 1; i <= sz; i++) cout << p[i].w << endl;
    cdq(1, sz);
    for (int i = 1; i <= sz; i++) {
        ans[p[i].ans + p[i].w - 1] += p[i].w;
    }
    for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
}
#include <bits/stdc++.h>
using namespace std;
#define rep(a,b,c) for (int a=b;a<=c;a++)
#define per(a,b,c) for (int a=b;a>=c;a--)
#define fi first
#define se second // pair
#define hav(s,p) (s>>(p-1)&1)
#define ins(s,p) (s|1<<(p-1))
#define del(s,p) (s^1<<(p-1)) // state compression
const int N = 12;
const int P = 1e8;
int s[N], sta[1<<N], cnt;
int f[2][1<<N];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	rep(i, 1, n) rep(j, 1, m) {
		int t; scanf("%d", &t);
		if(!t) s[i] = ins(s[i], j);
	}
	int MX = (1<<m) -1;
	rep(st, 0, MX) {
		if(st & (st<<1)) continue;
		sta[++cnt] = st;
	}
	f[0&1][0] = 1;
	rep(i, 1, n) {
		memset(f[i&1], 0, sizeof(f[i&1]));
		rep(j, 1, cnt) {
			if(sta[j] & s[i-1]) continue;
			rep(k, 1, cnt) {
				if(sta[k] & s[i]) continue;
				if(sta[j] & sta[k]) continue;
				f[i&1][sta[k]] = (f[i&1][sta[k]] + f[(i-1)&1][sta[j]]) % P;
			}
		}
	}
	int ans = 0;
	rep(st, 0, MX) ans = (ans + f[n&1][st]) % P;
	printf("%d\n", ans);
}
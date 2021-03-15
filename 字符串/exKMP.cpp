/*
扩展KMP求的是对于原串S1的每一个后缀子串与模式串S2的最长公共前缀。
extend[i]表示为以字符串S1中以i为起点的后缀字符串和模式串S2的最长公共前缀长度.
*/
const int N = 2e7 + 7;
int n, m, z[N], p[N];
char a[N], b[N];

inline void Z(char *s, int n) {
	for (int i = 1; i <= n; i++) z[i] = 0;
	z[1] = n;
	for (int i = 2, l = 0, r = 0; i <= n; i++) {
		if (i <= r) z[i] = min(z[i-l+1], r - i + 1);
		while (i + z[i] <= n && s[i+z[i]] == s[z[i]+1]) ++z[i];
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}

inline void exkmp(char *s, int n, char *t, int m) {
	Z(t, m);
	for (int i = 1; i <= n; i++) p[i] = 0;
	for (int i = 1, l = 0, r = 0; i <= n; i++) {
		if (i <= r) p[i] = min(z[i-l+1], r - i + 1);
		while (i + p[i] <= n && s[i+p[i]] == t[p[i]+1]) ++p[i];
		if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
	}
}

int main() {
	rds(a, n), rds(b, m);
	exkmp(a, n, b, m);
	ll ans = 0;
	for (int i = 1; i <= m; i++) ans ^= 1ll * i * (z[i] + 1); // next
	print(ans);
	ans = 0;
	for (int i = 1; i <= n; i++) ans ^= 1ll * i * (p[i] + 1); // extend
	print(ans);
	return 0;
}
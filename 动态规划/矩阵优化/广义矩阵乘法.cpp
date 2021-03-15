/*
* 模版: 广义矩阵乘法
* URL: https://www.luogu.com.cn/problem/P2886
* c[i][j] = Max/Min {a[i][k] + a[j][k]}
*/
#include <bits/stdc++.h>
using namespace std;
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}
const int N = 250;
const int inf = 0x3f3f3f3f;
void Min(int &x, int y) {if(x > y) x = y;}
struct Matrix {
	int mat[N][N], n;
	Matrix() {
		memset(mat, inf, sizeof mat);
	}
	inline int* operator [](const int i) { //暴力重载运算符
		return mat[i];
	}
	Matrix operator *(const Matrix& rhs) const {
		Matrix ret; ret.n = n;
	 	rep (i, 0, n-1) rep (j, 0, n-1) rep (k, 0, n-1) {
			Min(ret.mat[i][j], mat[i][k] + rhs.mat[k][j]);
		}
		return ret;
	}
};
Matrix qpow(Matrix x, int k) {
	assert(k > 0);
	Matrix res = x; k--;
	while (k) {
		if (k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}
int re[1005], cnt; // 离散化
int main() {
	int n, t, s, e;
	read(n, t, s, e);
	Matrix g;
	memset(re, -1, sizeof re); 
	rep (i, 1, t) {
		int u, v, w;
		read(w, u, v);
		if(~re[u]) u = re[u]; else {re[u] = cnt++; u = re[u];}
		if(~re[v]) v = re[v]; else {re[v] = cnt++; v = re[v];}
		g[u][v] = g[v][u] = min(w, g[u][v]);
	}
	g.n = cnt;
	g = qpow(g, n);
	s = re[s]; e = re[e];
	write(g[s][e]);
}
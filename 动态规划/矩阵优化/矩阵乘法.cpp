/*
* 模版: n*n矩阵
* 矩阵乘法: 快速幂加速
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

struct Matrix {
	double mat[2][2], n;
	Matrix() {
		n = 2;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) mat[i][j] = 0;
	}
	Matrix operator * (const Matrix& rhs) const {
		Matrix ret;
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) {
				ret.mat[i][j] = 0;
				for (int k = 0; k < n; k++)
					ret.mat[i][j] += mat[i][k] * rhs.mat[k][j];
			}
		return ret;
	}
};

Matrix qpow(Matrix x, int k) {
	Matrix res;
	res.n = x.n;
	rep (i, 0, res.n-1) res.mat[i][i] = 1;
	while (k) {
		if (k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}
	return res;
}

int main() {
	int n; double p;
	while(scanf("%d %lf", &n, &p) != EOF) {
		int x[15];
		rep (i, 1, n) read(x[i]);
		sort(x+1, x+n+1);
		double ans = 1;
		Matrix t;
		t.mat[0][0] = p; t.mat[0][1] = 1-p;
		t.mat[1][0] = 1; t.mat[1][1] = 0;

		x[0] = 0;
		rep(i, 1, n) {
			if(x[i] == x[i-1]) continue;
			Matrix tmp = qpow(t, x[i]-x[i-1]-1);
			ans *= (1 - tmp.mat[0][0]);
		}
		printf("%.7f\n", ans);
	}
}
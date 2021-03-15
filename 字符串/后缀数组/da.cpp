/*
后缀数组：把字符串S的每个后缀按字典序排序
LCP：最长公共前缀

定义:
- sa[i]：排名为i的后缀首字母的下标
- rk[i]：首字母下标为i的后缀的排名
- LCP(i,j)：Suffix(sa[i])和Suffix(sa[j])的最长公共前缀

定理:
height[i] = LCP(i,i-1): 排名相邻的两个后缀数组的公共前缀长度
令h[i] = height[rk[i]]，可证**h[i]>=h[i-1]-1**（递推条件，时间复杂度收敛）

注意:
1. 不要在main函数内定义n和m变量，两者为全局变量
2. s数组内的元素最小值为1
*/
char s[N];
int y[N], x[N], c[N], sa[N], rk[N], height[N], ans[N];
int f[N][20];
int n, m;
void get_SA() {
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) ++c[x[i]=s[i]];
    for (int i = 2; i <= m; i++) c[i] += c[i-1];
    for (int i = n; i >= 1; i--) sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++) y[++num] = i;
        for (int i = 1; i <= n; i++) if(sa[i] > k) y[++num] = sa[i] - k;
        for (int i = 1; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) ++c[x[i]];
        for (int i = 2; i <= m; i++) c[i] += c[i-1];
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1;
        num = 1;
        for (int i = 2; i <= n; i++)
            x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k]) ? num : ++num;
        if(num == n) break;
        m = num;
    }
}
void get_height() {
    int k = 0;
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1; i <= n; i++) {
        if(rk[i] == 1) continue;
        if(k) --k;
        int j = sa[rk[i] - 1];
        while(j + k <= n && i + k <= n && s[i+k] == s[j+k]) ++k;
        height[rk[i]] = k;
    }
}
void init() {
	for (int i = 1; i <= n; i++) {
		f[i][0] = height[i];
	}

	for (int j = 1; (1<<j) <= n; j++) {
		for (int i = 1; i + (1<<j) - 1 <= n; i++) {
			f[i][j] = min(f[i][j-1], f[i + (1<<(j-1))][j-1]);
		}
	}
}
int lcp(int l, int r) {
	int a = rk[l], b = rk[r];
	if(a > b) swap(a, b);
	++a;
	int k = log2(b - a + 1);
	return min(f[a][k], f[b-(1<<k)+1][k]);
}

scanf("%s", s+1);
n = strlen(s+1);
m = 123;
get_SA();
get_height();
init();
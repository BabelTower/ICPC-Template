#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
const int M = 5e4 + 5;

int n, m, m1, ti;
int fs[N], pre[N], match[N], f[N], bz[N], bp[N];
int nt[2*M], dt[2*M], d[N*N];

void link(int x, int y) {
	nt[++m1] = fs[x];
	dt[fs[x] = m1] = y; 
}
int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}
int lca(int x, int y) {
	ti++;
	x = find(x); y = find(y);
	while(bp[x] != ti) {
		bp[x] = ti;
		x = find(pre[match[x]]);
		if(y) swap(x, y);
	}
	return x;
}
void make(int x, int y, int w) {
	while(find(x) != w) {
		pre[x] = y; y = match[x];
		if(bz[y] == 2) {
			bz[y] = 1;
			d[++d[0]] = y;
		}
		if(find(x) == x) f[x] = w;
		if(find(y) == y) f[y] = w;
		x = pre[y];
	}
} 
bool solve(int st) {
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		pre[i] = bz[i] = 0;
	}
	d[d[0] = 1] = st;
	bz[st] = 1;
	int l = 0;
	while(l < d[0]) {
		int k = d[++l];
		for (int i = fs[k]; i; i = nt[i]) {
			int p = dt[i];
			if(find(p) == find(k) || bz[p] == 2) continue;
			if(!bz[p]) {
                bz[p]=2; pre[p]=k;
                if(!match[p]) { //找到增广路
                    for(int x=p,y; x; x=y) {
	                    y = match[pre[x]];
	                    match[x] = pre[x];
	                    match[pre[x]] = x;//返回修改匹配
	                }
                    return 1;
                }
                bz[match[p]] = 1;
                d[++d[0]] = match[p];//否则将其匹配点加入队列
            }
            else {
                int w = lca(k,p);
                make(k, p, w);
                make(p, k, w);//以上分别修改k到lca的路径以及p到lca的路径（环的两半）
            }      
		}
	}
	return 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		link(x, y); link(y, x);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if(!match[i]) ans += solve(i);
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++) {
		printf("%d ", match[i]);
	}
}
/*
* 模版: 二元一次不定方程 (ax + by = c)
* 功能: 
*	1. 有无整数解
*	2. 正整数解的的个数
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void print(ll x) {
    if (x>9) print(x/10);
    putchar('0'+x%10);
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) { 
		x = 1, y = 0; 
		return a;
	}
	ll d = exgcd(b, a%b, x, y);
	ll t = x; x = y; y = t - a / b * y;
	return d;
}
void calc(ll a, ll b, ll c) {
	ll x0, y0;
	ll d = exgcd(a, b, x0, y0);
	if(c % d) { // 无整数解
		printf("0\n");
		return ;
	}
	ll x1 = x0 * (c / d), y1 = y0 * (c / d), k;
	ll dx = b / d, dy = a / d;
	if(x1 < 0) { // 将x提高到最小正整数 
		k = (1-x1)/dx + ((1-x1)%dx>0);
		x1 += k * dx; y1 -= k * dy;
	}
	else { // 将x降低到最小正整数 
		 k = (x1-1)/dx;
		 x1 -= k * dx; y1 += k * dy;
	}
	if(y1 > 0) { // 有正整数解 
		print((y1-1)/dy+1);
		puts("");
	}
	else { // 无正整数解 
		printf("0\n");
	}
}

int main() {
	int n;
	scanf("%d", &n);
	while(n--) {
		int b, d;
		scanf("%d%d", &b, &d);
		calc(d, b, 1ll*b*b);
	}
}

#ifndef POJ
#include <bits/stdc++.h> // POJ不能用
#else
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#endif
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define per(a,b,c) for(int a=b;a>=c;a--)
template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}
template <typename T> void Max(T &x, T y) {if (x < y) x = y;}
template <typename T> void Min(T &x, T y) {if (x > y) x = y;}
template <typename T> T gcd(T a, T b) {return b ? gcd(b, a%b) : a;}

/*
DC3实现SA复杂度为O(n)，常数大，考虑在数据量大的时候使用。
注意: 
1.MAXN开n的十倍大小;
2.dc3(r,sa,n+1,mx+1);r为待后缀处理的数组,sa为存储排名位置的数组,n+1和mx+1 都和倍增一样
3.calheight(r,sa,n);和倍增一样
*/
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x)*3 + 1 : ((x)-tb) * 3 + 2)
const int MAXN = 1e7 + 5; //n*10
int wa[MAXN], wb[MAXN], wv[MAXN], wws[MAXN];
int sa[MAXN], rk[MAXN], height[MAXN], r[MAXN];
int n;
char s[MAXN];
void sort(int *r, int *a, int *b, int n, int m)
{
    int i;
    for (i = 0; i < n; i++) wv[i] = r[a[i]];
    for (i = 0; i < m; i++) wws[i] = 0;
    for (i = 0; i < n; i++) wws[wv[i]]++;
    for (i = 1; i < m; i++) wws[i] += wws[i - 1];
    for (i = n - 1; i >= 0; i--) b[--wws[wv[i]]] = a[i];
    return;
}
int c0(int *r, int a, int b)
{
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}
int c12(int k, int *r, int a, int b)
{
    if (k == 2) return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
    else return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
}

void dc3(int *r, int *sa, int n, int m)
{
    int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
    r[n] = r[n + 1] = 0;
    for (i = 0; i < n; i++) if (i % 3 != 0) wa[tbc++] = i;
    sort(r + 2, wa, wb, tbc, m);
    sort(r + 1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);
    for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
        rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
    if (p < tbc) dc3(rn, san, tbc, p);
    else for (i = 0; i < tbc; i++) san[rn[i]] = i;
    for (i = 0; i < tbc; i++)
        if (san[i] < tb) wb[ta++] = san[i] * 3;
    if (n % 3 == 1) wb[ta++] = n - 1;
    sort(r, wb, wa, ta, m);
    for (i = 0; i < tbc; i++)
        wv[wb[i] = G(san[i])] = i;
    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for (; i < ta; p++) sa[p] = wa[i++];
    for (; j < tbc; p++) sa[p] = wb[j++];
    return;
}
void calheight(int *r, int *sa, int n)
{
    int i, j, k = 0;
    for (i = 1; i <= n; ++i)
        rk[sa[i]] = i;
    for (i = 0; i < n; height[rk[i++]] = k)
        for (k ? k-- : 0, j = sa[rk[i] - 1]; r[i + k] == r[j + k]; ++k);
    return;
}

scanf("%s", s);
int mx = -1;
n = strlen(s);
for (int i = 0; i < n; i++)
{
    r[i] = s[i];
    if (r[i] > mx) mx = r[i];
}
r[n] = 0;
dc3(r, sa, n + 1, mx + 1);
calheight(r, sa, n);
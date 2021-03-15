/*
> 最优匹配——**定理**：设$M$是一个带权完全二分图$G$的一个完备匹配，给每个顶点一个可行顶标（第$i$个$x$顶点的可行顶标用 $x_i$表示，第$j$个y顶点的可行顶标用$y_j$表示)，如果对所有的边$(i,j)$ in $G$，都有$x_i+y_j≥w_{i,j}$成立（$w_{i,j}$表示边的权），且对所有的边$(i,j)$ in $M$，都有 成立，则$M$是图$G$的$x_i+y_j≥w_{i,j}$一个最优匹配。
- 时间复杂度$O(n^3)$
- 最小权值匹配，边权取反，答案取反
- $x_i+y_j>=w_{i,j}$，最小顶标和等价于最大权值匹配
  $x_i+y_j<=w_{i,j}$，最大顶标和等价于最小权值匹配
*/
typedef long long ll;
const int N = 405;
const ll INF = LONG_LONG_MAX;
struct KM
{
    int link_x[N], link_y[N], n, nx, ny;
    bool visx[N], visy[N];
    int que[N << 1], top, fail, pre[N];
    ll mp[N][N], hx[N], hy[N], slk[N];
    inline int check(int i)
    {
        visx[i] =true;
        if(link_x[i])
        {
            que[fail++] = link_x[i];
            return visy[link_x[i]] = true;
        }
        while(i)
        {
            link_x[i] = pre[i];
            swap(i, link_y[pre[i]]);
        }
        return 0;
    }
    void bfs(int S)
    {
        for(int i=1; i<=n; i++)
        {
            slk[i] = INF;
            visx[i] = visy[i] = false;
        }
        top = 0; fail = 1;
        que[0] = S;
        visy[S] = true;
        while(true)
        {
            ll d;
            while(top < fail)
            {
                for(int i = 1, j = que[top++]; i <= n; i++)
                {
                    if(!visx[i] && slk[i] >= (d = hx[i] + hy[j] - mp[i][j]))
                    {
                        pre[i] = j;
                        if(d) slk[i] = d;
                        else if(!check(i)) return;
                    }
                }
            }
            d = INF;
            for(int i=1; i<=n; i++)
            {
                if(!visx[i] && d > slk[i]) d = slk[i];
            }
            for(int i=1; i<=n; i++)
            {
                if(visx[i]) hx[i] += d;
                else slk[i] -= d;
                if(visy[i]) hy[i] -= d;
            }
            for(int i=1; i<=n; i++)
            {
                if(!visx[i] && !slk[i] && !check(i)) return;
            }
        }
    }
    void init(int cntx, int cnty)
    {
        nx = cntx; ny = cnty; n = max(nx, ny);
        top = fail = 0;
        for (int i = 1; i <= n; i++) {
            link_x[i] = link_y[i] = pre[i] = 0;
            hx[i] = hy[i] = 0;
            for (int j = 1; j <= n; j++) mp[i][j] = 0;
        }
    }
    void solve() {
        for(int i=1; i<=n; i++) for(int j=1; j<=n; j++)
            if(hx[i] < mp[i][j]) hx[i] = mp[i][j];
        ll ans = 0;
        for (int i = 1; i <= n; i++) bfs(i);
        for (int i = 1; i <= nx; i++) ans += mp[i][link_x[i]];
        printf("%lld\n", ans); // 输出最大权值
        
        /*
        for (int i = 1; i <= nx; i++) if(!mp[i][link_x[i]])
            link_x[i] = 0; // 如果不存在该边则置零
        for (int i = 1; i <= nx; i++) {
            if(i != 1) printf(" ");
            printf("%d", link_x[i]); // 输出每一组匹配
        }
        printf("\n");
         */
    }
}km;

// 调用
int n; scanf("%d", &n);
km.init(n, n);
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        ll w; scanf("%lld", &w);
        km.mp[i][j] = w;
    }
}
km.solve();
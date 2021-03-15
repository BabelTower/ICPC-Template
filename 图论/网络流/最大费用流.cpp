/*
	EK + SPFA
*/
const int maxn = 1e5+10;
struct node {
    int to,w,f,nxt;
} e[maxn];
int n,m,s,t,maxflow,mincost;
int dis[maxn],flow[maxn],via[maxn],pre[maxn],last[maxn];
int head[maxn],cnt=0;
void init() {
	memset(head,-1,sizeof(head));
	cnt=0;
}
void ade( int u, int v, int f, int w )
{
    e[cnt].to = v;
    e[cnt].f = f;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt++;
}
void add(int u, int v, int f, int w) {
	w = -w; // 最大费用
	ade(u, v, f, w);
	ade(v, u, 0, -w);
}
 
int spfa()
{
    memset(dis,inf,sizeof(dis));
    memset(flow,inf,sizeof(flow));
    memset(via,0,sizeof(via));
    queue <int> Q;
    Q.push(s); via[s]=1; dis[s]=0; pre[t]=-1;
    while ( !Q.empty() ) {
        int x = Q.front(); Q.pop(); via[x]=0;
        for ( int i=head[x]; i!=-1; i=e[i].nxt ) {
            int y = e[i].to, f=e[i].f, w=e[i].w;
            if ( f && dis[y]>dis[x]+w ) { // 只要最短流能更新就更新
                dis[y] = dis[x] + w;
                pre[y] = x; // y 的父节点是x
                last[y] = i; // y点连接其父节点的边，编号为i
                flow[y] = min(flow[x],f); // 源点到y点的最大流量。会被最小的一个分支限制住
                if ( via[y]==0 ) {    // 只有队列中没有当前值才往队列里加。
                    Q.push(y); via[y]=1;
                }
            }
        }
    }
    return pre[t]!=-1; // 判断汇点是否有点连入，即还存不存在增广路。初始化pre[t]=-1.
}
 
void EK()
{
    maxflow = mincost = 0;
    while ( spfa() ) { // 还存在增广路就进入
        int x = t;
        maxflow += flow[t]; // 源点到t点的最大流量
        mincost += flow[t]*dis[t];
        while ( x!=s ) {  // 递归改变边的流量
            e[last[x]].f -= flow[t];
            e[last[x]^1].f += flow[t];
            x = pre[x];
        }
    }
}
 
/*
调用:
EK();
cout << -mincost << endl;
 */ 

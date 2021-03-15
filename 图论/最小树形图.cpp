/*
最小树形图，就是给出一个带权有向图，从中指定一个特殊的结点 root.求一棵以 root 为根的有向生成树 T，且使得 T 中所有边权值最小。
*/

const int M = 1e4 + 5;
const int N = 105;
struct Edge {
    int u, v, w;
}e[M];
const int inf = 2e9;
int n, m, root;
int pre[N], ine[N];
int vis[N], id[N];
int zhuliu() {
    int ans = 0;
    while(1) {
        for (int i = 1; i <= n; i++) ine[i] = inf;
        for (int i = 1; i <= m; i++) {
            if(e[i].u != e[i].v && e[i].w < ine[e[i].v]) {
                ine[e[i].v] = e[i].w;
                pre[e[i].v] = e[i].u;
            }
        }
        for (int i = 1; i <= n; i++) {
            if(i != root && ine[i] == inf) return -1;
        }
        int cnt = 0;
        for (int i = 1; i <= n; i++) vis[i] = id[i] = 0;
        for (int i = 1; i <= n; i++) {
            if(i == root) continue;
            ans += ine[i];
            int v = i;
            while(vis[v] != i && !id[v] && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if(!id[v] && v != root) {
                id[v] = ++cnt;
                for (int u = pre[v]; u != v; u = pre[u]) {
                    id[u] = cnt;
                }
            }
        }
        if(cnt == 0) break;
        for (int i = 1; i <= n; i++) if(!id[i]) id[i] = ++cnt;
        for (int i = 1; i <= m; i++) {
            int u = e[i].u, v = e[i].v;
            e[i].u = id[u], e[i].v = id[v];
            if(id[u] != id[v]) e[i].w -= ine[v];
        }
        root = id[root];
        n = cnt;
    }
    return ans;
}
int main() {
    scanf("%d%d%d", &n, &m, &root);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    }
    printf("%d\n", zhuliu());
}

/*
无根树最小树形图
*/
#include <bits/stdc++.h>
#define lowbit(x) ( x&(-x) )
#define INF 0x3f3f3f3f
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int maxN = 1005;
int N, M;
ll sum;
struct Eddge    //存边
{
    int u, v;
    ll val;
    Eddge(int a=0, int b=0, ll c=0):u(a), v(b), val(c) {}
}edge[maxN*maxN];
int pre[maxN], id[maxN], vis[maxN], pos;
ll in[maxN];    //最小入边权，pre[]为其前面的点（该边的起点）
ll Dir_MST(int root, int V, int E)  //root是此时的根节点，我们最初的时候将0（万能节点作为根节点进入），V是点的个数（包括之后要收缩之后点的剩余个数），E是边的条数（不会改变）
{
    ll ans = 0;
    while(true)     //如果还是可行的话
    {
        for(int i=0; i<V; i++) in[i] = INF; //给予每个点进行初始化
        /* (1)、最短弧集合E0 */
        for(int i=1; i<=E; i++)     //通过这么多条单向边，确定的是每个点的指向边的最小权值
        {
            int u = edge[i].u, v = edge[i].v;
            if(edge[i].val < in[v] && u!=v)     //顶点v有更小的入边，记录下来    更新操作，u!=v是为了确保缩点之后，我们的环将会变成点的形式
            {
                pre[v] = u;     //节点u指向v
                in[v] = edge[i].val;    //最小入边
                if(u == root) pos = i;  //这个点就是实际的起点
            }
        }
        /* (2)、检查E0 */
        for(int i=0; i<V; i++)     //判断是否存在最小树形图
        {
            if(i == root) continue;     //是根节点，不管
            if(in[i] == INF) return -1;     //除了根节点以外，有点没有入边，则根本无法抵达它，说明是独立的点，一定不能构成树形图
        }
        /* (3)、收缩图中的有向环 */
        int cnt = 0;    //接下来要去求环，用以记录环的个数  找环开始！
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        in[root] = 0;
        for(int i=0; i<V; i++)     //标记每个环
        {
            ans += in[i];   //加入每个点的入边（既然是最小入边，所以肯定符合最小树形图的思想）
            int v = i;  //v一开始先从第i个节点进去
            while(vis[v] != i && id[v] == -1 && v != root)  //退出的条件有“形成了一个环，即vis回归”、“到了一个环，此时就不要管了，因为那边已经建好环了”、“到了根节点，就是条链，不用管了”
            {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1)    //如果v是root就说明是返回到了根节点，是条链，没环；又或者，它已经是进入了对应环的编号了，不需要再跑一趟了
            {
                for(int u=pre[v]; u!=v; u=pre[u])   //跑这一圈的环
                {
                    id[u] = cnt;    //标记点u是第几个环
                }
                id[v] = cnt++;  //如果再遇到，就是下个点了
            }
        }
        if(cnt == 0) return ans;    //无环的情况，就说明已经取到了最优解，直接返回，或者说是环已经收缩到没有环的情况了
        for(int i=0; i<V; i++) if(id[i] == -1) id[i] = cnt++;   //这些点是环外的点，是链上的点，单独再给他们赋值
        for(int i=1; i<=E; i++)     //准备开始建立新图  缩点，重新标记
        {
            int u = edge[i].u, v = edge[i].v;
            edge[i].u = id[u];  edge[i].v = id[v];  //建立新图，以新的点进入
            if(id[u] != id[v]) edge[i].val -= in[v];    //为了不改变原来的式子，使得展开后还是原来的式子
        }
        V = cnt;    //之后的点的数目
        root = id[root];    //新的根节点的序号，因为id[]的改变，所以根节点的序号也改变了
    }
    return ans;
}
int main()
{
    while(scanf("%d%d", &N, &M)!=EOF)
    {
        sum = 0;
        for(int i=1; i<=M; i++)
        {
            scanf("%d%d%lld", &edge[i].u, &edge[i].v, &edge[i].val);
            edge[i].u++;   edge[i].v++;   //把‘0’号节点空出来，用以做万能节点，留作之后用
            sum += edge[i].val;
        }
        sum++;  //一定要把sum给扩大，这就意味着，除去万能节点以外的点锁构成的图的权值和得在（sum-1）之内（包含）
        for(int i=M+1; i<=M+N; i++)     //这就是万能节点了，就是从0这号万能节点有通往所有其他节点的路，而我们最后的最小树形图就是从这个万能节点出发所能到达的整幅图
        {
            edge[i] = Eddge(0, i-M, sum);   //对于所有的N个其他节点都要建有向边
        }       //此时N+1为总的节点数目，M+N为总的边数
        ll ans = Dir_MST(0, N + 1, M+N);    //ans代表以超级节点0为根的最小树形图的总权值
        if(ans == -1 || ans - sum >= sum) printf("impossible\n");   //从万能节点的出度只能是1，所以最后的和必须是小于sum的，而万能节点的出度就由“ans - sum >= sum”保证
        else printf("%lld %d\n", ans - sum, pos - M - 1);   //pos-M得到的是1～N的情况，所以“-1”的目的就在于这里
        printf("\n");
    }
    return 0;
}



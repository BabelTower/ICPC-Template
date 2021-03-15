#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100002;
const int M=200002;
const int inf=2147483647;
inline int read()
{
    char ch=getchar();
    int x=0;bool f=false;
    while (!isdigit(ch)) f^=!(ch^45),ch=getchar();
    while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if (f) x=-x;return x;
}
int n,m,s;
int head[N],to[M],nex[M],cnt=0;
ll val[M];
ll dis[N];
bool vis[N];
struct data
{
    int id;
    ll v;
    bool operator <(const data&A)const
    {
        return A.v<v;
    }
};
inline void add(int s,int ed,ll w)
{
    to[++cnt]=ed;
    val[cnt]=w;
    nex[cnt]=head[s];
    head[s]=cnt;
}
inline void Dijkstra(int st)
{
    priority_queue<data>q;
    for (int i=1;i<=n;++i)
    dis[i]=inf;
    dis[st]=0;
    q.push((data){st,dis[st]});
    while (!q.empty())
    {
        int now=q.top().id;
        q.pop();
        if (vis[now]) continue;
        vis[now]=true;
        for (int i=head[now];i;i=nex[i])
        {
            int v=to[i];
            if (!vis[v]&&dis[v]>dis[now]+val[i])
            {
                dis[v]=dis[now]+val[i];
                q.push((data){v,dis[v]});
            }
        }
    }
}
int main()
{
    n=read(),m=read(),s=read();
    int x,y,z;
    for (int i=1;i<=m;++i)
    {
        x=read(),y=read(),z=read();
        add(x,y,z);
    }
    Dijkstra(s);
    for (int i=1;i<=n;++i)
    printf("%lld ",dis[i]);
    return 0;
}
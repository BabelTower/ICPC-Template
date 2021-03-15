#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
typedef long long ll;
const int maxn = 1e6 + 5;
int n,m,s,cnt=0;
int head[maxn],dep[maxn],fa[maxn][64],lg[maxn];
struct node
{
    int to,nex;
}e[maxn];
inline void add(int x,int y)
{
    e[++cnt].nex=head[x];
    e[cnt].to=y;
    head[x]=cnt;
}
void dfs(int u,int f)
{
    dep[u]=dep[f]+1;
    fa[u][0]=f;
    for(int i=1;(1<<i)<=dep[u];++i)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i;i=e[i].nex)
    {
        if(e[i].to==f) continue;
        dfs(e[i].to,u);
    }
}
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]-1];
    if(x!=y)
    {
        for(int i=lg[dep[x]];i>=0;--i)
            if(fa[x][i]!=fa[y][i])
            {
                x=fa[x][i];
                y=fa[y][i];
            }
        x=fa[x][0];
    }
    return x;
}
int main()
{
	cin >> n >> m >> s;
	for (int i = 1; i < n; i++)
    {
        int x,y;
		cin >> x >> y;
        add(x,y);add(y,x);
    }
    dfs(s,0);
	for (int i = 1; i <= n; i++)
		lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	for (int i = 1; i <= m; i++)
    {
        int x,y;
		cin >> x >> y;
        printf("%d\n",lca(x,y));
    }
    return 0;
}


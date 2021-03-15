const int maxn = 1e5 + 10;
struct edge{
	int dis;
	int nxt;
	int to;
}e[maxn<<1];
int head[maxn],tot;
inline void add(int u,int v,int dis){
	e[++tot].nxt=head[u];
	e[tot].dis=dis;
	e[tot].to=v;
	head[u]=tot;
}
int query[1010],rt,maxp[maxn],sum,size[maxn],vis[maxn],judge[10000000],rem[maxn],dis[maxn],test[10000000];
int q[maxn];
int n,m;
void getrt(int u,int pa){
	size[u]=1;
	maxp[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==pa || vis[v]) continue;
		getrt(v,u);
		size[u]+=size[v];
		maxp[u]=max(maxp[u],size[v]);
	}
	maxp[u]=max(maxp[u],sum-size[u]);
	if(maxp[u]<maxp[rt]) rt=u;
}
void getdis(int u,int fa){
	rem[++rem[0]]=dis[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa|| vis[v]) continue;
		dis[v]=dis[u]+e[i].dis;
		getdis(v, u);
	}
}
void cal(int u){
	int p=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]) continue;
		rem[0]=0;
		dis[v]=e[i].dis;
		getdis(v,u);
		for(int j=rem[0];j;--j)
			for(int k=1;k<=m;k++){
				if(query[k]>=rem[j]){
					test[k]|=judge[query[k]-rem[j]];
				}
			}
		for(int j=rem[0];j;--j){
			q[++p]=rem[j];
			judge[rem[j]]=1;
		}
	}
	for(int i=1;i<=p;++i){
		judge[q[i]]=0;
	}
}
void solve(int u){
	vis[u]=judge[0]=1;
	cal(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]) continue;
		sum=size[v];
		maxp[rt=0]=10000000;
		getrt(v, 0);
		solve(rt);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v,dis;
		scanf("%d%d%d",&u,&v,&dis);
		add(u,v,dis);
		add(v,u,dis);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",query+i);
	}
	maxp[rt]=sum=n;
	getrt(1,0);
	solve(rt);
	for(int i=1;i<=m;i++){
		if(test[i]) puts("AYE");
		else puts("NAY");
	}
}
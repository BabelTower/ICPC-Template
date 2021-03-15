/* 无向图
* 欧拉回路：
*   1. 图G是连通的，不能有孤立点存在。
*   2. 对于无向图来说度数为奇数的点个数为0;对于有向图来说每个点的入度必须等于出度。
* 欧拉通路：
*   1. 图G是连通的，无孤立点存在。
*   2. 对于无向图来说，度数为奇数的的点可以有2个或者0个，并且这两个奇点其中一个为起点另外一个为终点。对于有向图来说，可以存在两个点，其入度不等于出度，其中一个入度比出度大1，为路径的起点；另外一个出度比入度大1，为路径的终点。
*/
const int maxn = 100;
int deg[maxn];

struct Edge{
    int to,nxt;
}e[2010];
int head[maxn],tot;
void addEdge(int a,int b){
    ++tot;
    e[tot].to=b;
    e[tot].nxt=head[a];
    head[a]=tot;
}

int vis[2010];
void dfs(int u){
    for(int k=head[u];k;k=e[k].nxt){
        if(!vis[k]){
            vis[k]=1;
            if(k&1) vis[k+1]=1;
            else vis[k-1]=1;
            dfs(e[k].to);
            printf("%d %d\n",e[k].to,u);
        }
    }
}

int fa[60];
int find(int x){
    return fa[x]==x?x:find(fa[x]);
}

void init(){
    memset(head, 0, sizeof head);
    memset(deg, 0, sizeof deg);
    memset(vis, 0, sizeof vis);
    for(int i=1;i<=50;i++) fa[i]=i;
    tot=0;
}

int main() {
    int t,kase=0;
    scanf("%d",&t);
    
    while (t--) {
        int n;scanf("%d",&n);
        
        init();
        
        for(int i=1;i<=n;i++) {
            int a,b;
            scanf("%d%d",&a,&b);
            addEdge(a, b);
            addEdge(b, a);
            deg[a]++;deg[b]++;
            
            int xa=find(a);
            int xb=find(b);
            if(xa!=xb) fa[xa]=xb;
        }
        
        int cnt=0,count=0;
        for(int i=1;i<=50;i++) {
            if(find(i)==i && deg[i]) count++;
            if(deg[i]&1) cnt++;
        }
        
        if(kase) puts("");
        printf("Case #%d\n",++kase);
        if(cnt>0 || count!=1){
            puts("some beads may be lost");
        }
        else{
            for(int i=1;i<=50;i++){
                if(deg[i]){
                    dfs(i);
                    break;
                }
            }
        }
    }
}


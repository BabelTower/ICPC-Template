/*
1. 建图时初始化源点s、汇点t
2. 对于包含二分图最大匹配在内的单位网络，Dinic算法可以在O(m√n)的时间内求出其最大流。
*/

#define inf 0x7fffffff
#define maxn 25000
struct Edge{
    int from,to,cap,flow;
};
class Dinic{
private:
    int s,t,c;
    vector<Edge>edges;
    vector<int>G[maxn];//结点
    bool vis[maxn];
    int dist[maxn];
    int cur[maxn];
public:
    int n,m;
    void AddEdge(int from,int to,int cap){
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        c=edges.size();
        G[from].push_back(c-2);
        G[to].push_back(c-1);
    }
    bool BFS(){
        queue<int>Q;
        memset(vis,0,sizeof(vis));
        Q.push(s);
        dist[s]=0;
        vis[s]=1;
        while(!Q.empty()){
            int x=Q.front();Q.pop();
            for(int i=0;i<G[x].size();i++){
                Edge& e=edges[G[x][i]];
                if(!vis[e.to]&&e.cap>e.flow){
                    vis[e.to]=1;
                    dist[e.to]=dist[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int DFS(int x,int a){
        if(x==t||a==0)return a;
        int flow=0,f;
        for(int& i=cur[x];i<G[x].size();i++){
            Edge& e=edges[G[x][i]];
            if(dist[x]+1==dist[e.to]&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0)break;
            }
        }
        return flow;
    }
    int Maxflow(int s,int t){
        this->s=s;this->t=t;
        int flow=0;
        while(BFS()){
            memset(cur,0,sizeof(cur));
            flow+=DFS(s,inf);
            flow+=DFS(s,inf);
        }
        return flow;
    }
    void init(){
        edges.clear();
        for(int i=0;i<maxn;i++){
            G[i].clear();
            dist[i]=0;
        }
    }
    vector<int> Mincut(){
        BFS();
        vector<int> ans;
        for(int i=0;i<edges.size();i++){
            Edge& e=edges[i];
            if(vis[e.from]&&!vis[e.to]&&e.cap>0)ans.push_back(i);
        }
        return ans;
    }
}Do;


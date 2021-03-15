/*
* Bellman-Ford 算法
* 一种基于松弛（relax）操作的最短路算法,支持负权。
*/

bool inq[510];
int dis[510],sumv[510];
int n,v[510*3],__next[510*3],e,w[510*3],first[510],cnts[510];
void AddEdge(int U,int V,int W) {
    v[++e]=V;
    w[e]=W;
    __next[e]=first[U];
    first[U]=e;
}

bool spfa(const int &s) {
	queue<int>Q;
    memset(dis,0x7f,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    inq[s]=1;
    ++cnts[s];
    while(!Q.empty()) {
        int U=Q.front();
        for(int i=first[U]; i; i=__next[i])
            if(dis[v[i]]>dis[U]+w[i]) {
                dis[v[i]]=dis[U]+w[i];
                if(!inq[v[i]]) {
                    Q.push(v[i]);
                    inq[v[i]]=1;
                    ++cnts[v[i]];
                    if(cnts[v[i]]>n+1)
                        return 0;
                }
            }
        Q.pop();
        inq[U]=0;
    }
    return 1;
}
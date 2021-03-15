/*
1. 若图G是非连通图，则需要依次判断各连通子图是不是二分图。
2. 无向图加双向边
*/
vector<int> G[maxn];
int color[maxn];
 
int bfs(int u) {
	queue<int> Q;
	Q.push(u);
	color[u]=1;
 
	while(!Q.empty()) {
		int t=Q.front();
		Q.pop();
		for(int i=0; i<G[t].size(); i++) {
			if(color[G[t][i]]==color[t])
				return 0; //Adjacent nodes are the same color, not bipartite graph
			else if(color[G[t][i]]==0) { //no dyeing
				color[G[t][i]]=-color[t];
				Q.push(G[t][i]);
			}
		}
	}
 
	return 1;
}



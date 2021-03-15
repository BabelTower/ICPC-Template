/*
* 求多源负权最短路时用，比floyd快，𝑂(𝑉𝐸+𝑉2𝑙𝑜𝑔𝑉)
*/

const int N = 5007;

struct Edge {
	int nxt, pre, w, from;
} e[N << 1];
int head[N], cntEdge;
inline void add(int u, int v, int w) {
	e[++cntEdge] = (Edge){ head[u], v, w, u}, head[u] = cntEdge;
}

int DIS[N][N], H[N], vis[N];
int qq[N], h, t;
int n, m;
inline void SPFA(int st) {
	for(register int i = 1; i <= n; i += 3){
		H[i] = 0x3f3f3f3f;
		H[i + 1] = 0x3f3f3f3f;
		H[i + 2] = 0x3f3f3f3f;
	}
	H[st] = 0;
	qq[++t] = st;
	while(h != t){
		int u = qq[++h];
		if(h >= N - 5) h = 0;
		vis[u] = false;
		for(register int i = head[u]; i; i = e[i].nxt){
			int v = e[i].pre;
			if(H[v] > H[u] + e[i].w){
				H[v] = H[u] + e[i].w;
				if(!vis[v]){
					vis[v] = true;
					qq[++t] = v;
					if(t >= N - 5) t = 0;
				}
			}
		}
	}
}

struct nod {
	int x, w;
	bool operator < (const nod &com) const {
		return w > com.w;
	}
};
#include <queue>
priority_queue<nod> q;
int dis[N];
inline void Dijkstra(int st) {
	for(register int i = 1; i <= n; i += 3){
		dis[i] = 0x3f3f3f3f;
		dis[i + 1] = 0x3f3f3f3f;
		dis[i + 2] = 0x3f3f3f3f;
	}
	dis[st] = 0;
	q.push((nod){ st, 0});
	while(!q.empty()){
		int u = q.top().x, w = q.top().w;
		q.pop();
		if(w != dis[u]) continue;
		for(register int i = head[u]; i; i = e[i].nxt){
			int v = e[i].pre;
			if(dis[v] > dis[u] + e[i].w){
				dis[v] = dis[u] + e[i].w;
				q.push((nod){ v, dis[v]});
			}
		}
	}
}

int main() {
	io >> n >> m;
	
	R(i,1,m){
		int u, v, w;
		io >> u >> v >> w;
		add(u, v, w);
	}
	
	R(i,1,n){
		add(0, i, 0);
	}
	
	SPFA(0);

	R(i,1,cntEdge){
		e[i].w += H[e[i].from] - H[e[i].pre];
	}

	R(i,1,n){
		Dijkstra(i);
		R(j,1,n){
			DIS[i][j] = dis[j] - H[i] + H[j];
		}
	}
	
	R(i,1,n){
		R(j,1,n){
			printf("%d ", DIS[i][j]);
		}
		putchar('\n');
	}
	
	return 0;
}
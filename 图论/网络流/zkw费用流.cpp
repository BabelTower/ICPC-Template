/*
1. zkw费用流适用于稠密图;
2. 使用前调用init()，初始化n、s、t;
*/
const int N = 1e3 + 5;
const int M = 5e5 + 5;
const int inf = 0x3f3f3f3f;
namespace zkw {
    struct Edge {
        int to, nex, f, c;
    } e[M];
    int head[N], tot;
    int n, s, t;
    int level[N], dis[N];
    int maxf, cost;
    bool flag, vis[N];
    void init() {
        tot = 1;
        memset(head, 0, sizeof head);
    }
    void ade(int u, int v, int f, int c) {
        e[++tot] = {v, head[u], f, c};
        head[u] = tot;
    }
    void add(int u, int v, int f, int c) {
        // c = -c;
        ade(u, v, f, c);
        ade(v, u, 0, -c);
    }
    bool spfa() {
        memset(dis, inf, sizeof dis);
        memset(vis, 0, sizeof vis);
        memset(level, 0, sizeof level);
        dis[s] = 0; level[s] = 1; vis[s] = 1;
        deque<int> Q;
        Q.push_back(s);
        while(!Q.empty()) {
            int x = Q.front();
            Q.pop_front();
            vis[x] = 0;
            for (int i = head[x]; i; i = e[i].nex) {
                int to = e[i].to;
                if(dis[to]>dis[x]+e[i].c && e[i].f>0) {
                    dis[to] = dis[x] + e[i].c;
                    level[to] = level[x] + 1;
                    if(!vis[to]) {
                        vis[to] = 1;
                        if(!Q.empty() && dis[to] < dis[Q.front()])
                            Q.push_front(to);
                        else
                            Q.push_back(to);
                    }
                }
            }
        }
        return dis[t] != inf;
    }
    int dfs(int x, int f) {
        if(x == t) {
            maxf += f;
            flag = true;
            return f;
        }
        int num = 0, flow = 0;
        for (int i = head[x]; i; i=e[i].nex) {
            int to = e[i].to;
            if(f == num) break;
            if(dis[x]+e[i].c==dis[to] && level[x]+1==level[to] && e[i].f>0) {
                flow = dfs(to, min(f-num, e[i].f));
                num += flow;
                cost += flow * e[i].c;

                e[i].f -= flow;
                e[i^1].f += flow;
            }
        }
        return num;
    }
    void mcmf() {
        maxf = cost = 0;
        while(spfa()) {
            flag = true;
            while(flag) {
                flag = false;
                dfs(s, inf);
            }
        }
    }
}


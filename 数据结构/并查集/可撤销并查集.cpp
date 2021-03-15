/*
    按秩合并实现，不能路经压缩
*/
struct UFS {
    stack<pair<int*, int>> stk;
    int fa[N], rnk[N];
    inline void init(int n) {
        for (int i = 0; i <= n; ++i) fa[i] = i, rnk[i] = 0;
    }
    inline int Find(int x) {
        while(x^fa[x]) x = fa[x];
        return x;
    }
    inline void Merge(int x, int y) {
        x = Find(x), y = Find(y);
        if(x == y) return ;
        if(rnk[x] <= rnk[y]) {
            stk.push({fa+x, fa[x]});
            fa[x] = y;
            if(rnk[x] == rnk[y]) {
                stk.push({rnk+y, rnk[y]});
                rnk[y]++;
            }
        }
        else {
            stk.push({fa+y, fa[y]});
            fa[y] = x;
        }
    }
    inline void Undo() {
        *stk.top().fi = stk.top().se;
        stk.pop();
    }
}ufs;

/*
    按大小合并，复杂度无差异
*/
namespace UFS {
    int fa[maxn], sz[maxn], top;
    struct STK {
        int x, y;
    } stk[maxn*2];
    void init(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
        top = 0;
    }
    int find(int x) {
        return fa[x] == x ? x : find(fa[x]);
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if(fx == fy) return ;
        if(sz[fx] > sz[fy]) swap(fx, fy);
        sz[fy] += sz[fx];
        stk[++top] = {fx, fy};
        fa[fx] = fy;
    }
    void back() {
        sz[stk[top].y] -= sz[stk[top].x];
        fa[stk[top].x] = stk[top].x;
        top--;
    }
}
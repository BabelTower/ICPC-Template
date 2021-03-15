/*
CF1444C - 可撤销种类并查集
满足“敌人的敌人是朋友”这个条件时可用，或是相邻节点都是不同种类（总共两个种类）
1. 种类并查集初始化两倍空间，Init(2*n)
2. 只能合并两个敌对关系的节点，Merge(x,y+n) Merge(y,x+n)
3. 判断两个节点的关系，Find(x)==Find(y)表示x和y是朋友，Find(x)==Find(y+n)表示x和y是敌人
4. Undo撤销并不是一次操作，而是每一次数值更改都会入栈
*/

struct UFS {
    stack<pair<int*, int>> stk;
    int fa[maxn*2], rnk[maxn*2];
    inline void Init(int n) {
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
        *stk.top().first = stk.top().second;
        stk.pop();
    }
}T;
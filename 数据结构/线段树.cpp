/* 
    区间修改、区间查询区间和
*/
const int N = 1e5 + 5;
#define ls o<<1
#define rs o<<1|1
int sum[N<<2], lz[N<<2], n;
void pushup(int o) {
    sum[o] = sum[ls] + sum[rs];
}
void pushdown(int o, int l, int r) {
    if(lz[o] != -1) {
        int m = (l + r) >> 1;
        sum[ls] = lz[o] * (m - l + 1);
        sum[rs] = lz[o] * (r - m);
        lz[ls] = lz[rs] = lz[o];
        lz[o] = -1;
    }
}
void build(int l, int r, int o) {
    lz[o] = -1; sum[o] = 0;
    if(l == r) return ;
    int m = (l + r) >> 1;
    build(l, m, ls);
    build(m+1, r, rs);
}
void update(int L, int R, int val, int l = 1, int r = n, int o = 1) {
    if(l > R || r < L) return ;
    if(L <= l && r <= R) {
        sum[o] = val * (r - l + 1);
        lz[o] = val;
        return ;
    }
    int m = (l + r) >> 1;
    pushdown(o, l, r);
    update(L, R, val, l, m, ls);
    update(L, R, val, m+1, r, rs);
    pushup(o);
}
int query(int L, int R, int l = 1, int r = n, int o = 1) {
    if(l > R || r < L) return 0;
    if(L <= l && r <= R) {
        return sum[o];
    }
    int m = (l + r) >> 1, res = 0;
    pushdown(o, l, r);
    res += query(L, R, l, m, ls);
    res += query(L, R, m+1, r, rs);
    return res;
}

/*
    区间修改，区间查询极值
*/
const int inf = 0x3f3f3f3f;
#define ls o<<1
#define rs o<<1|1
int n, f;
int lazy[maxn<<2], mx[maxn<<2], mn[maxn<<2];
void pushdown(int o) {
    if(lazy[o]) {
        mx[ls] = mx[rs] = lazy[o];
        mn[ls] = mn[rs] = lazy[o];
        lazy[ls] = lazy[rs] = lazy[o];
        lazy[o] = 0;
    }
}
void pushup(int o) {
    mx[o] = max(mx[ls], mx[rs]);
    mn[o] = min(mn[ls], mn[rs]);
}
void update(int L, int R, int x, int l = 1, int r = n, int o = 1) {
    if(l > R || r < L) return ;
    if(L <= l && r <= R) {
        lazy[o] = x;
        mx[o] = mn[o] = x;
        return ;
    }
    pushdown(o);
    int mid = (l + r) >> 1;
    update(L, R, x, l, mid, ls);
    update(L, R, x, mid+1, r, rs);
    pushup(o);
}

int query_max(int L, int R, int l = 1, int r = n, int o = 1) {
    if(l > R || r < L) return 0;
    if(L <= l && r <= R) {
        return mx[o];
    }
    pushdown(o);
    int mid = (l + r) >> 1;
    return max(query_max(L, R, l, mid, ls), query_max(L, R, mid+1, r, rs));
}

int query_min(int L, int R, int l = 1, int r = n, int o = 1) {
    if(l > R || r < L) return inf;
    if(L <= l && r <= R) {
        return mn[o];
    }
    pushdown(o);
    int mid = (l + r) >> 1;
    
    return min(query_min(L, R, l, mid, ls), query_min(L, R, mid+1, r, rs));
}

/*
    单点修改、区间查询
*/
#define ls o<<1
#define rs o<<1|1
const int N = 2e5 + 5;
int tr[N<<2];
int sz;
void pushup(int o) {
    tr[o] = max(tr[ls], tr[rs]);
}

void update(int i, int x, int l = 1, int r = sz, int o = 1) {
    if(l == r) {
        tr[o] = x;
        return ;
    }
    int mid = (l + r) >> 1;
    if(i <= mid) update(i, x, l, mid, ls);
    else update(i, x, mid+1, r, rs);
    pushup(o);
}

int query(int L, int R, int l = 1, int r = sz, int o = 1) {
    if(r < L || R < l) return 0;
    if(L <= l && r <= R) {
        return tr[o];
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if(L <= mid) res = max(res, query(L, R, l, mid, ls));
    if(mid < R) res = max(res, query(L, R, mid+1, r, rs));
    return res;
}
/*
划分树是一种来解决区间第k大的一种数据结构，其常数、理解难度都要比主席树低很多。
Tips:非递归版本，常数较小。
*/
const int MAXN = 2e5 + 5;
const int LOG_N = 30;
// tree[dep][i] 第dep层第i个位置的数值
// toleft[p][i] 第p层前i个数中有多少个整数分入下一层
int tree[LOG_N][MAXN], sorted[MAXN], toleft[LOG_N][MAXN];
void build(int l, int r, int dep) {
    if(l == r) return;
    int mid = (l + r) / 2;
    int same = mid - l + 1; // 和中点数相同的数的个数
    for(int i = l; i <= r; i++)
        if(tree[dep][i] < sorted[mid]) same--;
    int lpos = l, rpos = mid + 1;
    for(int i = l; i <= r; i++) {
        if(tree[dep][i] < sorted[mid])
            tree[dep + 1][lpos++] = tree[dep][i];
        else if(tree[dep][i] == sorted[mid] && same) {
            tree[dep + 1][lpos++] = tree[dep][i];
            same--;
        }
        else tree[dep + 1][rpos++] = tree[dep][i];
        toleft[dep][i] = toleft[dep][l - 1] + lpos - l;
    }
    build(l, mid, dep + 1);
    build(mid + 1, r, dep + 1);
}
// [L,R]里查询子区间[l,r]第k小的数
int query(int L, int R, int l, int r, int dep, int k)
{
    if(l == r) return tree[dep][l];
    int mid = (L + R) / 2;
    // 有多少个查询区间内的节点会进入下一层的左子树
    int cnt = toleft[dep][r] - toleft[dep][l - 1];
    if(cnt >= k) {
        int newl = L + toleft[dep][l - 1] - toleft[dep][L - 1];
        int newr = newl + cnt - 1;
        return query(L, mid, newl, newr, dep + 1, k);
    }
    else {
        int newr = r + toleft[dep][R] - toleft[dep][r];
        int newl = newr - (r - l - cnt);
        return query(mid + 1, R, newl, newr, dep + 1, k - cnt);
    }
}
int main() {
    int n, m;
    while(~scanf("%d%d", &n, &m)) {
        for(int i = 1; i <= n; i++) {
            scanf("%d", &sorted[i]);
            tree[0][i] = sorted[i];
        }
        sort(sorted + 1, sorted + n + 1);
        build(1, n, 0);
        while(m--) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", query(1, n, l, r, 0, k));
        }
    }
    return 0;
}
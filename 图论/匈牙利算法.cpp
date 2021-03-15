/*
1. 时间复杂度O(nm)
2. 邻接矩阵建双向边
3. ans为最大匹配数
*/
int mp[maxn][maxn]; // 图的存储矩阵
int n, m, ans;
bool vis[maxn]; // 当前搜索过程中是否被访问过
int link[maxn]; // y集合中的点在x集合中的匹配点 -1表示未匹配
 
bool find_(int x) {
    for (int i=1; i<=n; ++i) {
        if (mp[x][i] && !vis[i]) { // 有边相连
            vis[i] = 1; // 标记该点
            if (link[i] == -1 || find_(link[i])) { //该点未匹配 或者匹配的点能找到增光路
                link[i] = x; // 删掉偶数条边 加进奇数条边
                return true; // 找到增光路
            }
        }
    }
    return false;
}
 
void match() {
    //初始化
    ans = 0;
    memset(link, -1, sizeof(link));
 
    for (int i=1; i<=n; ++i) {
        memset(vis, 0, sizeof(vis)); // 从集合的每个点依次搜索
        if (find_(i)) // 如果能搜索到 匹配数加1
            ans++;
    }
    return;
}
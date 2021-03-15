/*
* 后缀自动机 Suffix Automation (SAM)
* 功能:
*   1. 多个串的最长公共子串
*   2. 统计不同子串数量
*   3. 统计子串出现次数
*   4. dfs2: 查询字典序第k大的子串（不考虑重复情况）
*   5. dfs3: 查询字典序第k大的子串（考虑重复情况）
*/

#include <bits/stdc++.h>
using namespace std;

namespace SAM {
    const int MAXLEN = 1e6 + 5;
    struct state {
        int len, link; 
        int next[26]; // 字符集很小时，常数优化
    } st[MAXLEN * 2];
    int sz, last;
    // sz: 状态总数 [0,sz)
    // last: 最后插入的状态编号

    int cnt[MAXLEN * 2], topo[MAXLEN * 2], d[MAXLEN * 2];
    // cnt: 从起点到节点表示的字符串在子串中出现的次数
    // topo: parent树中的拓扑序

    void sam_init() { // 初始化
        st[0].len = 0;
        st[0].link = -1;
        sz++; 
        last = 0;
    }

    void sam_extend(int c) { // 插入时是 ch-'a' 这种形式
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        cnt[cur] = 1; // 次数统计

        int p = last;
        while (p != -1 && !st[p].next[c]) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];

            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } 
            else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                for (int i = 0; i < 26; i++)
                    st[clone].next[i] = st[q].next[i];
                st[clone].link = st[q].link;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
        // ans += st[cur].len - st[st[cur].link].len; 统计不同子串的个数
    }

    void Topo_init() { // 求出parent树的Topo序
        int mx = 0;
        memset(d, 0, sizeof d);
        for (int i = 1; i < sz; i++) mx = max(mx, st[i].len), d[st[i].len]++;
        for (int i = 1; i <= mx; i++) d[i] += d[i-1];
        for (int i = 1; i < sz; i++) topo[d[st[i].len]--] = i;
   
        // 求出现次数
        for (int i = sz-1; i > 0; i--) cnt[st[topo[i]].link] += cnt[topo[i]];
    }
}
using namespace SAM;

void debug() {
    for (int i = 0; i < sz; i++) {
        for (int c = 0; c < 26; c++) {
            if(st[i].next[c]) {
                cout << i << " -- " << char(c+'a') << " --> " << st[i].next[c] << endl;
            }
        }
    }
}
int nlcs[MAXLEN * 2], lcs[MAXLEN * 2];
void calc(char t[]) { // 多个字符串的最长公共子串
    int m = strlen(t+1), now = 0, len = 0;
    for (int i = 0; i < sz; i++) nlcs[i] = 0;
    for (int i = 1; i <= m; i++) {
        if(st[now].next[t[i]-'a']) {
            len++;
            now = st[now].next[t[i]-'a'];
        }
        else {
            while(now && !st[now].next[t[i]-'a']) now = st[now].link;
            len = st[now].len;
            if(st[now].next[t[i]-'a']) {
                now = st[now].next[t[i]-'a'];
                len++;
            }
        }
        nlcs[now] = max(nlcs[now], len);
    }
    for (int i = sz-1; i > 0; i--) {
        int u = topo[i], v = st[topo[i]].link;
        nlcs[v] = max(nlcs[v], nlcs[u]);
    }
    for (int i = 0; i < sz; i++) lcs[i] = min(lcs[i], nlcs[i]);
}
int dp[MAXLEN * 2][2];
void dfs(int u) { 
    if(dp[u][0]) return ;
    if(u > 0) {
        dp[u][0] = 1;
        dp[u][1] = cnt[u];
    }
    for (char ch = 'a'; ch <= 'z'; ch++) {
        if(!st[u].next[ch-'a']) continue;
        int v = st[u].next[ch-'a'];
        // printf("u=%d, v=%d, ch=%c\n", u, v, ch);
        dfs(v);
        dp[u][0] += dp[v][0];
        dp[u][1] += dp[v][1];
    }
}
char s[MAXLEN], t[MAXLEN];
int main() {
    scanf("%s", s+1);
    int n = strlen(s+1);

    sam_init();
    for (int i = 1; i <= n; i++) sam_extend(s[i]-'a');
    for (int i = 0; i < sz; i++) lcs[i] = st[i].len;
    Topo_init();
    while(~scanf("%s", t+1)) {
        calc(t);
    }
    int ans = 0;
    for (int i = 0; i < sz; i++) ans = max(ans, lcs[i]);
    printf("%d\n", ans);
}

/*
void dfs(int u) { 
    if(dp[u][0]) return ;
    if(u > 0) {
        dp[u][0] = 1;
        dp[u][1] = cnt[u];
    }
    for (char ch = 'a'; ch <= 'z'; ch++) {
        if(!st[u].next[ch-'a']) continue;
        int v = st[u].next[ch-'a'];
        // printf("u=%d, v=%d, ch=%c\n", u, v, ch);
        dfs(v);
        dp[u][0] += dp[v][0];
        dp[u][1] += dp[v][1];
    }
}
void dfs2(int u, int k) {
    if(u > 0 && k == 1) return ;
    k -= (u > 0);
    for (char ch = 'a'; ch <= 'z'; ch++) {
        if(!st[u].next[ch-'a']) continue;
        int v = st[u].next[ch-'a'];
        // printf("ch=%c,v=%d,k=%d,dp=%d\n", ch, v, k, dp[v][op]);
        if(k > dp[v][0]) k -= dp[v][0];
        else {
            printf("%c", ch);
            dfs2(v, k);
            break;
        }
    }
}
void dfs3(int u, int k) {
    if(u > 0) {
        if(k <= cnt[u]) return ;
        k -= cnt[u];
    }
    for (char ch = 'a'; ch <= 'z'; ch++) {
        if(!st[u].next[ch-'a']) continue;
        int v = st[u].next[ch-'a'];
        if(k > dp[v][1]) k -= dp[v][1];
        else {
            printf("%c", ch);
            dfs3(v, k);
            break;
        }
    }
}
int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    sam_init();
    for (int i = 1; i <= n; i++) sam_extend(s[i]-'a');
    Topo();
    dfs(0);
    int op, k;
    while(~scanf("%d%d", &op, &k)) {
        if(!op) {
            if(dp[0][0] >= k) dfs2(0, k);
            else printf("-1");
        }
        else {
            if(dp[0][1] >= k) dfs3(0, k);
            else printf("-1");
        }
        printf("\n");
    }
}
*/
}
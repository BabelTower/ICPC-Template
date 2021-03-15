/*
在线
出现次数统计：可能会有重复的串，所以每个返回的节点加cnt
*/
#include <bits/stdc++.h>
using namespace std;
#define MAXN 600005
#define CHAR_NUM 26
char s[MAXN];
int rt[MAXN];
int cnt[MAXN], c[MAXN], id[MAXN];
// cnt[i]: 出现次数统计
int tot = 1,link[MAXN],len[MAXN],trans[MAXN][CHAR_NUM];
//link[i]: 后缀链接
//trans[i]: 状态转移数组
inline int insert(int ch, int last){
    if(trans[last][ch]){
        int p=last,x=trans[p][ch];
        if(len[p]+1==len[x])return x;//即最初的特判1
        else{
            int y=++tot;len[y]=len[p]+1;
            for(int i=0;i<26;++i)trans[y][i]=trans[x][i];
            while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
            link[y]=link[x],link[x]=y;
            return y;//即最初的特判2
        }
    }
    int z=++tot,p=last;len[z]=len[last]+1;
    while(p&&!trans[p][ch])trans[p][ch]=z,p=link[p];
    if(!p)link[z]=1;
    else{
        int x=trans[p][ch];
        if(len[p]+1==len[x])link[z]=x;
        else{
            int y=++tot;len[y]=len[p]+1;
            for(int i=0;i<26;++i)trans[y][i]=trans[x][i];
            while(p&&trans[p][ch]==x)trans[p][ch]=y,p=link[p];
            link[y]=link[x],link[z]=link[x]=y;
        }
    }
    return z;
}
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    scanf("%s", s+1);
    rt[1] = insert(s[1] - 'A', 1);
    for (int i = 2; i <= n; i++) {
        int u; scanf("%d", &u);
        rt[i] = insert(s[i] - 'A', rt[u]);
    }

    // 次数统计
    for (int i = 1; i <= n; i++) cnt[rt[i]]++;
    for (int i = 1; i <= tot; i++) c[i] = 0;
    for (int i = 1; i <= tot; i++) c[len[i]]++;
    for (int i = 2; i <= tot; i++) c[i] += c[i-1];
    for (int i = 1; i <= tot; i++) id[c[len[i]]--] = i;
    for (int i = tot; i >= 1; i--) {
        int u = id[i];
        cnt[link[u]] += cnt[u];
    }
    
    while (q--) {
        int X, L;
        scanf("%d%d", &X, &L);
        int p = rt[X];
        while(len[link[p]] >= L) {
            p = link[p];
        }
        printf("%d\n", cnt[p]);
    }
}

/*
* 题目: P6139 【模板】广义后缀自动机（广义 SAM）
* URL: https://www.luogu.com.cn/problem/P6139
* 题意: 统计多串的不同子串个数
*/
#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000000  // 双倍字符串长度
#define CHAR_NUM 30   // 字符集个数，注意修改下方的 (-'a')
struct exSAM {
  int len[MAXN];             // 节点长度
  int link[MAXN];            // 后缀链接，link
  int next[MAXN][CHAR_NUM];  // 转移
  int tot;                   // 节点总数：[0, tot)
  void init() {
    tot = 1;
    link[0] = -1;
  }
  int insertSAM(int last, int c) {
    int cur = next[last][c];
    if (len[cur]) return cur;
    len[cur] = len[last] + 1;
    int p = link[last];
    while (p != -1) {
      if (!next[p][c])
        next[p][c] = cur;
      else
        break;
      p = link[p];
    }
    if (p == -1) {
      link[cur] = 0;
      return cur;
    }
    int q = next[p][c];
    if (len[p] + 1 == len[q]) {
      link[cur] = q;
      return cur;
    }
    int clone = tot++;
    for (int i = 0; i < CHAR_NUM; ++i)
      next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;
    len[clone] = len[p] + 1;
    while (p != -1 && next[p][c] == q) {
      next[p][c] = clone;
      p = link[p];
    }
    link[clone] = link[q];
    link[cur] = clone;
    link[q] = clone;
    return cur;
  }
  int insertTrie(int cur, int c) {
    if (next[cur][c]) return next[cur][c];
    return next[cur][c] = tot++;
  }
  void insert(const string &s) {
    int root = 0;
    for (auto ch : s) root = insertTrie(root, ch - 'a');
  }
  void insert(const char *s, int n) {
    int root = 0;
    for (int i = 0; i < n; ++i) root = insertTrie(root, s[i] - 'a');
  }
  void build() {
    queue<pair<int, int>> q;
    for (int i = 0; i < 26; ++i)
      if (next[0][i]) q.push({i, 0});
    while (!q.empty()) {
      auto item = q.front();
      q.pop();
      auto last = insertSAM(item.second, item.first);
      for (int i = 0; i < 26; ++i)
        if (next[last][i]) q.push({i, last});
    }
  }
} T;
int main() {
  int n;
  scanf("%d", &n);
  T.init();
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    T.insert(s);
  }
  T.build();
  long long ans = 0;
  for (int i = 1; i < T.tot; i++) {
    ans += T.len[i] - T.len[T.link[i]];
  }
  printf("%lld\n", ans);
}
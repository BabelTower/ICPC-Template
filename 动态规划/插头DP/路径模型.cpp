/*
* 状态编码: 括号表示和最小表示
*/

/* 最小表示
* 长度m+1的整形数组，记录轮廓线上每个插头的状态
* 0表示没有插头，并约定连通的插头用相同的数字进行标记
* b[]: 轮廓线上插头的状态。
* bb[]: 在最小表示的编码的过程中，每个数字被映射到的最小数字。
* 注意: 0表示插头不存在，不能被映射成其他值。
*/
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; ++i)
const int M = 10;
const int offset = 3, mask = (1 << offset) - 1;
int n, m;
long long ans, d;
const int MaxSZ = 16796, Prime = 9973;
// MaxSz: 表示合法状态的上界，可以估计，也可以预处理出较为精确的值。
// Prime:  一个小于 MaxSZ 的大素数。
struct hashTable {
  int head[Prime], next[MaxSZ], sz;
  int state[MaxSZ];
  long long key[MaxSZ];
  // 初始化函数，和手写邻接表类似，我们只需要初始化表头节点的指针。
  inline void clear() {
    sz = 0;
    memset(head, -1, sizeof(head));
  }
  // 状态转移函数，其中d是一个全局变量，表示每次状态转移所带来的增量。如果找到的话就+=，否则就创建一个状态为s，关键字为d的新节点。
  inline void push(int s) {
    int x = s % Prime;
    for (int i = head[x]; ~i; i = next[i]) {
      if (state[i] == s) {
        key[i] += d;
        return;
      }
    }
    state[sz] = s, key[sz] = d;
    next[sz] = head[x];
    head[x] = sz++;
  }
  void roll() { REP(i, sz) state[i] <<= offset; }
} H[2], *H0, *H1;
int b[M + 1], bb[M + 1];
int encode() {
  int s = 0;
  memset(bb, -1, sizeof(bb));
  int bn = 1;
  bb[0] = 0;
  for (int i = m; i >= 0; --i) {
#define bi bb[b[i]]
    if (!~bi) bi = bn++;
    s <<= offset;
    s |= bi;
  }
  return s;
}
void decode(int s) {
  REP(i, m + 1) {
    b[i] = s & mask;
    s >>= offset;
  }
}
void push(int j, int dn, int rt) {
  b[j] = dn;
  b[j + 1] = rt;
  H1->push(encode());
}
int main() {
  cin >> n >> m;
  if (m > n) swap(n, m);
  H0 = H, H1 = H + 1;
  H1->clear();
  d = 1;
  H1->push(0);
  REP(i, n) {
    REP(j, m) {
      swap(H0, H1);
      H1->clear();
      REP(ii, H0->sz) {
        decode(H0->state[ii]); 	// 取出状态，并解码
        d = H0->key[ii];		// 得到增量 delta
        int lt = b[j], up = b[j + 1]; // 左插头，上插头
        bool dn = i != n - 1, rt = j != m - 1; // 下插头，右插头
        if (lt && up) {	// 如果左、上均有插头
          if (lt == up) { // 来自同一个连通块
            if (i == n - 1 && j == m - 1) { // 只有在最后一个格子时，才能合并，封闭回路。
              push(j, 0, 0);
            }
          } else { // 否则，必须合并这两个连通块，因为本题中需要回路覆盖
            REP(i, m + 1) if (b[i] == lt) b[i] = up;
            push(j, 0, 0);
          }
        } else if (lt || up) { // 如果左、上之中有一个插头
          int t = lt | up; // 得到这个插头
          if (dn) { // 如果可以向下延伸
            push(j, t, 0);
          }
          if (rt) { // 如果可以向右延伸
            push(j, 0, t);
          }
        } else { // 如果左、上均没有插头
          if (dn && rt) { // 生成一对新插头
            push(j, m, m);
          }
        }
      }
    }
    H1->roll();
  }
  assert(H1->sz <= 1);
  cout << (H1->sz == 1 ? H1->key[0] : 0) << endl;
}
/*
* 多条回路问题并不属于插头 DP，因为我们只需要和上面的骨牌覆盖问题一样，记录插头是否存在，然后成对的合并和生成插头就可以了。
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 11;
long long f[2][1 << (N + 1)], *f0, *f1;
int n, m;
int main() {
  int T;
  cin >> T;
  for (int Case = 1; Case <= T; ++Case) {
    cin >> n >> m;
    f0 = f[0];
    f1 = f[1];
    fill(f1, f1 + (1 << m + 1), 0);
    f1[0] = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        bool bad;
        cin >> bad;
        bad ^= 1;
        swap(f0, f1);
        fill(f1, f1 + (1 << m + 1), 0);
#define u f0[s]
        for (int s = 0; s < 1 << m + 1; ++s)
          if (u) {
            bool lt = s >> j & 1, up = s >> j + 1 & 1;
            if (bad) {
              if (!lt && !up) f1[s] += u;
            } else {
              f1[s ^ 3 << j] += u;
              if (lt != up) f1[s] += u;
            }
          }
      }
      swap(f0, f1);
      fill(f1, f1 + (1 << m + 1), 0);
      for (int s = 0; s < 1 << m; ++s) f1[s << 1] = u;
    }
    printf("Case %d: There are %lld ways to eat the trees.\n", Case, f1[0]);
  }
}
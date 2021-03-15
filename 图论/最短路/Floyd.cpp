/*
* 计算最短路径的基础算法，Floyd算法基础模板
*/
const int inf = 0x3f3f3f3f;
const int maxn = 1050;

int n, m;
int d[maxn][maxn];

void floyd() {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][j] < inf && d[k][j] < inf)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

/*
* 利用floyd可以求传递闭包，边权用1和0表示“连通”和“不连通”
*/

// std::bitset<SIZE> f[SIZE];
for (k = 1; k <= n; k++)
  for (i = 1; i <= n; i++)
    if (f[i][k]) f[i] = f[i] | f[k];
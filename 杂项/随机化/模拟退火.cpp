/*
* 题目: [JSOI2004]平衡点 / 吊打XXX
* URL: https://www.luogu.com.cn/problem/P1337
* 温度T的初始值设置问题: 
*   1. 初始温度高，则搜索到全局最优解的可能性大，但因此要花费大量的计算时间；
*   2. 反之，则可节约计算时间，但全局搜索性能可能受到影响。
* 退火速度问题: 
*   1. 模拟退火算法的全局搜索性能也与退火速度密切相关。同一温度下的“充分”搜索(退火)是相当必要的，但这需要计算时间。
* 温度管理问题: 
*   1. 降温系数应为正的略小于1.00的常数。
* 注意: 
*   1. 为了使得解更为精确，我们通常不直接取当前解作为答案，而是在退火过程中维护遇到的所有解的最优值。
*   2. 有时为了使得到的解更有质量，会在模拟退火结束后，以当前温度在得到的解附近多次随机状态，尝试得到更优的解（其过程与模拟退火相似）。
* 技巧:
*   1. 分块模拟退火，将值域分为几段，每段跑一遍模拟退火，再取最优解。
*   2. 卡时可以把主程序中的 simulateAnneal(); 换成 while ((double)clock()/CLOCKS_PER_SEC < MAX_TIME) simulateAnneal();。这样子就会一直跑模拟退火，直到用时即将超过时间限制。
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 10005;
const double MAX_TIME = 4.5; // 这里的 MAX_TIME 是一个自定义的略小于时限的数。
int n, x[N], y[N], w[N];
double ansx, ansy, dis;

double Rand() { return (double)rand() / RAND_MAX; }
// 因为物重一定，绳子越短，重物越低，势能越小，势能又与物重成正比。
// 所以，只要使得sum{dist[i]*weight[i]}也就是总的重力势能最小，就可以使系统平衡。
double calc(double xx, double yy)
{
  double res = 0;
  for (int i = 1; i <= n; ++i)
  {
    double dx = x[i] - xx, dy = y[i] - yy;
    res += sqrt(dx * dx + dy * dy) * w[i];
  }
  if (res < dis)
    dis = res, ansx = xx, ansy = yy;
  return res;
}
void simulateAnneal()
{
  double t = 100000;
  double nowx = ansx, nowy = ansy;
  while (t > 0.001)
  {
    // 随机变化坐标，变化幅度为 T 。
    double nxtx = nowx + t * (Rand() * 2 - 1);
    double nxty = nowy + t * (Rand() * 2 - 1);
    // 计算新解与当前解的差 DE。
    double delta = calc(nxtx, nxty) - calc(nowx, nowy);
    // 如果新解比当前解优(DE > 0)，就用新解替换当前解。
    // 否则以 exp(DE / T) 的概率用新解替换当前解。
    if (exp(-delta / t) > Rand())
      nowx = nxtx, nowy = nxty;
    // 温度乘上一个小于1的系数，即降温。
    t *= 0.97;
  }
  for (int i = 1; i <= 1000; ++i)
  {
    double nxtx = ansx + t * (Rand() * 2 - 1);
    double nxty = ansy + t * (Rand() * 2 - 1);
    calc(nxtx, nxty);
  }
}
int main()
{
  srand(time(0));
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d%d%d", &x[i], &y[i], &w[i]);
    ansx += x[i], ansy += y[i];
  }
  ansx /= n, ansy /= n, dis = calc(ansx, ansy);
  while ((double)clock()/CLOCKS_PER_SEC < MAX_TIME)
  simulateAnneal();
  printf("%.3lf %.3lf\n", ansx, ansy);
  return 0;
}
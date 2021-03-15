
/*
* URL: https://zoj.pintia.cn/problem-sets/91827364500/problems/91827368253
* 题意：
* 有三个骰子，分别有k1,k2,k3个面。
* 每次掷骰子，如果三个面分别为a,b,c则分数置0，否则加上三个骰子的分数之和。
* 当分数大于n时结束。求游戏的期望步数。初始分数为0
* 分析：
* 假设dp[i]表示拥有分数i到游戏结束的期望步数
* 则
* (1):dp[i]=SUM(p[k]*dp[i+k])+p[0]*dp[0]+1;//p[k]表示增加分数为k的概率,p[0]表示分数变为0的概率
* 假定
* (2):dp[i]=A[i]*dp[0]+B[i];
* 则
* (3):dp[i+k]=A[i+k]*dp[0]+B[i+k];
* 将(3)代入(1)得：
* (4):dp[i]=(SUM(p[k]*A[i+k])+p[0])*dp[0]+SUM(p[k]*B[i+k])+1;
* 将4与2做比较得：
* A[i]=(SUM(p[k]*A[i+k])+p[0]);
* B[i]=SUM(p[k]*B[i+k])+1;
* 当i+k>n时A[i+k]=B[i+k]=0可知
* 所以dp[0]=B[0]/(1-A[0])可求出
*************************************************************************
总结下这类概率DP:
既DP[i]可能由DP[i+k]和DP[i+j]需要求的比如DP[0]决定
相当于概率一直递推下去会回到原点
比如
(1):DP[i]=a*DP[i+k]+b*DP[0]+d*DP[i+j]+c;
但是DP[i+k]和DP[0]都是未知
这时候根据DP[i]的方程式假设一个方程式：
比如:
(2):DP[i]=A[i]*DP[i+k]+B[i]*DP[0]+C[i];
因为要求DP[0],所以当i=0的时候但是A[0],B[0],C[0]未知
对比(1)和(2)的差别
这时候对比(1)和(2)发现两者之间的差别在于DP[i+j]
所以根据(2)求DP[i+j]然后代入(1)消除然后对比(2)就可以得到A[i],B[i],C[i]
然后视具体情况根据A[i],B[i],C[i]求得A[0],B[0],C[0]继而求DP[0]
请看这题：http://acm.hdu.edu.cn/showproblem.php?pid=4035
*************************************************************************
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 505;
const double eps = 1e-9;
double p[40], A[N], B[N];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(p, 0, sizeof(p));
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        int n, k1, k2, k3, a, b, c;
        scanf("%d%d%d%d%d%d%d", &n, &k1, &k2, &k3, &a, &b, &c);
        p[0] = 1.0 / (k1 * k2 * k3);
        for (int i = 1; i <= k1; i++) {
            for (int j = 1; j <= k2; j++) {
                for (int k = 1; k <= k3; k++) {
                    int sum = i + j + k;
                    p[sum] += p[0];
                }
            }
        }
        p[a+b+c] -= p[0];
        
        
        for (int i = n; i >= 0; i--) {
            A[i] = p[0];
            B[i] = 1;
            for (int k = 3; k <= k1 + k2 + k3; k++) {
                if(i+k > n) {
                    break; // 注意精度
                }
                A[i] += p[k] * A[i+k];
                B[i] += p[k] * B[i+k];
            }
        }
        printf("%.15f\n", B[0]/(1-A[0]));
    }
}


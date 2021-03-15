/*
HDU 4035

    dp求期望的题。
    题意：
    有n个房间，由n-1条隧道连通起来，实际上就形成了一棵树，
    从结点1出发，开始走，在每个结点i都有3种可能：
        1.被杀死，回到结点1处（概率为ki）
        2.找到出口，走出迷宫 （概率为ei）
        3.和该点相连有m条边，随机走一条
    求：走出迷宫所要走的边数的期望值。

    设 E[i]表示在结点i处，要走出迷宫所要走的边数的期望。E[1]即为所求。

    叶子结点：
    E[i] = ki*E[1] + ei*0 + (1-ki-ei)*(E[father[i]] + 1);
         = ki*E[1] + (1-ki-ei)*E[father[i]] + (1-ki-ei);

    非叶子结点：（m为与结点相连的边数）
    E[i] = ki*E[1] + ei*0 + (1-ki-ei)/m*( E[father[i]]+1 + ∑( E[child[i]]+1 ) );
         = ki*E[1] + (1-ki-ei)/m*E[father[i]] + (1-ki-ei)/m*∑(E[child[i]]) + (1-ki-ei);

    设对每个结点：E[i] = Ai*E[1] + Bi*E[father[i]] + Ci;

    对于非叶子结点i，设j为i的孩子结点，则
    ∑(E[child[i]]) = ∑E[j]
                   = ∑(Aj*E[1] + Bj*E[father[j]] + Cj)
                   = ∑(Aj*E[1] + Bj*E[i] + Cj)
    带入上面的式子得
    (1 - (1-ki-ei)/m*∑Bj)*E[i] = (ki+(1-ki-ei)/m*∑Aj)*E[1] + (1-ki-ei)/m*E[father[i]] + (1-ki-ei) + (1-ki-ei)/m*∑Cj;
    由此可得
    Ai =        (ki+(1-ki-ei)/m*∑Aj)   / (1 - (1-ki-ei)/m*∑Bj);
    Bi =        (1-ki-ei)/m            / (1 - (1-ki-ei)/m*∑Bj);
    Ci = ( (1-ki-ei)+(1-ki-ei)/m*∑Cj ) / (1 - (1-ki-ei)/m*∑Bj);

    对于叶子结点
    Ai = ki;
    Bi = 1 - ki - ei;
    Ci = 1 - ki - ei;

    从叶子结点开始，直到算出 A1,B1,C1;

    E[1] = A1*E[1] + B1*0 + C1;
    所以
    E[1] = C1 / (1 - A1);
    若 A1趋近于1则无解...

*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
const double eps = 1e-9;
vector<int> g[N];
double k[N], e[N];
double A[N], B[N], C[N];
bool dfs(int u, int fa) {
    int m = g[u].size();
    A[u] = k[u];
    B[u] = (1 - k[u] - e[u]) / m;
    C[u] = 1 - k[u] - e[u];
    double tmp = 1;
    for (auto v : g[u]) {
        if(v == fa) continue;
        if(!dfs(v, u)) return false;
        A[u] += (1-k[u]-e[u])/m*A[v];
        C[u] += (1-k[u]-e[u])/m*C[v];
        tmp -= (1-k[u]-e[u])/m*B[v];
    }
    if(fabs(tmp)<eps) return false;
    A[u] /= tmp;
    B[u] /= tmp;
    C[u] /= tmp;
    return true;
}
int main() {
    int T, kase = 0;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        for (int i = 1; i <= n; i++) {
            int ki, ei;
            scanf("%d%d", &ki, &ei);
            k[i] = ki / 100.0;
            e[i] = ei / 100.0;
        }
        printf("Case %d: ", ++kase);
        if(dfs(1, 0) && fabs(1-A[1])>eps) {
            printf("%.6lf\n", C[1]/(1-A[1]));
        }
        else {
            puts("impossible");
        }
    }
}

/*
    注意空间问题
    二维线段树求区间最值问题（可修）。
    给你一个n*n的初始矩阵，支持三种操作    
    单点修改某个位置的值（或者加上一个值）
    查询子矩阵最小值和最大值，或者查询子矩阵的和
    测试题目：hdu 4819 && poj 1195
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1024 + 5;
ll MAX[N << 2][N << 2], minV, maxV,MIN[N<<2][N<<2];//维护最值
ll a[N<<2][N<<2];//初始矩阵
ll SUM[N<<2][N<<2],sumV;//维护求和
int n;
void pushupX(int deep, int rt)
{
    MAX[deep][rt] = max(MAX[deep << 1][rt], MAX[deep << 1 | 1][rt]);
    MIN[deep][rt] = min(MIN[deep << 1][rt], MIN[deep << 1 | 1][rt]);
    SUM[deep][rt] = SUM[deep<<1][rt]+SUM[deep<<1|1][rt];
}
void pushupY(int deep, int rt)
{
    MAX[deep][rt] = max(MAX[deep][rt << 1], MAX[deep][rt << 1 | 1]);
    MIN[deep][rt] = min(MIN[deep][rt << 1], MIN[deep][rt << 1 | 1]);
    SUM[deep][rt]=SUM[deep][rt<<1]+SUM[deep][rt<<1|1];
}
void buildY(int ly, int ry, int deep, int rt, int flag)
{
    //y轴范围ly,ry;deep,rt;标记flag
    if (ly == ry){
        if (flag!=-1)
            MAX[deep][rt] = MIN[deep][rt] = SUM[deep][rt] = a[flag][ly];
        else
            pushupX(deep, rt);
        return;
    }
    int m = (ly + ry) >> 1;
    buildY(ly, m, deep, rt << 1, flag);
    buildY(m + 1, ry, deep, rt << 1 | 1, flag);
    pushupY(deep, rt);
}
void buildX(int lx, int rx, int deep)
{
    //建树x轴范围lx,rx;deep
    if (lx == rx){
        buildY(1, n, deep, 1, lx);
        return;
    }
    int m = (lx + rx) >> 1;
    buildX(lx, m, deep << 1);
    buildX(m + 1, rx, deep << 1 | 1);
    buildY(1, n, deep, 1, -1);
}
void updateY(int Y, int val, int ly, int ry, int deep, int rt, int flag)
{
    //单点更新y坐标;更新值val;当前操作y的范围ly,ry;deep,rt;标记flag
    if (ly == ry){
        if (flag) //注意读清楚题意，看是单点修改值还是单点加值
            MAX[deep][rt] = MIN[deep][rt] = SUM[deep][rt] = val;
        else pushupX(deep, rt);
        return;
    }
    int m = (ly + ry) >> 1;
    if (Y <= m)
        updateY(Y, val, ly, m, deep, rt << 1, flag);
    else
        updateY(Y, val, m + 1, ry, deep, rt << 1 | 1, flag);
    pushupY(deep, rt);
}
void updateX(int X, int Y, int val, int lx, int rx, int deep)
{
    //单点更新范围x,y;更新值val;当前操作x的范围lx,rx;deep
    if (lx == rx){
        updateY(Y, val, 1, n, deep, 1, 1);
        return;
    }
    int m = (lx + rx) >> 1;
    if (X <= m)
        updateX(X, Y, val, lx, m, deep << 1);
    else
        updateX(X, Y, val, m + 1, rx, deep << 1 | 1);
    updateY(Y, val, 1, n, deep, 1, 0);
}
void queryY(int Yl, int Yr, int ly, int ry, int deep, int rt)
{
    //询问区间y轴范围y1,y2;当前操作y的范围ly,ry;deep,rt
    if (Yl <= ly && ry <= Yr)
    {
        minV = min(MIN[deep][rt], minV);
        maxV = max(MAX[deep][rt], maxV);
        sumV += SUM[deep][rt];
        return;
    }
    int m = (ly + ry) >> 1;
    if (Yl <= m)
        queryY(Yl, Yr, ly, m, deep, rt << 1);
    if (m < Yr)
        queryY(Yl, Yr, m + 1, ry, deep, rt << 1 | 1);
}
void queryX(int Xl, int Xr, int Yl, int Yr, int lx, int rx, int rt)
{
    //询问区间范围x1,x2,y1,y2;当前操作x的范围lx,rx;rt
    if (Xl <= lx && rx <= Xr){
        queryY(Yl, Yr, 1, n, rt, 1);
        return;
    }
    int m = (lx + rx) >> 1;
    if (Xl <= m)
        queryX(Xl, Xr, Yl, Yr, lx, m, rt << 1);
    if (m < Xr)
        queryX(Xl, Xr, Yl, Yr, m + 1, rx, rt << 1 | 1);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%lld",&a[i][j]);
    buildX(1,n,1);
    int m;
    scanf("%d",&m);
    while(m--){
        int opt;
        scanf("%d",&opt);
        if(opt==1){ //单点修改
            int x,y,val;
            scanf("%d%d%d",&x,&y,&val);
            updateX(x,y,val,1,n,1);
        }
        else if(opt==2){//查询子矩阵最值，以及和
            minV=INF,maxV=-INF,sumV=0;//注意初始化
            int x1,y1,x2,y2;//注意看清楚给范围的方式以及下标是从0开始还是从1开始
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            queryX(x1,x2,y1,y2,1,n,1);
            printf("%lld %lld %lld\n",sumV,minV,maxV);
        }
        
    }
    return 0;
}
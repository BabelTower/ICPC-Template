/*
* 模版: 高斯消元法解方程组(Gauss-Jordan elimination).
* 返回值: 
*   -2表示有浮点数解，但无整数解
*   -1表示无解
*   0表示唯一解
*   大于0表示无穷解，并返回自由变元的个数
* 初始化: 有equ个方程，var个变元。增广矩阵行数为equ,分别为0到equ-1,列数为var+1,分别为0到var.
* 注意: 参数不能重复使用，每次都要重新赋值
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10;
int a[MAXN][MAXN];//增广矩阵
int x[MAXN];//解集
bool free_x[MAXN];//标记是否是不确定的变元
int gcd(int a,int b) {
    return b ? gcd(b, a%b) : a;
}
int lcm(int a,int b) {
    return a/gcd(a,b)*b;//先除后乘防溢出
}

int Gauss(int equ, int var) {
    int i,j,k;
    int max_r;// 当前这列绝对值最大的行.
    int col;//当前处理的列
    int ta,tb;
    int LCM;
    int temp;
    int free_x_num;
    int free_index;
    for(int i=0;i<=var;i++) {
        x[i]=0;
        free_x[i]=true;
    }
    //转换为阶梯阵.
    col=0; // 当前处理的列
    for(k = 0;k < equ && col < var;k++,col++) { // 枚举当前处理的行.
	// 找到该col列元素绝对值最大的那行与第k行交换.(为了在除法时减小误差)
        max_r=k;
        for(i=k+1;i<equ;i++) {
            if(abs(a[i][col])>abs(a[max_r][col])) max_r=i;
        }
        if(max_r!=k) {// 与第k行交换
            for(j=k;j<var+1;j++) swap(a[k][j],a[max_r][j]);
        }
        if(a[k][col]==0) {// 说明该col列第k行以下全是0了，则处理当前行的下一列.
            k--;
            continue;
        }
        for(i=k+1;i<equ;i++) {// 枚举要删去的行.
            if(a[i][col]!=0)
            {
                LCM = lcm(abs(a[i][col]),abs(a[k][col]));
                ta = LCM/abs(a[i][col]);
                tb = LCM/abs(a[k][col]);
                if(a[i][col]*a[k][col]<0)tb=-tb;//异号的情况是相加
                for(j=col;j<var+1;j++)
                {
                    a[i][j] = a[i][j]*ta-a[k][j]*tb;
                }
            }
        }
    }
    // 1. 无解的情况: 化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0).
    for (i = k; i < equ; i++)
    { // 对于无穷解来说，如果要判断哪些是自由变元，那么初等行变换中的交换就会影响，则要记录交换.
        if (a[i][col] != 0) return -1;
    }
    // 2. 无穷解的情况: 在var * (var + 1)的增广阵中出现(0, 0, ..., 0)这样的行，即说明没有形成严格的上三角阵.
    // 且出现的行数即为自由变元的个数.
    if (k < var)
    {
        // 首先，自由变元有var - k个，即不确定的变元至少有var - k个.
        for (i = k - 1; i >= 0; i--)
        {
            // 第i行一定不会是(0, 0, ..., 0)的情况，因为这样的行是在第k行到第equ行.
            // 同样，第i行一定不会是(0, 0, ..., a), a != 0的情况，这样的无解的.
            free_x_num = 0; // 用于判断该行中的不确定的变元的个数，如果超过1个，则无法求解，它们仍然为不确定的变元.
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && free_x[j]) free_x_num++, free_index = j;
            }
            if (free_x_num > 1) continue; // 无法求解出确定的变元.
            // 说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的.
            temp = a[i][var];
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && j != free_index) temp -= a[i][j] * x[j];
            }
            x[free_index] = temp / a[i][free_index]; // 求出该变元.
            free_x[free_index] = 0; // 该变元是确定的.
        }
        return var - k; // 自由变元有var - k个.
    }
    // 3. 唯一解的情况: 在var * (var + 1)的增广阵中形成严格的上三角阵.
    // 计算出Xn-1, Xn-2 ... X0.
    for (i = var - 1; i >= 0; i--)
    {
        temp = a[i][var];
        for (j = i + 1; j < var; j++)
        {
            if (a[i][j] != 0) temp -= a[i][j] * x[j];
        }
        if (temp % a[i][i] != 0) return -2; // 说明有浮点数解，但无整数解.
        x[i] = temp / a[i][i];
    }
    return 0;
}

/*
* 模版: 解对P取模的方程组
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
typedef long long ll;
int equ, var;
int a[N][N];
int b[N][N];
int x[N];
int free_x[N];
int free_num;
int n;
int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}
int Gauss(int P) {
    int max_r, col, k;
    free_num = 0;
    for (k = 0, col = 0; k < equ && col < var; k++, col++) {
        max_r = k;
        for (int i = k + 1; i < equ; i++) {
            if(abs(a[i][col]) > abs(a[max_r][col])) max_r = i;
        }
        if(a[max_r][col] == 0) {
            k--;
            free_x[free_num++] = 0;
            continue;
        }
        if(max_r != k) {
            for (int j = col; j < var+1; j++) {
                swap(a[k][j], a[max_r][j]);
            }
        }
        for (int i = k+1; i < equ; i++) {
            if(a[i][col] != 0) {
                int LCM = lcm(abs(a[i][col]), abs(a[k][col]));
                int ta = LCM / abs(a[i][col]);
                int tb = LCM / abs(a[k][col]);
                if(a[i][col] * a[k][col] < 0) tb = -tb;
                for (int j = col; j < var+1; j++) {
                    a[i][j] = (a[i][j]*ta-a[k][j]*tb)%P;
                    a[i][j] = (a[i][j] + P) % P;
                }
            }
        }
    }
    for (int i = k; i < equ; i++) {
        if(a[i][col] != 0) return -1;
    }
    if(k < var) return var-k;
    for (int i = var-1; i >= 0; i--) {
        ll temp = a[i][var];
        for (int j = i+1; j < var; j++) {
            temp = (temp - a[i][j] * x[j]) % P;
            temp = (temp + P) % P;
        }
        while(temp % a[i][i]) temp += P;
        temp /= a[i][i];
        temp %= P;
        x[i] = temp;
    }
    return 0;
}
void init() {
    memset(a, 0, sizeof a);
    memset(x, 0, sizeof x);
    equ = n;
    var = n;
}
void debug() {
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= n; j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}

/*
* 高斯消元实数版本
*/
const double EPS = 1e-8;
typedef vector<double> vec;
typedef vector<vec> mat;
//解 Ax = b
//无解或无穷多解时返回一个长度为0的数组
vec gauss_jordan(const mat& A, const vec& b) {
    int n = A.size();
    mat B(n, vec(n + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];
    for (int i = 0; i < n; i++) B[i][n] = b[i];
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i; j < n; j++) {
            if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
        }
        swap(B[i], B[pivot]);
        if (abs(B[i][i]) < EPS) return vec();//无解或无穷多解
        for (int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (!B[j][i]) continue;
                for (int k = i + 1; k <= n; k++)
                    B[j][k] -= B[j][i] * B[i][k];
            }
        }
    }
    vec x(n);
    for (int i = 0; i < n; i++) x[i] = B[i][n];
    return x;
}
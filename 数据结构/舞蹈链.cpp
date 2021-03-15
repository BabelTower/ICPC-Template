#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
 
const int N = 9;
const int MaxN = N * N * N + 10;
const int MaxM = N * N * 4 + 10;
const int maxnode = MaxN * 4 + MaxM + 10;
char g[MaxN];
struct DLX {
    int n, m, size;
    int U[maxnode], D[maxnode], R[maxnode], L[maxnode], Row[maxnode], Col[maxnode];
	// up, down, right, left, 行号, 列号
    int H[MaxN], S[MaxM]; // S是列中1的个数
    int ansd, ans[MaxN]; // 辅助数组
    void init(int _n, int _m) { // n是列数，m是行数
        n = _n;
        m = _m;
        for(int i = 0; i <= m; ++i) { // 初始化列标
            S[i] = 0; // ？？
            U[i] = D[i] = i; // ？？
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0;
        L[0] = m; // 循环双向链表
        size = m;
        for(int i = 1; i <= n; ++i)
            H[i] = -1; // 是否是第0列，及第i列是否有首个元素
    }
 
    void Link(int r, int c) {
        ++S[Col[++size] = c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)
            H[r] = L[size] = R[size] = size;
        else {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
 
    void remove(int c) { // 删除列标c上有1的行的所有元素
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }
 
    void resume(int c) { // 恢复列标c上有1的行的所有元素
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                ++S[Col[U[D[j]] = D[U[j]] = j]];
        L[R[c]] = R[L[c]] = c;
    }
 
    bool Dance(int d) { // d是深度
        if(R[0] == 0) { // 如果head.right = head
            for(int i = 0; i < d; ++i)
                g[(ans[i] - 1) / 9] = (ans[i] - 1) % 9 + '1';
            for(int i = 0; i < N * N; ++i)
                printf("%c", g[i]);
            printf("\n");
            return true;
        }
        int c = R[0]; // c = head.right
        for(int i = R[0]; i != 0; i = R[i]) {
            if(S[i] < S[c]) c = i; // 最优化，列中1的个数最多
        }
        remove(c); // 删除列标c
        for(int i = D[c]; i != c; i = D[i]) { // 循环列标c中所有的行号
            ans[d] = Row[i]; // 记录答案
            for(int j = R[i]; j != i; j = R[j])
                remove(Col[j]); // 删除列标
            if(Dance(d + 1)) return true;
            for(int j = L[i]; j != i; j = L[j])
                resume(Col[j]); // 恢复列标
        }
        resume(c); // 恢复列标
        return false;
    }
};
 
void place(int &r, int &c1, int &c2, int &c3, int &c4, int i, int j, int k) {
    r = (i * N + j) * N + k;
    c1 = i * N + j + 1;
    c2 = N * N + i * N + k;
    c3 = N * N * 2 + j * N + k;
    c4 = N * N * 3 + ((i / 3) * 3 + (j / 3)) * N + k;
}
 
DLX dlx;
 
int main() {
    while(~scanf("%s", &g)) {
        if(g[0] == 'e')
            exit(0);
        dlx.init(N * N * N, N * N * 4);
        int r, c1, c2, c3, c4;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                for(int k = 1; k <= N; ++k) {
                    if(g[i * N + j] == '.' || g[i * N + j] == '0' + k) {
                        place(r, c1, c2, c3, c4, i, j, k);
                        dlx.Link(r, c1);
                        dlx.Link(r, c2);
                        dlx.Link(r, c3);
                        dlx.Link(r, c4);
                    }
 
                }
            }
        }
        dlx.Dance(0);
    }
    return 0;
}


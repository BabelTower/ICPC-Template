#include <bits/stdc++.h>
using namespace std;
//埃式筛法
//求n以内的质数的个数
const int maxn = 1e8 + 5;
int p;
int prime[maxn/10];
bool is_prime[maxn];
  
int GetPrime(int n)
{
    p = 0;
    for (int i = 0; i <= n; ++i) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i <= n; ++i)
        if (is_prime[i])
            for (int j = i*i; j <= n; j += i)
                is_prime[j] = false;
    for (int i = 0; i <= n; ++i)
        if (is_prime[i])
            prime[p++] = i;
    return p;
}



int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    GetPrime(n);
    while (q--) {
        int k;
        scanf("%d", &k);
        printf("%d\n", prime[--k]);
    }
}
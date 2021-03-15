/*
* GarsiaWachs算法专门解决石子合并问题
*/
#include <bits/stdc++.h>
using namespace std;

int n, k, j;
int ans, sum;
vector<int> v;

int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

int main()
{
    n = read();
    v.push_back(INT_MAX - 1);
    for (int i = 1; i <= n; i++)
        v.push_back(read());
    v.push_back(INT_MAX);

    while (n-- > 1)
    {
        for (k = 1; k <= n; k++)
            if (v[k - 1] < v[k + 1])
                break;
        sum = v[k] + v[k - 1];
        for (j = k - 1; j >= 0; j--)
            if (v[j] > v[k] + v[k - 1])
                break;
        v.erase(v.begin() + k - 1);
        v.erase(v.begin() + k - 1);
        v.insert(v.begin() + j + 1, sum);
        ans += sum;
    }
    
    printf("%d", ans);
    return 0;
}
/*
 Lyndon 分解
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e6 + 5;
char s[N];
int n, ans;
int main()
{
    scanf("%s", s+1);
    n = (int)strlen(s+1);
    for(int i = 1; i <= n; ) {
        int j = i, k = i + 1;
        while(k <= n && s[j] <= s[k]) {
            if(s[j] < s[k]) j = i;
            else j++;
            k++;
        }
        while(i <= j) {
            ans ^= i + k - j - 1; //右端点的位置
            i += k - j;
        }
    }
    printf("%d\n", ans);
    return 0;
}

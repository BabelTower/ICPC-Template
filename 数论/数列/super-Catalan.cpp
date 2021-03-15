/*
超级卡特兰数（又称大施罗德数）
*/

const int maxn=3e5;
typedef long long LL;
#define mod 998244353

LL num[maxn];

LL inverse(LL x,LL y)///快速幂加费马小定理求逆元
{
    LL sum=1;
    
    while(y)
    {
        
        if(y&1) sum=sum*x%mod;
        
        y/=2;
        x=x*x%mod;
        
    }
    return sum%mod;
}


int main()
{
    int n;
    
    while(~scanf("%d",&n))
    {
        num[1]=num[0]=1;
        if(n==1) {
            printf("1\n");continue;
        }
        
        for(int i=2;i<=n;i++)
        {
            num[i]=((6*i-3)*num[i-1]%mod-(i-2)*num[i-2]%mod+mod)%mod*inverse(i+1,mod-2)%mod;
        }
        
        printf("%lld\n",num[n-1]*2%mod);
    }
    return 0;
}


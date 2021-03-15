/*
	适用于n,m，p较大的情况，复杂度大概为O(mlogn)
*/

const ll p = (ll)1e9 + 7;
ll pow(ll a, ll b, ll m)
{
    ll ans = 1;
    a %= m;
    while(b)
    {
        if(b & 1)ans = (ans % m) * (a % m) % m;
        b /= 2;
        a = (a % m) * (a % m) % m;
    }
    ans %= m;
    return ans;
}
ll inv(ll x, ll p)//x关于p的逆元，p为素数
{
    return pow(x, p - 2, p);
}
ll C(ll n, ll m, ll p)//组合数C(n, m) % p
{
    if(m > n)return 0;
    ll up = 1, down = 1;//分子分母;
    for(int i = n - m + 1; i <= n; i++)up = up * i % p;
    for(int i = 1; i <= m; i++)down = down * i % p;
    return up * inv(down, p) % p;
}
ll Lucas(ll n, ll m, ll p)
{
    if(m == 0)return 1;
    return C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
}
int main()
{
	long long n,m;	
	while(~scanf("%lld%lld",&n,&m))
	{
		printf("%lld\n",Lucas(n,m,p));
	}
	return 0;
}


/*
    打表版，适用于n,m较大，p<10^6情况。复杂度为O(logn)
*/
const int maxn = 1e5 + 10;
const ll p = (ll)13;
ll fac[maxn];//阶乘打表
void init(ll p)//此处的p应该小于1e5，这样Lucas定理才适用
{
    fac[0] = 1;
    for(int i = 1; i <= p; i++)
        fac[i] = fac[i - 1] * i % p;
}
ll pow(ll a, ll b, ll m)
{
    ll ans = 1;
    a %= m;
    while(b)
    {
        if(b & 1)ans = (ans % m) * (a % m) % m;
        b /= 2;
        a = (a % m) * (a % m) % m;
    }
    ans %= m;
    return ans;
}
ll inv(ll x, ll p)//x关于p的逆元，p为素数
{
    return pow(x, p - 2, p);
}
ll C(ll n, ll m, ll p)//组合数C(n, m) % p
{
    if(m > n)return 0;
    return fac[n] * inv(fac[m] * fac[n - m], p) % p;
}
ll Lucas(ll n, ll m, ll p)
{
    if(m == 0)return 1;
    return C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
}
int main()
{
    ll n,m;
    init(p);    
    while(~scanf("%lld%lld",&n,&m))
    {
        printf("%lld\n",Lucas(n,m,p));
    }
    return 0;
}




/*
	适用于N<=3000【打表】
	c[i][j]表示从i个中选j个的选法。
*/
 
long long C[N][N];
 
void get_C(int maxn)
{
    C[0][0] = 1;
    for(int i=1;i<=maxn;i++)
    {
        C[i][0] = 1;
        for(int j=1;j<=i;j++)
            C[i][j] = C[i-1][j]+C[i-1][j-1];
            //C[i][j] = (C[i-1][j]+C[i-1][j-1])%MOD;
    }
}

/*
	n<=200000【求值】
*/

ll fac[maxn],inv[maxn];
ll pow_mod(ll a,ll n)
{
    ll ret =1;
    while(n)
    {
        if(n&1) ret=ret*a%mod;
          a=a*a%mod;
          n>>=1;
    }
    return ret;
}
void init()
{
    fac[0]=1;
    for(int i=1;i<maxn;i++)
    {
        fac[i]=fac[i-1]*i%mod;
    }
}
ll Cc(ll x, ll y)
{
    return fac[x]*pow_mod(fac[y]*fac[x-y]%mod,mod-2)%mod;
}
 
int main(){
    ll n,m;
    init();
    while(1){
        cin>>n>>m;
        cout<<Cc(n,m)<<endl;
    }
}


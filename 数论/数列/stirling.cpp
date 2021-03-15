/*
第一类斯特林数 S1(n,m) 表示的是将 n 个不同元素构成 m 个圆排列的数目。
*/

const int mod=1e9+7;//取模
LL s[N][N];//存放要求的第一类Stirling数
void init(){
    memset(s,0,sizeof(s));
    s[1][1]=1;
    for(int i=2;i<=N-1;i++){
        for(int j=1;j<=i;j++){
            s[i][j]=s[i-1][j-1]+(i-1)*s[i-1][j];
            if(s[i][j]>=mod)
                s[i][j]%=mod;
        }
    }
}

/*
第二类斯特林数 S2(n,m) 表示的是把 n 个不同元素划分到 m 个集合的方案数。
*/

const int mod=1e9+7;//取模
LL s[N][N];//存放要求的Stirling数
void init(){
    memset(s,0,sizeof(s));
    s[1][1]=1;
    for(int i=2;i<=N-1;i++){
        for(int j=1;j<=i;j++){
            s[i][j]=s[i-1][j-1]+j*s[i-1][j];
            if(s[i][j]>=mod)
                s[i][j]%=mod;
        }
    }
}

/*
S(n,m) 的奇偶性 
*/

int calc(int n,int m){
    return (m&n)==n;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    if(n==0&&m==0)//特判
        printf("1\n");
    else if(n==0||m==0||n<m)//特判
        printf("0\n");
    else{
        int a=n-m;
        int b=(m+1)/2;
        int res=calc(b-1,a+b-1);
        printf("%d\n",res);
    }
    return 0;
}


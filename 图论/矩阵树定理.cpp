/*
取模（不用逆元版本）
1. 图中节点的下标从0开始计数！
2. 不存在自环，允许存在重边
3. 求行列式参数为n，求生成树计数参数为n-1
*/
struct Matrix {
    ll mat[N][N];
    void init() {
        memset(mat,0,sizeof(mat));
    }
    void addEdge(int u,int v) {
        mat[u][v]--;
        mat[u][u]++;
    }
    ll det(int n){
        ll res=1;
        for(int i=0;i<n;++i){
            if(!mat[i][i]){
                bool flag=false;
                for(int j=i+1;j<n;++j){
                    if(mat[j][i]){
                        flag=true;
                        for(int k=i;k<n;++k) swap(mat[i][k],mat[j][k]);
                        res=-res;
                        break;
                    }
                }
                if(!flag) return 0;
            }
            for(int j=i+1;j<n;++j){
                while(mat[j][i]){
                    ll t=mat[i][i]/mat[j][i];
                    for(int k=i;k<n;++k){
                        mat[i][k]=(mat[i][k]-t*mat[j][k])%mod;
                        swap(mat[i][k],mat[j][k]);
                    }
                    res=-res;
                }
            }
            res*=mat[i][i];
            res%=mod;//模意义下的语句，不是模意义则不加
        }
        if(res<0) res+=mod;
        return res;
    }
}ret;

/*
取逆元（mod为质数）
1. 图中节点的下标从0开始计数！
2. 不存在自环，允许存在重边
3. 求行列式参数为n，求生成树计数参数为n-1
*/
ll inv(ll a) {
    if(a == 1)return 1;
    return inv(mod%a)*(mod-mod/a)%mod;
}

struct Matrix {
    ll mat[N][N];
    void init() {
        memset(mat,0,sizeof(mat));
    }
    void addEdge(int u,int v) {
        mat[u][v]--;
        mat[u][u]++;
    }
    ll det(int n) { //求行列式的值模上MOD，需要使用逆元
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                mat[i][j] = (mat[i][j]%mod+mod)%mod;
        ll res = 1;
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++)
                if(mat[j][i]!=0) {
                    for(int k = i; k < n; k++)
                        swap(mat[i][k],mat[j][k]);
                    if(i != j)
                        res = (-res+mod)%mod;
                    break;
                }
            if(mat[i][i] == 0) {
                res = 0;//不存在(也就是行列式值为0)
                break;
            }
            for(int j = i+1; j < n; j++) {
                //int mut = (mat[j][i]*INV[mat[i][i]])%MOD;//打表逆元
                ll mut = (mat[j][i]*inv(mat[i][i]))%mod;
                for(int k = i; k < n; k++)
                    mat[j][k] = (mat[j][k]-(mat[i][k]*mut)%mod+mod)%mod;
            }
            res = (res * mat[i][i])%mod;
        }
        return res;
    }
}ret;

/*
不取模
1. 图中节点的下标从1开始计数！
2. 不存在自环，允许存在重边
3. 求行列式参数为n，求生成树计数参数为n-1
*/

struct Matrix {
    ll mat[N][N];
    void init() {
        memset(mat, 0, sizeof mat);
    }
    ll gauss(int n) {
        ll res = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                while (mat[j][i]) {
                    ll t = mat[i][i] / mat[j][i];
                    for (int k = i; k <= n; k++)
                        mat[i][k] = (mat[i][k] - t * mat[j][k]);
                    swap(mat[i], mat[j]);
                    res = -res;
                }
            }
            if(mat[i][i] == 0) return 0;
            res = res * mat[i][i];
        }
        if(res < 0) res = -res;
        return res;
    }
    void add(int u, int v) {
        mat[u][u]++;
        mat[v][v]++;
        mat[u][v]--;
        mat[v][u]--;
    }
}ret;
/*
线性基是一个数的集合，并且每个序列都拥有至少一个线性基，取线性基中若干个数异或起来可以得到原序列中的任何一个数。
 功能：
 1. 查询异或最值
 2. 查询k小值
 3. 查询某个数
 */

struct XOR {
    const int MN=62;
    ll a[63], tmp[63];
    bool flag; //可以表示0
    void ins(ll x){
        for(int i = MN; ~i; i--)
            if(x&(1ll<<i)) {
                if(!a[i]) { a[i]=x; return;}
                else x ^= a[i];
            }
        flag=true;
    }
    bool check(ll x){ // 查询某个数
        for(int i = MN; ~i; i--)
            if(x&(1ll<<i)) {
                if(!a[i]) return false;
                else x ^= a[i];
            }
        return true;
    }
    ll qmax(ll res = 0){ // 查询异或最大值
        for(int i = MN; ~i; i--)
            res = max(res, res^a[i]);
        return res;
    }
    ll qmin(){ // 查询异或最小值
        if(flag) return 0;
        for(int i = 0; i <= MN; i++) if(a[i]) return a[i];
        return -1; // not exists
    }
    ll query(ll k){ // 查询k小值
        ll res = 0; int cnt = 0;
        k -= flag;if(!k) return 0;
        for(int i = 0; i <= MN; i++){
            for(int j = i - 1; ~j; j--)
                if(a[i]&(1ll<<j)) a[i] ^= a[j];
            if(a[i]) tmp[cnt++] = a[i];
        }
        if(k >= (1ll<<cnt)) return -1;
        for(int i = 0; i < cnt; i++)
            if(k&(1ll<<i)) res ^= tmp[i];
        return res;
    }
}ret;


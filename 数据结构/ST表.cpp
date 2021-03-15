#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
int Max[N][30], Min[N][30];
class Solution {
public:
    inline int mx(int l,int r)
    {
        int k=(int)(log((double)(r-l+1))/log(2.0));
        return max(Max[l][k],Max[r-(1<<k)+1][k]);
    }
    inline int mn(int l,int r)
    {
        int k=(int)(log((double)(r-l+1))/log(2.0));
        return min(Min[l][k],Min[r-(1<<k)+1][k]);
    }
    
    int Intervalxor(vector<int> &num, vector<vector<int>> &ask) {
        // write your code here
        int n = num.size();
        for(int i = 1; i <= n; i++)
        {
            Max[i][0] = num[i-1];
            Min[i][0] = num[i-1];
        }
        for(int j=1;(1<<j)<=n;j++)
        {
            for(int i=1;i+(1<<j)-1<=n;i++)
            {
                Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
                Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
            }
        }
        int ans = 0;
        for (auto i : ask) {
            int l1 = i[0], r1 = i[1], l2 = i[2], r2 = i[3];
//            cout << mx(l1, r1) << " " << mn(l2, r2) << endl;
            ans ^= mx(l1, r1) + mn(l2, r2);
        }
        return ans;
    }
};

int main() {
    while(true) {
        int n; cin >> n;
        vector<int> num(n);
        for (auto& i : num) cin >> i;
        int m; cin >> m;
        vector<vector<int>> ask(m);
        for (auto& i : ask) {
            for (int j = 0; j < 4; j++) {
                int t; cin >> t;
                i.push_back(t);
            }
        }
        cout << Solution().Intervalxor(num, ask) << endl;
    }
}


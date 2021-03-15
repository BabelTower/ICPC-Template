/*
 模版：字符串循环同构（最小表示法）
 返回：字典序最小的起始位置
 */

const int N = 1e4 + 5;
int Minrp(char* s, int l) {
    int i = 0, j = 1, k = 0;
    while (i < l && j < l && k < l) {
        int d = s[(i+k)%l] - s[(j+k)%l];
        if(!d) k++;
        else {
            if(d > 0) i = i + k + 1;
            else j = j + k + 1;
            if(i == j) j++;
            k = 0;
        }
    }
    return i;
}
char str[N];
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        scanf("%s", str);
        printf("%d\n", Minrp(str, n));
    }
}
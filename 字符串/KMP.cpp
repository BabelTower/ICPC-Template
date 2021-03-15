/*
 模版：kmp字符串匹配
 */

const int N = 1e6 + 5;
int nxt[N];
char s1[N], s2[N];
void get_next(char* s, int* nxt) {
    int i = 0, j = -1, l = strlen(s);
    nxt[0] = -1;
    while(i < l) {
        if(j == -1 || s[i] == s[j])
            nxt[++i] = ++j;
        else j = nxt[j];
    }
}
void kmp(char* s, char* p, int* nxt) {
    int i = 0, j = 0, n = strlen(p), m = strlen(s);
    while (i < n) {
        if(j == -1 || p[i] == s[j]) i++, j++;
        else j = nxt[j];
        if(j == m) printf("%d\n", i-m+1), j = nxt[j];
    }
}
int main() {
    scanf("%s%s", s1, s2);
    get_next(s2, nxt);
    kmp(s2, s1, nxt);
    for (int i = 1; i <= strlen(s2); i++)
        printf("%d ", nxt[i]);
}
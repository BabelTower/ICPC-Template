/* 
* 普通快读
*/
inline int read() {
    int res = 0; bool bo = 0; char c;
    while (((c = getchar()) < '0' || c > '9') && c != '-');
    if (c == '-') bo = 1; else res = c - 48;
    while ((c = getchar()) >= '0' && c <= '9')
        res = (res << 3) + (res << 1) + (c - 48);
    return bo ? ~res + 1 : res;
}

/*
* 注意: 
*	1. 结束读入输ctrl+Z!
*	2. 一旦用了这个读入优化。getchar，scanf都不能用了（存到buf里了），所有读入都必须自己写了。所以说数据流不是太大的时候（如1*10^6），可以考虑不用这个读入优化。
* 原理: fread这个函数的原理就是先把数据流中的一整段都存下来，然后从这个数组里读取，直到数组读空了再重新从数据流中读取，由于是整段整段读取，所以自然比getchar()要快的多。 
*/
inline char nc() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 100000, stdin);
        if (p1 == p2)
            return EOF;
    }
    return *p1++;
}
inline void read(int &x) {
    char c = nc(), b = 1;
    for (; !(c >= '0' && c <= '9'); c = nc())
        if (c == '-')
            b = -1;
    for (x = 0; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = nc())
        ;
    x *= b;
}

/*
* 泛型模版，支持多参数读入(整形)，不支持读入实数
*/
template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}
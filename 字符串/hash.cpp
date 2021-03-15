/*
* 前缀hash: 求子串的hash值
* 注意: string的size()要强转int类型!
*/
const int MAXLEN = 2e6 + 5;
typedef unsigned long long ull;
ull base = 1331;
ull h[MAXLEN], p[MAXLEN];
ull get_hash(int l, int r) {
	return h[r] - h[l-1] * p[r-l+1];
}
ull hashs(string& s) {
	p[0] = 1; h[0] = 0;
	int sz = s.size();
	rep(i, 0, sz-1) {
		p[i+1] = p[i] * base;
		h[i+1] = h[i] * base + s[i];
	}
	return h[sz];
}
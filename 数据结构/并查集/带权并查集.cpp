/*
1. 路径压缩实现，维护集合内元素之间可量化的关系，如种类并查集（洛谷-食物链）
*/
struct DSU {
	int f[maxn], val[maxn];
	inline void Init(int n) {
		for (int i = 0; i <= n; i++) {
			f[i] = i;
			val[i] = 0;
		}
	}

	inline int Find(int x) {
		if(f[x] == x) return f[x];
		int fx = Find(f[x]); //这里不能够没有，因为在递归的过程中f[x]的值会被改变，会影响val[x]的更新
		val[x] += val[f[x]];
		return f[x] = fx;
	}

	inline bool Union(int a, int b, int v) {
		int fa = Find(a), fb = Find(b);
		if(fa != fb) {
			if(fa > fb) {
				f[fb] = fa;
				val[fb] = -val[b] - v + val[a];
			}
			else {
				f[fa] = fb;
				val[fa] = -val[a] + v + val[b];
			}
			return true;
		}
		else {
			if(val[fa] != -val[a] + v + val[b]) return false; // 不合法
			/*
				if(val[fa] != (-val[a] + v + val[b] + 2) % 2) return false; 
				种类并查集可由带权并查集扩展而来，常见的用途有判二分图（其实是判奇环）
			*/
			else return true;
		}
	}
}T;

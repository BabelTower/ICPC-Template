#include <bits/stdc++.h>
using namespace std;
template<typename T>
inline void deduplication(T& c) {
	sort(c.begin(), c.end());
	T::iterator new_end = unique(c.begin(), c.end());//"删除"相邻的重复元素
	c.erase(new_end, c.end());//删除(真正的删除)重复的元素
}
 
int main() {
	int ary[] = {1, 1, 2, 3, 2, 4, 3};
	vector<int> vec(ary, ary + sizeof(ary) / sizeof(int));
	//
	deduplication(vec);
	//
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}


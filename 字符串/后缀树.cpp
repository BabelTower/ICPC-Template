/*
1.时间复杂度
注意到，在从左到右扫描字符串的过程中，最长后缀回文串的左边界只可能向右移动，并且最多移动n次，与后缀链接边相对应的左边界也只可能向右移动，并且最多移动n词。因此总的时间复杂度是O(|S|)或者说O(N)的。
2.空间复杂度
空间复杂度为O(|alphbet|∗N)，还有其他几个数组，可以忽略掉。对于小写英文字母表|alphabet|=26。
3.应用
末尾追加一个字符，会产生多少个新的回文串？
举个例子，如果我们在字符串aba后面添加一个新的字符a，已经存在的回文串有a, b, aba，新产生的回文串为aa。
根据前面的讨论，这个问题的答案只可能是0或者1，当我们更新回文树的时候，插入这个新的字符，如果新产生了新节点，那么答案就是1，否则就是0。
4.回文子串的数目
给定一个字符串，计数这个字符串当中有多少个回文子串。比如，aba有四个：两个a,一个b，一个aba。
这个问题其实就是上面的代码所解决的问题，当我们扫描到一个新字符的时候，将结果累加上以这个字符结尾的后缀回文字符串个数，这个数字就是新节点通过后缀链接边可达的节点个数，为了高效计数，可以在每个节点新增一个域num，表示由该节点出发的链接长度。
对于根节点而言，链长为0，对于其他节点，链长为其后续节点的链长 + 1.
这个问题还可以用Manacher’s algorithm求解，时间复杂度也是O(N)。但回文树相对更好写并且应用的范围更广。
5.回文串出现的个数统计
这个问题要求统计出每个回文串各出现了多少次，解决的思路和上面类似，每扫描一个新的字符x时，就对新出现的最长后缀回文串以及它可达的所有回文串计数加1。
为了加快更新速度，需要类似于线段树那样采用一个延迟更新的策略，就不多说了。
最后再进行一遍计数值的传播更新，就可以得到所有回文串出现的次数了。
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

struct node {
    int next[26];
    int len;
    int sufflink;
    int num;
};

int len;
char s[MAXN];
node tree[MAXN];
int num;            // node 1 - root with len -1, node 2 - root with len 0
int suff;           // max suffix palindrome
long long ans;

bool addLetter(int pos) {
    int cur = suff, curlen = 0;
    int let = s[pos] - 'a';

    while (true) {
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
            break;
        cur = tree[cur].sufflink;
    }
    if (tree[cur].next[let]) {
        suff = tree[cur].next[let];
        return false;
    }

    num++;
    suff = num;
    tree[num].len = tree[cur].len + 2;
    tree[cur].next[let] = num;

    if (tree[num].len == 1) {
        tree[num].sufflink = 2;
        tree[num].num = 1;
        return true;
    }

    while (true) {
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
            tree[num].sufflink = tree[cur].next[let];
            break;
        }
    }
    tree[num].num = 1 + tree[tree[num].sufflink].num;
    return true;
}

void initTree() {
    num = 2; suff = 2;
    tree[1].len = -1; tree[1].sufflink = 1;
    tree[2].len = 0; tree[2].sufflink = 1;
}

int main() {
    scanf("%s", s);
    len = strlen(s);

    initTree();

    for (int i = 0; i < len; i++) {
        addLetter(i);
        ans += tree[suff].num;
    }
    cout << ans << endl;
    return 0;
}

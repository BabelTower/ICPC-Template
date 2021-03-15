struct pt { // 点
    ll x,y;
}p[10];
struct ln{ // 线段
    pt s,e;
};
 
ll mul(pt a,pt b,pt c) { // 向量叉积
    return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
 
int is(ln a,ln b) { // 判断线段是否相交
    if( min(a.s.x,a.e.x) <= max(b.s.x,b.e.x) &&
        max(a.s.x,a.e.x) >= min(b.s.x,b.e.x) &&
        min(a.s.y,a.e.y) <= max(b.s.y,b.e.y) &&
        max(a.s.y,a.e.y) >= min(b.s.y,b.e.y) &&
        mul(b.s,a.s,b.e)*mul(b.s,b.e,a.e) >= 0 &&
        mul(a.s,b.s,a.e)*mul(a.s,a.e,b.e) >= 0 )
    return 1;
    else return 0;
}
/*
凸函数求极大值 int
*/
while(l+1<r) 
{
    int lm=(l+r)>>1,rm=(lm+r)>>1;
    if(judge(lm)>judge(rm))
        r=rm;
    else
        l=lm;
}
//答案取 l 

/*
凸函数求极大值 double
*/
while(l+eps<r)
{
    double lm=(l+r)/2,rm=(lm+r)/2;
    if(judge(lm)>judge(rm))
        r=rm;
    else
        l=lm;
}
//答案取 l 或 (l+r)/2  (尽管此时 l 和 r 已经相等，但因为精度问题，取 r 可能会错)

/*
凹函数求极小值：int
*/
while(l+1<r)
{
    int lm=(l+r)>>1,rm=(lm+r)>>1;
    if(judge(lm)>judge(rm))
        l=lm;
    else
        r=rm;
}
//答案取 r

/*
凹函数求极小值 double
*/
while(l+eps<r)
{
    double lm=(l+r)/2,rm=(lm+r)/2;
    if(judge(lm)>judge(rm))
        l=lm;
    else
        r=rm;
}
//答案取 r 或 (l+r)/2  (尽管此时 l 和 r 已经相等，但因为精度问题，取 l 可能会错)
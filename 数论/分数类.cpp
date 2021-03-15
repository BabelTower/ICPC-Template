namespace Fraction{
	template<typename Int>Int gcd(Int a,Int b){return b?gcd(b,a%b):a;}
	template<typename Int>Int abs(Int a){return a<0?-a:a;}
	template<typename Int>struct Frac{
		Int a,b;
		Frac(){a=(Int)0;b=(Int)1;}
		Frac(Int x){a=x;b=(Int)1;}
		Frac(Int x,Int y){a=x;b=y;}
		Frac &operator =(Int x){a=x;b=1;return *this;}
		double to_double(){return (double)a/b;}
		Frac rec(){assert(a);return Frac(b,a);}
		Frac operator-(){return (Frac){-a,b};}
		Frac&operator++(){a+=b;return*this;}
		Frac&operator--(){a-=b;return*this;}
		Frac&operator+=(Frac x){
			Int g=gcd(b,x.b);
			a=b/g*x.a+x.b/g*a; b*=x.b/g;
			g=gcd(abs(a),b);a/=g;b/=g;
			return*this;
		}
		Frac&operator-=(Frac x){return*this+=-x;}
		Frac&operator*=(Frac x){
			Int g1=gcd(abs(a),x.b),g2=gcd(abs(x.a),b);
			(a/=g1)*=x.a/g2;(b/=g2)*=x.b/g1;
			return*this;
		}
		Frac&operator/=(Frac x){return*this*=x.rec();}
		Frac friend operator +(Frac x,Frac y){return x+=y;}
		Frac friend operator -(Frac x,Frac y){return x-=y;}
		Frac friend operator *(Frac x,Frac y){return x*=y;}
		Frac friend operator /(Frac x,Frac y){return x/=y;}
		int operator !(){return a;}
		int friend operator &&(Frac x,Frac y){return x.a&&y.a;}
		int friend operator ||(Frac x,Frac y){return x.a||y.a;}
#define logical_operator(op) int friend operator op(Frac x,Frac y){return (x-y).a op 0;}
		
		logical_operator(<)
		logical_operator(>)
		logical_operator(<=)
		logical_operator(>=)
		logical_operator(==)
		/*
		friend ostream&operator<<(ostream&ostr,Frac x){
			ostr<<x.a;
			assert(x.b);
			if(x.b!=1)ostr<<"/"<<x.b;
			return ostr;
		}
		*///输出一个分数，一般用不上，要用取消注释并使用std::cout即可
	};
#undef logical_operator
}

Frac<int>x;//定义一个初值为0的分数
Frac<int>x(a);//定义一个初值为a的分数
Frac<int>x(a,b);//定义一个初值为a/b的分数
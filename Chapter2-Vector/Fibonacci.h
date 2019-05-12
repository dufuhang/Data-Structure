class Fib 
{ 
private:
   int f, g;    //g存储斐波那契类的最大值，f存储次大值。即f(k)=g,f(k-1)=f
public:
   Fib ( int n ) : f(1), g(0) { while ( g < n ) next(); }   //创建一个最大值不小于n的最小斐波那契数列类
   int get()  { return g; } //返回当前g值
   int next() { g += f; f = g - f; return g; }
   int prev() { f = g - f; g -= f; return g; }
};
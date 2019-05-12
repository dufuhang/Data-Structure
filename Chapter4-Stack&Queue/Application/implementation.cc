//
// Created by 杜府航 on 2019/5/9.
//

#include "implementation.h"
//十进制转base进制,递归版
void convertRecursive(Stack<char>& S, long long n, int base)
{
    //0 < n, 1 < base <= 16,新进制下的数位符号，可视base取值范围适当扩充
    static char digit[]
    = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    if (n > 0)
    {
        convertRecursive(S, n / base, base);//通过递归得到所哟更高位
        S.push(digit[n % base]);//输出低位
    }
}//新进制下由高到低的各数位，自定而下保存与栈S中
//迭代版
void convertIteration(Stack<char>& S, long long n, int base)
{
    //0 < n, 1 < base <= 16,新进制下的数位符号，可视base取值范围适当扩充
    static char digit[]
    = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (n > 0)
    {
        int remainder = (int)(n % base);//为什么强制类型转换？
        S.push(digit[remainder]);
        n /= base;
    }
}

//括号匹配,可兼顾三种括号
bool paren(const char exp[], int lo, int hi)//可兼顾三种括号
{
    Stack<char> S;  //使用栈记录以发现但还尚未匹配的左括号
    for (int i = 0; exp[i]; i++)
    {
        //左括号直接进栈，右括号与栈顶比较，若失配，则表达式比不匹配
        switch (exp[i])
        {
            case '(':
            case '{':
            case '[':
                S.push(exp[i]);
                break;
            case ')':
                if ((S.empty()) || ('(' != S.pop())) { return false; }
                break;
            case '}':
                if ((S.empty()) || ('{' != S.pop())) { return false; }
                break;
            case ']':
                if ((S.empty()) || ('[' != S.pop())) { return false; }
                break;
            default:    //非括号字符一律hulue
                break;
        }
    }
    //扫描完整个表达式，栈中若残留左括号，则不匹配；否则栈为空，匹配
    return S.empty();
}
//
// Created by 杜府航 on 2019/5/9.
//

#ifndef CHAPTER4_STACK_QUEUE_IMPLEMENTATION_H
#define CHAPTER4_STACK_QUEUE_IMPLEMENTATION_H
#include "../Stack.h"
//进制转换
void convertRecursive(Stack<char>& S, long long n, int base);   //十进制转base进制,递归版
void convertIteration(Stack<char>& S, long long n, int base);   //迭代版

//括号匹配
bool paren(const char exp[], int lo, int hi);
#endif //CHAPTER4_STACK_QUEUE_IMPLEMENTATION_H

//逆波兰表达式(reverse Polish notation, RPN)


//试探回溯法

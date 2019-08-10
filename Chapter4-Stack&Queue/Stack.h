//
// Created by 杜府航 on 2019/5/8.
//

#ifndef CHAPTER4_STACK_QUEUE_STACK_H
#define CHAPTER4_STACK_QUEUE_STACK_H

#include <stddef.h>
#include "../Chapter2-Vector/Vector.hpp"  //以向量为基类，派生出栈模版类

template <typename T>
class Stack : public Vector<T>    //以向量为首/末端作为栈底/顶
{
public:
    void push(const T& e) { this->insert(this->size(), e); }    //入栈：等效于将新元素作为向量的末元素插入
    T pop() { return this->remove(this->size() - 1); }  //出栈：等效于删除向量的末元素
    T& top() { return (*this)[this->size() - 1]; }    //取顶：直接返回向量的末元素
};

#endif //CHAPTER4_STACK_QUEUE_STACK_H

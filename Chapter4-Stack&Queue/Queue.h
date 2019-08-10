//
// Created by 杜府航 on 2019/5/12.
//

#ifndef CHAPTER4_STACK_QUEUE_QUEUE_H
#define CHAPTER4_STACK_QUEUE_QUEUE_H

//以List为基类
#include "../Chapter3-List/List.h"
template <typename T>
class Queue : public List<T>
{
public:
    void enqueue(const T& e) { this->insertAslast(e); } //入队：尾部插入
    T dequeue() { return this->remove(this->first()); }   //出队：首部删除
    T& front() { return this->first()->data; }  //队首
};


#endif //CHAPTER4_STACK_QUEUE_QUEUE_H

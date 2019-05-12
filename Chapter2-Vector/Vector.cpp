//
//  Vector.cpp
//  Chapter-2
//
//  Created by 杜府航 on 2019/4/2.
//  Copyright © 2019 杜府航. All rights reserved.
//

#include "Vector.hpp"
#include "Fibonacci.h"
#include <cstdlib>
#include <iostream>
//以数组区间A[lo,hi)为蓝本复制向量
template <typename T>
void Vector<T>::copyForm(const T* A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)];//分配空间,s双倍的容量
    _size = 0;  //规模清零
    while (lo < hi)
    {
        _elem[_size++] = A[lo++];   //复制至_elem[0,hi-lo)
    }
}
//重载赋值运算符
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& A) 
{
    if (_elem)  //释放原有内容
    {
        delete [] _elem;
    }
    copyForm(A._elem, 0, A._size);  //  整体复制
    return *this;   //返回当前对象的引用，以便链式赋值
}
//空间不足时，扩容
template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity)  //未满，不必扩容
    {
        return ;
    }
    if (_capacity < DEFAULT_CAPACITY)   //不低于最小容量（？）
    {
        _capacity = DEFAULT_CAPACITY;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity << 1]; //容量加倍(位运算)
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;  //释放原始空间
}
//缩容（不用太过考虑）
template <typename T>
void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1)  //不致收缩到DEFAULT_CAPACITY以下
    {
        return ;
    }
    if (_size << 2 > _capacity) //以25%为界
    {
        return ;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity >> 1];  //容量减半
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;  //释放原空间
}
//重载下标运算符
template <typename T>
T& Vector<T>::operator[](Rank r) const  
{
    return _elem[r];
}
//等概率随机置乱向量区间[lo,hi)
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)    
{
    T* V = _elem + lo;  //将向量_elem[lo,hi)视作向量V[0,hi-lo)
    for (Rank i = hi - lo; i > 0; i--)  //自后向前
    {
        std::swap(V[i-1], V[rand() % i]);    //将V[i-1]与V[0,i)中某一元素随即交换
    }
}
//无序向量的顺序查找:返回最后一个元素e的位置；失败时，d返回lo-1
template <typename T>   
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const
{
    while ((lo < hi--) && (e != _elem[hi]));    //从后向前，顺序查找（返回相同元素秩最大的那个，所以从后往前）
    return hi;  //若hi<lo，说明查找失败；否则hi即为所求秩
}
//插入
template <typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
    expand();   //判断是否需要扩容
    for (int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i-1];  //z
    }
    _elem[r] = e;   //插入
    _size++;    //更新容量
    return r;   //返回秩
}
//区间删除
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi)   //为效率考虑，单独处理退化情况
    {
        return 0;
    }
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++];  //顺次前移hi-lo个单元
    }
    _size = lo; //更新规模
    shrink();   //缩容
    return hi - lo; //返回被删除的元素数目
}
//单元素删除，基于区间删除
template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = r;    //备份待删元素以用于返回
    remove(r, r+1); //调用区间删除算法，等效于删除区间[r,r+1)
    return e;   //返回被删元素
}
//无序向量去重
template <typename T>
int Vector<T>::deduplicate()
{
    int oldSize = _size;    //记录原始规模
    Rank i = 1; //从_elem[1]开始
    while (i < _size)
    {
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    }
    return oldSize - _size; //返回被删除元素总数。_size在remove()函数中会被更新
}
//遍历()
template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) //借助函数指针
{
    for (int i = 0; i < _size; i++) //遍历向量
    {
        visit(_elem[i]);
    }
}
//??????????
template <typename T>
template <typename VST> void Vector<T>::traverse(VST& visit)    //使用函数对象
{
    for (int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
}
//判断向量是否有序
template <typename T>
int Vector<T>::disordered() const   //返回向量中逆序相邻元素对的总数
{
    int n = 0;  //计数器
    for (int i = 1; i < _size; i++)
    {
        if (_elem[i-1] > _elem[i])
        {
            n++;    //逆序则计数
        }
    }
    return n;   //当且仅当n = 0时，向量有序
}
//有序向量去重（低效）
// template <typename T>
// int Vector<T>::uniquify()
// {
//     int oldSize = _size;
//     int i = 1;
//     while (i < _size)   //从前向后，每次remove()操作都会更新规模 _size
//     {
//         _elem[i-1] == _elem[i] ? remove(i) : i++;   //相同则删除后者
//     }
//     return oldSize - _size; //向量规模变化量，即被删除的元素总数
// }
//(高效)
template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;  //互异“相邻”元素的秩
    while (++j < _size) //逐一扫描，直至末元素
    {
        if (_elem[i] != _elem[j])   //元素相同则跳过
        {
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    shrink();   //使用shrink()复制进新分配过大小的数组，缩容，同时截取了多余元素
    return j - i;   //向量规模变化量，即被删除元素的总数
}
//有序向量区间查找
template <typename T>
Rank Vector<T>::search(const T& e, Rank lo, Rank hi) const
{
    // return (rand() % 2) ? binSearch_C(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
    return binSearch_C(_elem, e, lo, hi);
}
//二分查找版本A
template <typename T>
Rank Vector<T>::binSearch_A(T* A, const T& e, Rank lo, Rank hi)
{
    while (lo < hi)
    {
        Rank mi = (lo+hi) >> 1; //以中点作为中心点。使用整数位移操作可避免更加费事的除法运算
        if (e < A[mi])
        {
            hi = mi;
        }
        else if (e > A[mi])
        {
            lo = mi + 1;
        }
        else
        {
            return mi;  //在mi处命中所求值
        }
        return -1;  //查找失败
    }
}
//二分查找版本B
template <typename T>
Rank Vector<T>::binSearch_B(T* A, const T& e, Rank lo, Rank hi)
{
    while (hi - lo > 1)
    {
        Rank mi = (hi + lo) / 2;    //以中点为轴点
        (e < A[mi]) ? hi = mi : lo = mi;
    }   //跳出循环时，hi=lo+1,查找区间仅含有一个元素A[lo]
    return (e == A[lo]) ? lo : -1;  //查找成功返回秩，不成功统一返回-1
}
//二分查找版本C
template <typename T>
Rank Vector<T>::binSearch_C(T* A, const T& e, Rank lo, Rank hi)
{
    while (lo < hi)
    {
        Rank mi = (hi + lo) / 2;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;    //循环结束时，lo为大于e的元素的最小秩，故lo-1为不大于e的元素的最大秩
}   //有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置。
//斐波那契查找（存疑）
// template <typename T>
// Rank Vector<T>::fibSearch(T* A, const T& e, Rank lo, Rank hi)
// {
//     Fib fib(hi - lo);   //引入Fibonacci类，并创建一个fib数列
//     while (lo < hi)
//     {
//         while (hi - lo < fib.get())
//         {
//             fib.prev();
//         }
//         Rank mi = lo + fib.get() - 1;   //确定轴点
//         if (e < A[mi])
//         {
//             hi = mi;    //深入前半段
//         }
//         else if (A[mi] < e)
//         {
//             lo = mi + 1;    //深入后半段
//         }
//         else
//         {
//             return mi;      //命中返回
//         }
//     }
//     return -1;  //查找失败
// }
//向量排序器接口
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
    switch (rand() % 3) // 随机选择排序算法
    {
        case 1 : bubbleSort(lo, hi);
                 break;
        case 2 : mergeSort(lo, hi);
                 break;
        // case 3 : selectionSort(lo, hi);
        //          break;
        // case 4 : heapSort(lo, hi);
        //          break;
        // default : quickSort(lo, hi);
        //           break;
    }
}
//冒泡排序
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!(bubble(lo, hi--)));    //  逐趟做扫描交换，直至全序
}
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
    bool sorted = true; //整体有序标志
    while (++lo < hi)
    {
        if (_elem[lo-1] > _elem[lo])
        {
            sorted = false;
            std::swap(_elem[lo-1], _elem[lo]);
        }
    }
    return sorted;
}
//归并排序
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    if (hi - lo < 2)
    {
        return ;
    }
    int mi = (hi + lo) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);  //归并
}
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
    T* A = _elem + lo;  //合并后的向量A[0,hi-lo) = _elem[lo,hi)
    int lb = mi - lo;
    T* B = new T[lb];   //前子向量B[0.lb) = _elem[lo,mi)
    for (Rank i = 0; i < lb;B[i] = A[i++]); //复制前子向量
    int lc = hi - mi;
    T* C = _elem + mi;  //后子向量C[0,lc) = _elem[mi,hi)
    for (Rank i = 0, j = 0, k = 0;(j < lb) || (k < lc); )
    {
        if ( (j<lb) && (!(k<lc) || (B[j] <= C[k])))
        {
            A[i++] = B[j++];
        }
        if ( (k<lc) && (!(j<lb) || (C[k] < B[j])))
        {
            A[i++] = C[k++];
        }
    }
    delete [] B;    //释放临时空间B
}   //归并后得到完整的有序向量[lo,hi)
//输出向量
template <typename T>
void Vector<T>::show()
{
    for (int i = 0; i < _size; i++)
    {
        std::cout << _elem[i] << " ";
    }
    std::cout << std::endl;
}
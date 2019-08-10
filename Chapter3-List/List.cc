//
// Created by 杜府航 on 2019/5/12.
//

#include <iostream>
#include "List.h"
using namespace std;


//列表初始化，在创建列表对象时统一调用
template <typename T>
void List<T>::init() {
    header = new ListNode<T>; //创建头哨兵节点
    trailer = new ListNode<T>; //创建尾哨兵节点
    header->succ = trailer; header->pred = nullptr;
    trailer->pred = header; trailer->succ = nullptr;
    _size = 0; //记录规模
}

//清空列表
template <typename T>
int List<T>::clear() {
    int oldSize = _size;
    while ( 0 < _size ) remove ( header->succ ); //反复删除首节点，直至列表变空
    return oldSize;
}

//列表内部方法：复制列表中自位置p起的n项
template <typename T>
void List<T>::copyNodes ( ListNodePosi(T) p, int n ) { //p合法，且至少有n-1个真后继节点
    init(); //创建头、尾哨兵节点并做初始化
    while ( n-- ) { insertAsLast ( p->data ); p = p->succ; } //将起自p的n项依次作为末节点插入
}

//有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
template <typename T>
void List<T>::merge ( ListNodePosi(T) & p, int n, List<T>& L, ListNodePosi(T) q, int m ) {
// assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
//          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
// 注意：在归并排序之类的场合，有可能 this == L && rank(p) + n = rank(q)
    ListNodePosi(T) pp = p->pred; //借助前驱（可能是header），以便返回前 ...
    while ( 0 < m ) //在q尚未移出区间之前
        if ( ( 0 < n ) && ( p->data <= q->data ) ) //若p仍在区间内且v(p) <= v(q)，则
        { if ( q == ( p = p->succ ) ) break; n--; } //p归入合并的列表，并替换为其直接后继
        else //若p已超出右界或v(q) < v(p)，则
        { insertB ( p, L.remove ( ( q = q->succ )->pred ) ); m--; } //将q转移至p之前
    p = pp->succ; //确定归并后区间的（新）起点
}

//列表的归并排序算法：对起始于位置p的n个元素排序
template <typename T>
void List<T>::mergeSort ( ListNodePosi(T) & p, int n ) { //valid(p) && rank(p) + n <= size
    cout << "MergeSort" << " " << n << endl;
    if ( n < 2 ) return; //若待排序范围已足够小，则直接返回；否则...
    int m = n >> 1; //以中点为界
    ListNodePosi(T) q = p; for ( int i = 0; i < m; i++ ) q = q->succ; //均分列表
    mergeSort ( p, m ); mergeSort ( q, n - m ); //对前、后子列表分别排序
    merge ( p, m, *this, q, n - m ); //归并
} //注意：排序后，p依然指向归并后区间的（新）起点

//列表的插入排序算法：对起始于位置p的n个元素排序
template <typename T>
void List<T>::insertionSort ( ListNodePosi(T) p, int n ) { //valid(p) && rank(p) + n <= size
    cout << "InsertionSort..." << endl;
    for ( int r = 0; r < n; r++ ) { //逐一为各节点
        insertA ( search ( p->data, r, p ), p->data ); //查找适当的位置并插入
        p = p->succ; remove ( p->pred ); //转向下一节点
    }
}

//列表的选择排序算法：对起始于位置p的n个元素排序
template <typename T>
void List<T>::selectionSort ( ListNodePosi(T) p, int n ) { //valid(p) && rank(p) + n <= size
    cout << "SelectionSort..." << endl;
    ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
    for ( int i = 0; i < n; i++ ) tail = tail->succ; //待排序区间为(head, tail)
    while ( 1 < n ) { //在至少还剩两个节点之前，在待排序区间内
        ListNodePosi(T) max = selectMax ( head->succ, n ); //找出最大者（歧义时后者优先）
        insertB ( tail, remove ( max ) ); //将其移至无序区间末尾（作为有序区间新的首元素）
        /*DSA*///swap(tail->pred->data, selectMax( head->succ, n )->data );
        tail = tail->pred; n--;
    }
}

//构造函数

//复制列表中自位置p起的n项（assert: p为合法位置，且至少有n-1个后继节点）
template <typename T>
List<T>::List ( ListNodePosi(T) p, int n ) { copyNodes ( p, n ); }
//整体复制列表L
template <typename T>
List<T>::List ( List<T> const& L ) { copyNodes ( L.first(), L._size ); }
//复制L中自第r项起的n项（assert: r+n <= L._size）
template <typename T>
List<T>::List ( List<T> const& L, int r, int n ) { copyNodes ( L[r], n ); }

//重载下标操作符，以通过秩直接访问列表节点（虽方便，效率低，需慎用）
template <typename T>
T& List<T>::operator[] ( Rank r ) const { //assert: 0 <= r < size
    ListNodePosi(T) p = first(); //从首节点出发
    while ( 0 < r-- ) p = p->succ; //顺数第r个节点即是
    return p->data; //目标节点，返回其中所存元素
}

//统计逆序相邻元素对的总数
template <typename T> int List<T>::disordered() const {
    int n = 0; ListNode<T>* p = first();
    for ( int i = 0; i < _size - 1; p = p->succ, i++ )
        if ( p->data > p->succ->data ) n++;
    return n;
}

//在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
template <typename T>
ListNodePosi(T) List<T>::find ( T const& e, int n, ListNodePosi(T) p ) const {
    while ( 0 < n-- ) //（0 <= n <= rank(p) < _size）对于p的最近的n个前驱，从右向左
        if ( e == ( p = p->pred )->data ) return p; //逐个比对，直至命中或范围越界
    return NULL; //p越出左边界意味着区间内不含e，查找失败
} //失败时，返回NULL

//在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
template <typename T>
ListNodePosi(T) List<T>::search ( T const& e, int n, ListNodePosi(T) p ) const {
// assert: 0 <= n <= rank(p) < _size
    cout << "searching for " << e << " :" << endl;
    while ( 0 <= n-- ) //对于p的最近的n个前驱，从右向左逐个比较
        /*DSA*/{ printf ( "  <%4d>", p->pred->data );
        if ( ( ( p = p->pred )->data ) <= e ) break; //直至命中、数值越界或范围越界
        /*DSA*/} printf ( "\n" );
// assert: 至此位置p必符合输出语义约定——尽管此前最后一次关键码比较可能没有意义（等效于与-inf比较）
    return p; //返回查找终止的位置
} //失败时，返回区间左边界的前驱（可能是header）——调用者可通过valid()判断成功与否


//e当作首节点插入
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst ( T const& e )
{  _size++; return header->insertAsSucc ( e );  }
//e当作末节点插入
template <typename T>
ListNodePosi(T) List<T>::insertAsLast ( T const& e )
{  _size++; return trailer->insertAsPred ( e );  }
//e当作p的后继插入（After）
template <typename T>
ListNodePosi(T) List<T>::insertA ( ListNodePosi(T) p, T const& e )
{  _size++; return p->insertAsSucc ( e );  }
//e当作p的前驱插入（Before）
template <typename T>
ListNodePosi(T) List<T>::insertB ( ListNodePosi(T) p, T const& e )
{  _size++; return p->insertAsPred ( e );  }

//剔除无序列表中的重复节点
template <typename T> int List<T>::deduplicate() {
    if ( _size < 2 ) return 0; //平凡列表自然无重复
    int oldSize = _size; //记录原规模
    ListNodePosi(T) p = header; Rank r = 0; //p从首节点开始
    while ( trailer != ( p = p->succ ) ) { //依次直到末节点
        ListNodePosi(T) q = find ( p->data, r, p ); //在p的r个（真）前驱中查找雷同者
        q ? remove ( q ) : r++; //若的确存在，则删除之；否则秩加一
    } //assert: 循环过程中的任意时刻，p的所有前驱互不相同
    return oldSize - _size; //列表规模变化量，即被删除元素总数
}

//成批剔除重复元素，效率更高
template <typename T> int List<T>::uniquify() {
    if ( _size < 2 ) return 0; //平凡列表自然无重复
    int oldSize = _size; //记录原规模
    ListNodePosi(T) p = first(); ListNodePosi(T) q; //p为各区段起点，q为其后继
    while ( trailer != ( q = p->succ ) ) //反复考查紧邻的节点对(p, q)
        if ( p->data != q->data ) p = q; //若互异，则转向下一区段
        else remove ( q ); //否则（雷同），删除后者
    return oldSize - _size; //列表规模变化量，即被删除元素总数
}

//借助函数指针机制遍历
template <typename T>
void List<T>::traverse ( void ( *visit ) ( T& ) )
{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
//元素类型、操作器
template <typename T>
template <typename VST>
void List<T>::traverse ( VST& visit ) //借助函数对象机制遍历
{  for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) visit ( p->data );  }
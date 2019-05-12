//
// Created by 杜府航 on 2019/4/11.
//

#ifndef CHAPTER3_LIST_LISTNODE_H
#define CHAPTER3_LIST_LISTNODE_H

typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>*  //列表节点位置(列表类型的指针)

template <typename T>
struct ListNode     //列表节点模版类(以双向列表形式实现)
{

  //成员
  T data; //数据域
  ListNodePosi(T) pred; //前驱
  ListNodePosi(T) succ; //后继

  //构造函数
  ListNode() = default; //针对header和trailer的构造
  ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s) {}  //默认构造器

  //接口
  ListNodePosi(T) insertAsPred(const T& e); //紧靠当前节点之前插入新节点
  ListNodePosi(T) insertAsSucc(const T& e); //紧靠当前节点之后插入新节点
};

#endif //CHAPTER3_LIST_LISTNODE_H

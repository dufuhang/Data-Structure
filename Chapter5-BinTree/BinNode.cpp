//
// Created by 杜府航 on 2019-08-05.
//

#include "BinNode.h"
//将e作为当前节点的左孩子插入二叉树
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
    return lChild = new BinNode(e, this);
}

//将e作为当前节点的右孩子插入二叉树
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
    return rChild = new BinNode(e, this);
}
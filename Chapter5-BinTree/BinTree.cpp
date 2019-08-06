//
// Created by 杜府航 on 2019-08-05.
//

#include "BinTree.h"
template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)  //更新节点x高度
{
    //具体规则因树不同而异
    return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)    //更新v及祖先的高度
{
    //可优化。一旦高度未变，即可终止
    while (x)
    {
        updateHeight(x);
        x = x->parent;
    }
}

//将e当作根节点插入空的二叉树,该节点成为树根
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
    _size = 1;
    return _root = new BinNode<T>(e);
}

//将e插入为x的左孩子
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lChild;
}

//将e插入为x的右孩子
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rChild;
}

//子树接入
//二叉树子树接入算法：将S当作节点x的左子树接入，S本身置空
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S)
{

}
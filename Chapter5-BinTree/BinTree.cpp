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
    if (x->lChild = S->_root)
    {
        x->lChild->parent = x;  //接入
        _size += S->_size;      //更新全树规模
        updateHeightAbove(x);   //更新祖先节点的高度
        S->_root = nullptr;     //释放原树
        S->_size = 0;
        release(S);
        S = nullptr;
        return x;               //返回接入位置
    }
}

//二叉树子树接入算法：将S当作节点x的右子树接入，S本身置空
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S)
{
    if (x->rChild = S->_root)
    {
        x->rChild->parent = x;  //接入
        _size += S->_size;      //更新全树规模
        updateHeightAbove(x);   //更新祖先节点的高度
        S->_root = nullptr;     //释放原树
        S->_size = 0;
        release(S);
        S = nullptr;
        return x;               //返回接入位置
    }
}

//子树的删除
//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)    //x为二叉树中的合法位置
{
    FromParentTo(*x) = nullptr; //切断来自父节点的指针
    updateHeightAbove(x->parent);  //更新祖先高度
    int n = removeAt(x);    //删除子树x
    _size -= n; //更新规模
    return n;   //返回删除节点的总数
}

template <typename T>
static int removeAt(BinNodePosi(T) x)   //x为二叉树中的合法位置
{
    if (!x) return 0;   //递归基：空树
    int n = 1 + removeAt(x->lChild) + removeAt(x->rChild);  //递归释放左、右子树
    //释放被摘的节点
    release(x->data);
    release(x);
    return n;   //返回删除节点总数
}

//子树分离
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)    //x为二叉树中的合法位置
{
    FromParentTo(*x) = nullptr; //切断来自父节点的指针
    updateHeightAbove(x->parent);   //更新原树中所有祖先的高度
    //新树以x为根
    BinTree<T>* S = new BinTree<T>;
    S->_root = x;
    x->parent = nullptr;
    //更新规模，返回分离出来的子树
    S->_size = x->size();
    _size -= S-_size;
    return S;
}
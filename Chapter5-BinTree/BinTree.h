//
// Created by 杜府航 on 2019-08-05.
//

#ifndef CHAPTER5_BINTREE_BINTREE_H
#define CHAPTER5_BINTREE_BINTREE_H

#include "BinNode.h"    //引入二叉树节点类
//二叉树模版类
template <typename T>
class BinTree
{
protected:
    int _size;  //规模
    BinNodePosi(T) _root;   //根节点
    //虚方法。不同种类的树，高度的定义不一样，定义为虚方法，便于派生类在必要时重写(override)
    virtual int updateHeight(BinNodePosi(T) x);    //更新节点x
    void updateHeightAbove(BinNodePosi(T) x);    //更新节点x及其祖先的高度

public:
    BinTree() : _size(0), _root(nullptr) { }    //构造函数
    ~BinTree() { if (0 < _size) remove(_root); }    //析构函数
    int size() const { return _size; }  //返回树的规模
    bool empty() const { return !_root; }   //判空
    BinNodePosi(T) root() const { return _root; }   //树根
    BinNodePosi(T) insertAsRoot(T const& e);    //插入根节点
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);    //e作为x的左孩子(原无)插入
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);    //作为右孩子插入
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &);  //T作为左子树接入
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &);    //T作为右子树接入
    int remove(BinNodePosi(T) x);   //删除以位置x处节点为根的子树，返回该子树原先的规模
    BinTree<T>* secede(BinNodePosi(T) x);   //将子树x从当前树中摘除，并将其转换为一颗独立子树
    template <typename VST> //操作器
    void traLevel(VST& visit) { if (_root) _root->travLevel(visit); }   //层次遍历
    template <typename VST>
    void travPre(VST& visit) { if (_root) _root->travPre(visit); }  //先序遍历
    template <typename VST>
    void travIn(VST& visit) { if (_root) _root->travIn(visit); }    //中序遍历
    template <typename VST>
    void travPost(VST& visit) { if (_root) _root->travPost(visit); }    //后序遍历
    //比较器、判等器（各列其一）
    bool operator<(BinTree<T> const& t) { return _root && t._root && lt(_root, t._root); }
    bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root); }

};  //BinTree
#endif //CHAPTER5_BINTREE_BINTREE_H

//
// Created by 杜府航 on 2019-08-05.
//

#ifndef CHAPTER5_BINTREE_BINNODE_H
#define CHAPTER5_BINTREE_BINNODE_H

//一些简化代码的宏
#define BinNodePosi(T) BinNode<T>* //指针，节点位置
#define stature(p) ((p) ? (p)-> height : -1)    //节点高度(与"空树高度为-1"的约定相统一)

/*
 * 在BinNode模板类各接口以及后续相关算法的实现中，将频繁检查和判断二叉树节点的状态
 * 与性质，有时还需要定位与之相关的(兄弟、叔叔等)特定节点，为简化算法描述同时增强可读性
 * 在书118页，如有需要可进行参考和补充
*/

typedef enum { RB_RED, RB_BLACK} RBColor;   //节点颜色

//二叉树节点模版类
template <typename T>
struct BinNode
{
    //成员(为简化描述起见，统一开放权限)
    T data; //数值
    BinNodePosi(T) parent;  //父节点
    BinNodePosi(T) lChild;  //左孩子
    BinNodePosi(T) rChild;  //右孩子
    int height; //高度(通用)
    int npl;    //Null Path Length(左式堆，也可直接用height代替)
    RBColor color;  //颜色(红黑树)

    //构造函数
    BinNode() : parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED) { }

    BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int h = 0,
            int l = 1, RBColor c = RB_RED)
            : data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(1), color(c)
    { }

    //操作接口
    int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
    BinNodePosi(T) insertAsLC(T const&);    //作为当前节点的左孩子插入新节点
    BinNodePosi(T) insertAsRC(T const&);    //作为右孩子插入
    BinNodePosi(T) succ();  //取当前节点的直接后继
    template <typename VST> void travLevel(VST&);   //子树层次遍历
    template <typename VST> void travPre(VST&);     //子树先序遍历
    template <typename VST> void travIn(VST&);      //子树中序遍历
    template <typename VST> void travPost(VST&);    //子树后序遍历

    //比较器、判等器(各列其一)
    bool operator<(BinNode const& bn) { return data < bn.data; } //小于
    bool operator==(BinNode const& bn) { return data == bn.data; }  //等于
};



#endif //CHAPTER5_BINTREE_BINNODE_H

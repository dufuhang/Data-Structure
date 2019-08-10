////
//// Created by 杜府航 on 2019/5/12.
////
//
//#ifndef CHAPTER4_STACK_QUEUE_QUEEN_H
//#define CHAPTER4_STACK_QUEUE_QUEEN_H
//
//
//struct Queen
//{
//    int x, y;   //皇后在棋盘上的位置坐标
//    Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};    //构造函数
//    //重载判等操作符，以检测不同皇后之间可能的冲突
//    bool operator==(const Queen& q) const
//    {
//        return (x == q.x)   //行冲突(这一情况其实可能并不会发生，故可省略)
//            || (y == q.y)   //列冲突
//            || (x + y == q.x + q.y) //沿正对角线冲突
//            || (x - y == q.x - q.y); //沿反对角线冲突
//    }
//    //重载不等操作符。将同行、同列、同对角线的任意两个皇后视作"相等"的，于是两个皇后相互冲突当且仅当二者被判为"相等"
//    bool operator!=(const Queen& q) const { return !(*this == q); }
//    //N皇后算法
//    //迭代版：采用试探/回溯的策略，借助栈记录查找的结果
//    void placeQueens(int N);
//};
//
//
//#endif //CHAPTER4_STACK_QUEUE_QUEEN_H

////
//// Created by 杜府航 on 2019/5/12.
////
//
//#include "Queen.h"
//#include "../Stack.h"
//int nCheck = 0; //尝试的总次数
//int nSolu = 0;  //解的总数
//void placeQueens(int N)
//{
//    Stack<Queen> solu;  //存放部分解的栈
//    Queen q(0, 0);   //从原点位置出发
//    //反复试探，回溯
//    do
//    {
//        if (N <= solu.size() || N <= q.y)   //若已出界，则回溯一行，并继续试探下一列
//        {
//            q = solu.pop();
//            q.y++;
//        }
//        else    //否则，试探下一行
//        {
//            while ((q.y < N) && (0 <= solu.find(q)))    //通过与已有皇后的对比
//            {
//                //尝试找到的可摆放下一皇后的列
//                q.y++;
//                nCheck++;
//            }
//            if (N > q.y)    //若存在可摆放的列，则
//            {
//                //摆上皇后
//                solu.push(q);
//                //若部分解已成为全局解，则通过全局变量nSolu计数
//                if (N <= solu.size())
//                {
//                    nSolu++;
//                }
//                //转入下一行，从第0列开始，试探下一皇后
//                q.x++;
//                q.y = 0;
//            }
//        }
//    }while ((0 < q.x) || (q.y < N));    //所有分支均已或穷举或剪枝之后，算法结束
//}
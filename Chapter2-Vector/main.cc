//
//  main.cpp
//  Chapter-2
//
//  Created by 杜府航 on 2019/4/2.
//  Copyright © 2019 杜府航. All rights reserved.
//

#include <iostream>
#include "Vector.cpp"
using namespace std;

int main()
{
    Vector<int> A;    //初始化测试向量
//测试插入
    A.insert(0,9);
    A.insert(0,4);
    A.insert(1,5);
    A.show();
//将秩为1的元素替换为2，并返回原来元素的值
    cout << A.put(1,2) << endl;
    A.show();
//返回秩为2的元素值
    cout << A.get(2) << endl;
//继续插入
    A.insert(3,6);
    A.insert(1,7);
    A.show();
//删除并返回
    cout << A.remove(2) << endl;
    A.show();
//插入
    A.insert(1,3);
    A.insert(3,4);
    A.show();
//返回当前元素个数
    cout << A.size() << endl;
//判断是否逆序（从小到大），并返回逆序对数
    cout << A.disordered() << endl;
//查找指定元素的秩，并返回
    cout << A.find(9) << endl;
    cout << A.find(5) << endl;
//排序
    cout << "before sorting: " << endl;
    A.show();
    A.sort();
    cout << "after sorting: " << endl;
    A.show();
//有序向量，查找制定元素，并返回不大于指定元素且秩最大的元素
    cout << A.search(1) << endl;
    cout << A.search(4) << endl;
    cout << A.search(8) << endl;
    cout << A.search(9) << endl;
    cout << A.search(10) << endl;
//有序向量的去重
    cout << "before: " << endl;
    A.show();
    A.uniquify();
    cout << "after: " << endl;
    A.show();    
    return 0;
}


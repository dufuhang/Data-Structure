//
//  Vector.hpp
//  Chapter-2
//
//  Created by 杜府航 on 2019/4/2.
//  Copyright © 2019 杜府航. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp
typedef int Rank; //秩
#define DEFAULT_CAPACITY 3  //默认的初始容量(实际中可设置更大)

template <typename T>
class Vector
{
protected:
    Rank _size; //有效数据的规模
    int _capacity;  //容量
    T* _elem;   //指向数据区的指针
    void copyForm(const T* A, Rank lo, Rank hi);    //  复制数组区间A[lo,hi),注意左闭右开
    void expand();  //空间不足时进行扩容
    void shrink();  //压缩
    bool bubble(Rank lo, Rank hi);  //扫描交换
    void bubbleSort(Rank lo, Rank hi);  //冒泡排序
    Rank max(Rank lo, Rank hi); //选取最大元素
    void selectionSort(Rank lo, Rank hi);   //选择排序
    void merge(Rank lo, Rank mi, Rank hi);   //归并算法
    void mergeSort(Rank lo, Rank hi);   //归并排序
    void partition(Rank lo, Rank hi);   //轴点构造算法
    void quickSort(Rank lo, Rank hi);   //快速排序
    void heapSort(Rank lo, Rank hi);    //堆排序
public:
//构造函数
    //容量，规模，初始值v    s <= c(规模小于容量)
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];   //分配空间，返回地址
        for (_size = 0; _size < s; _elem[_size++] = v);     //遍历，将数组的值初始化为v，
    }
    Vector(const T* A, Rank lo, Rank hi) { copyForm(A, lo, hi); }    //数组区间整体复制
    Vector(const T* A, Rank n) { copyForm(A, 0, n); }    //数组整体复制
    Vector(const Vector<T>& V, Rank lo, Rank hi) { copyForm(V._elem, lo, hi); }      //向量区间复制
    Vector(const Vector<T>& V, Rank n) { copyForm(V._elem, 0, n); }      //向量整体复制
//析构函数
    ~Vector() { delete [] _elem; }  //释放空间
//只读访问接口
    Rank size() const { return _size; };    //返回规模
    bool empty() const { return !_size; }   //判空
    int disordered() const; //判断向量是否已排序
    Rank find(const T& e, Rank lo, Rank hi) const;    //无序向量区间查找
    Rank find(const T& e) const { return find(e, 0, _size); }; //无序向量整体查找
    Rank search(const T& e, Rank lo, Rank hi) const;    //有序向量区间查找
    Rank search(const T& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); } //有序向量整体查找
    static Rank binSearch_A(T* A, const T& e, Rank lo, Rank hi);  //二分查找，版本A
    static Rank binSearch_B(T* A, const T& e, Rank lo, Rank hi);  //二分查找，版本B
    static Rank binSearch_C(T* A, const T& e, Rank lo, Rank hi);  //二分查找，版本C
    static Rank fibSearch(T* A, const T& e, Rank lo, Rank hi);    //斐波那契查找
    void show(); //输出向量
    T get(Rank r) { return _elem[r]; }  //返回秩为r元素
//可写访问接口
    T& operator[](Rank r) const;    //重载下标操作符，使其可以像数组一样引用各元素
    Vector<T>& operator=(const Vector<T>&); //  重载赋值运算符,便于直接克隆向量
    T remove(Rank r);   //删除秩为r的元素,并返回
    T put(Rank r, const T& e) { T oldElement = _elem[r]; _elem[r] = e; return oldElement; }  //将秩为r的元素替换为e，并返回该元素
    int remove(Rank lo, Rank hi);   //删除秩在区间[lo,hi)之内的元素
    Rank insert(Rank r, const T& e);    //插入元素
    Rank insert(const T& e) { return insert(_size, e); }    //默认作为末尾元素插入
    void sort(Rank lo, Rank hi);    //对[lo,hi)排序
    void sort() { sort(0, _size); } //整体排序
    void unsort(Rank lo, Rank hi);  //对[lo,hi)置乱
    void unsort() { unsort(0, _size); } //整体置乱
    int deduplicate();  //无序去重
    int uniquify();     //有序去重
//遍历
    void traverse(void (*)(T&));    //遍历（使用函数指针，只读或者局部性修改)
    template <typename VST> void traverse(VST&);    //遍历（使用函数对象，可全局性修改）
};//Vector

#endif /* Vector_hpp */

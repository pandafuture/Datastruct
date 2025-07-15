#include <iostream>

#define MAX_SIZE 100  // 定义静态顺序表的最大长度
// 静态顺序表结构体
struct StaticSeqList {
    int data[MAX_SIZE];  // 静态数组：用于存储顺序表的元素
    int length;  // 当前顺序表的长度（即元素个数）
};



// 初始化顺序表
void InitList(StaticSeqList &L){
    L.length = 0; // 将顺序表的长度初始化为0，表示空表
}



// 在顺序表第i个元素插入元素e
bool ListInsert(StaticSeqList &L, int i, int e) {
    // 判断插入位置是否合法，i是位序，在1 ~ length+1之间
    if(i < 1 || i > L.length +1)
        return false;
    // 判断表是否已满
    if(L.length >= MAX_SIZE)
        return false;
    
    // 将第i个元素及其后面的元素都后移一个位置（从最后一个元素开始移动）
    for(int j = L.length; j >= i; j--) {
        L.data[j] = L.data[j - 1];  // 把前一个位置的元素赋值给当前位置
    }
    L.data[i - 1] = e;  // 在位置为i-1（数组下标）除插入元素e
    L.length++;  // 表长增加1
    return true;
}



// 删除顺序表第i个位置的元素，并用e返回
bool ListDelete(StaticSeqList &L, int i, int &e) {
    // 判断删除位置是否合法， i必须在1~length之间
    if(i < 1 || i > L.length)
        return false;

    // 保存被删除元素的值
    e = L.data[i - 1];

    // 将第i个元素之后的元素向前移一个位置（从第i个位置开始）
    for(int j = i; j < L.length; j++) {
        L.data[j - 1] = L.data[j];  // 将后一个位置的元素赋值给前一个位置
    }
    L.length--;  // 表长减1
    return true;
}



// 按值查找：返回顺序表中第一个值为e的元素的位序，找不到返回0
int LacateElem(StaticSeqList L, int e) {
    for(int i = 0; i < L.length; i++) {
        if(L.data[i] == e)
            return i + 1;  // 返回位序
    }
    return 0;
}



// 按位查找：返回顺序表中第i个元素的值
int GetElem(StaticSeqList L, int i) {
    return L.data[i - 1];  // 第i个元素存放在数组中的第i-1个位置
}



// 遍历打印顺序表
void PrintList(StaticSeqList L) {
    for(int i = 0; i < L.length; i++) {
        std::cout << L.data[i] << " ";
    }
    std::cout << std::endl;
}


int main(){
    StaticSeqList L;  // 新建一个静态顺序表L
    int e;  // 用来返回删除的值
    InitList(L);  // 初始化静态顺序表L

    ListInsert(L, 1, 1);  // 在L的第一个位序插入1
    ListInsert(L, 2, 2);  // 在L的第二个位序插入2
    ListInsert(L, 3, 3);  // 在L的第三个位序插入3
    ListInsert(L, 4, 4);  
    ListInsert(L, 5, 5);
    PrintList(L);  // 遍历打印顺序表

    ListDelete(L, 1, e);  // 删除L中的一号位置的元素，并返回其值
    PrintList(L);  // 遍历打印顺序表

    std::cout << LacateElem(L, 3);  // 按值查找操作
    std::cout << std::endl;

    std::cout << GetElem(L, 1) << " ";  // 按位查找第1个位序的元素
    std::cout << std::endl;

    PrintList(L);  // 遍历打印顺序表
    return 0;
}
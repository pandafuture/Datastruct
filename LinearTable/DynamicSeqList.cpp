#include <iostream>
#include <cstdlib>  // 包含malloc和free函数

// 动态顺序表结构
struct DynamicSeqList {
    int *data;  // 指向动态分配数组的指针，指向这一片存储空间的存储地址
    int maxSize;  // 数组的最大容量
    int length;  // 当前长度
};


// 初始化动态顺序表，size为初始分配的大小
void InitList (DynamicSeqList &L, int size) {
    L.data = (int *)malloc(size * sizeof(int));  // 申请size个大小为int的空间，并用malloc函数返回一个强制转换为int类型的指向这片空间开始地址的指针
    if(!L.data)
        exit(1);  // 如果分配失败，则退出程序
    L.length = 0;  // 初始长度为0
    L.maxSize = size;  // 记录最大容量
}


// 判空
bool Empty(DynamicSeqList L) {
    return L.length == 0;
}


// 增加动态顺序表的容量（增加len个长度）
void IncreaseSize(DynamicSeqList &L, int len) {
    int *p = L.data;  // 保存原数组指针
    // 申请新的更大的空间
    L.data = (int *)malloc((L.maxSize + len) * sizeof(int));
    if(!L.data)
        exit(1);  // 如果分配失败，则退出程序
    
    // 将原数组的元素复制到新数组
    for(int i = 0; i < L.length; i++) {
        L.data[i] = p[i];
    }
    L.maxSize += len;  // 更新最大容量
    free(p);  // 释放原空间
}


// 在顺序表第i个位置插入元素e
bool ListInsert(DynamicSeqList &L, int i, int e) {
    // 判断插入位置是否合法，i必须在1~length+1之间
    if(i < 1 || i > L.length + 1) 
        return false;
    // 判断表是否已满，若已满则增加表容量
    if(L.length >= L.maxSize)
        IncreaseSize(L, 10);

    // 将第i个元素及其后面的元素往后移一个位置（从最后一个元素开始）
    for(int j = L.length; j >= i; j--) {
        L.data[j] = L.data[j - 1];  // 将前一个位置的元素赋值给当前位置
    }
    L.data[i -1] = e;  // 当位置i-1出插入元素e
    L.length++;  // 表长加1
    return true;
}


// 删除表中第i个元素，并用e返回
bool ListDelete(DynamicSeqList &L, int i, int &e) {
    // 判断删除位置是否合法，i必须要在1~length之间
    if(i < 1 || i > L.length)
        return false;
        
    e = L.data[i -1];  // 保存被删除元素的值

    // 将第i个元素之后的所有元素前移一位（从第一个元素开始）
    for(int j = i; j < L.length; j++) {
        L.data[j - 1] = L.data[j];  // 将后一个位置的元素赋值给前一个元素
    }
    L.length--;  // 表长减1
    return true;
}


// 按值查找：找到第一个值为e的元素的位序，找不到返回0
int LocateElem(DynamicSeqList L, int e) {
    for(int i = 0; i < L.length; i++) {
        if(L.data[i] == e)
            return i + 1;  // 返回位序
    }
    return 0;  // 未找到
}


// 按位查找：返回列表中第i个元素的值
int GetElem(DynamicSeqList L, int i) {
    return L.data[i -1];
}


// 求表长
int Length(DynamicSeqList L) {
    return L.length;
}


// 遍历打印顺序表
void PrintList(DynamicSeqList L) {
    for(int i = 0; i < L.length; i++){
        std::cout << L.data[i] << " ";
    }
    std::cout << std::endl;
}
 

// 销毁操作
void DestroyList(DynamicSeqList &L) {
    free(L.data);
    L.data = nullptr;
    L.length = 0;
    L.maxSize = 0;
}


int main(){
    DynamicSeqList L;  // 声明一个动态顺序表
    InitList(L ,5);  // 初始化
    int e;

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空操作
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    ListInsert(L, 1, 1);  // 在第一个位置插入 1
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    ListInsert(L, 4, 4);
    ListInsert(L, 5, 5);

    std::cout << "输出：";
    PrintList(L);  // 打印顺序表

    ListDelete(L, 2, e);  // 删除操作
    std::cout << "输出：";
    PrintList(L);

    ListInsert(L, 2, 2);  // 插入操作
    std::cout << "输出：";
    PrintList(L);

    ListInsert(L, 6, 6);  // 在超过表长的位置插入 6
    std::cout << "输出：";
    PrintList(L);

    std::cout << "按值查找：" << LocateElem(L, 3) << std::endl;  // 找到第一个值为 3 的位序

    std::cout << "按位查找：" << GetElem(L, 6) << std::endl;  // 找到第六个元素的值

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空操作
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    DestroyList(L);  // 销毁操作
    std::cout << "判空：" << Empty(L) << std::endl;  // 判空操作
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长
}
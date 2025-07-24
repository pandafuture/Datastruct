#include <iostream>

// 定义循环单链表的结点结构
struct CNode {
    int data;  // 数据域
    CNode *next;  // 指针域
};


// 初始化循环单链表
void InitList(CNode *&L) {
    L = new CNode;  // 新建一个头结点
    L -> next = L;  // 让头结点的 next 域指向自己，形成循环
}


// 判空
bool Empty(CNode *L) {
    return L -> next == L;  // 看头结点的 next 是否指向自己，如果是，则为空，如果不是，则不为空
}


// 判断结点 p 是否为最后一个结点 
bool isTail(CNode *L, CNode *p) {
    return p -> next == L;  // 看 p 的 next 是否指向头结点，如果是，则为最后一个结点，反之，不是最后一个结点
}


// 插入（在第 i 个位置插入一个结点 e）
bool ListInsert(CNode *L, int i, int e) {
    if(i < 1)
        return false;  // 判断插入位置是否合法，i 不能为 0
    
    // 找到第 i-1 个结点
    CNode *p = L;  // 新建一个指针 p ，指向头结点
    int j = 0;  // 设置一个计数器，记录当前指向第几个结点，默认为 0 （头结点记为 0 ）
    while(p -> next != L && j < i - 1) {  // 遍历链表，直到找到第 i-1 个结点
        p = p -> next;
        j++;
    }
    if(j != i - 1) 
        return false;  //如果计数器未指向第 i-1 个结点，则说明位置 i 超过了 表长+1

    CNode *s = new CNode;  // 新建一个结点 s
    s -> data = e;  // 把 e 的值赋给 s
    s -> next = p -> next;  // 把新结点 s 的 next 指向第 i 个结点
    p -> next = s;  // 把第 i-1 个结点的 next 指向 s
    return true;
}


// 删除（删除第 i 个位置的结点，并用 e 返回）
bool ListDelete(CNode *L, int i, int &e) {
    // 判断删除位置是否合法，i 不能为 0
    if(i < 1)
        return false;

    // 找到第 i-1 个位置的结点
    CNode *p = L;  // 新建一个结点，指向头结点
    int j = 0;  // 设置一个计数器，记录当前指向第几个结点。默认为 0 （指向头结点）
    while(p -> next != L && j < i - 1) {  // 遍历整个链表，找到第 i-1 个结点
        p = p -> next;
        j++;
    }
    if(p -> next == L || j != i - 1) 
        return false;  // 如果遍历过程中，p 指向了尾结点，则说明删除位置 i 超过了表长

    CNode *q = p -> next;  // 新建一个指针 q ，指向被删除结点
    e = q -> data;  // 用 e 存储被删除结点的值
    p -> next = q -> next;  // 把结点 p 的 next 指向被删除结点后面的一个结点
    delete q;  // 释放被删除结点 q 的空间
    
    return true;
}


// 按值查找
int LocateElem(CNode *L, int e) {
    CNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    int j = 1;  // 设置一个计数器，记录当前指向第几个结点
    while(p != L) {
        if(p -> data == e)
            return j;  // 如果找到就返回位序
        p = p -> next;
        j++;
    }
    return 0;  // 若没找到就返回 0
}


// 按位查找
int GetElem(CNode *L, int i) {
    // 判断输入是否合法，不能小于 1
    if(i < 1)
        return -1;
    
    CNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    int j = 1;  // 设置一个计数器，记录当前指向第几个结点
    while(p != L && j < i) {
        p = p -> next;
        j++;
    }
    if(p == L)
        return -1;  // 如果为找到就返回 -1
    return p -> data;  // 如果找到了就返回其值
}


// 求表长
int Length(CNode *L) {
    int length = 0;  // 设置一个表长计数器
    CNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    while(p != L) {
        length++;
        p = p -> next;
    }
    return length;  // 返回最终表长
}


// 遍历打印循环单链表
void PrintList(CNode *L) {
    CNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    while(p != L) {  // 遍历整个链表，并输出每个结点的值
        std::cout << p -> data << " ";
        p = p -> next;
    }
    std::cout << std::endl;  // 换行
}


// 销毁操作
void DestroyList(CNode *&L) {
    CNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    while(p != L) {
        CNode *temp = p;  // 新建一个指针 temp ，指向 p 指向的结点
        p = p -> next;
        delete temp;  // 删除 temp 指向的结点
    }
    delete L;  // 删除头结点
    L = nullptr;  // 把头指针置为空
}


// 测试
int main() {
    CNode *L;  // 创建一个循环单链表 L
    int e;
    InitList(L);  // 初始化

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    ListInsert(L, 1, 1);  // 在 L 的第 1 个位置插入 1
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    std::cout << "输出：";
    PrintList(L);  // 打印链表

    ListInsert(L, 1, 4);
    std::cout << "输出：";
    PrintList(L);
    ListInsert(L, 5, 5);
    std::cout << "输出：";
    PrintList(L);
    ListInsert(L, 6, 6);
    std::cout << "输出：";
    PrintList(L);

    ListDelete(L, 6, e);  // 删除 L 的第 1 个结点，并用 e 返回
    std::cout << "输出：";
    PrintList(L);
    std::cout << "删除：" << e << std::endl;

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    std::cout << "按值查找：" << LocateElem(L, 3) << std::endl;  // 按值查找
    std::cout << "按位查找: " << GetElem(L, 2) << std::endl;  // 按位查找

    DestroyList(L);  // 销毁

    return 0;
}
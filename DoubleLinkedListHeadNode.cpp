#include <iostream>

// 带头结点的双链表结点结构
struct DNode {
    int data;  // 数据域
    DNode *prior;  // 指向前驱的指针
    DNode *next;  // 指向后继的指针 
};


// 初始化双链表
void InitList(DNode *&L) {
    L = new DNode;  // 新建一个头结点
    L -> prior = nullptr;  // 双链表的头结点的 prior 指针永远指向空
    L -> next = nullptr;  // 当前没有其他结点，头结点的 next 指向空
}


// 在第 i 个位置插入元素 e
bool ListInsert(DNode *L, int i, int e) {
    if(i < 1)
        false;  // 插入位置不能为0
    
    // 找到第 i-1 个结点
    DNode *p = L;  // 新建一个指针 p ，指向头结点
    int j = 0;  // 设置一个计数器，表示当前指向第几个结点，默认为 0 （带头结点）
    while(p && j < i - 1) {
        p = p -> next;
        j++;
    }
    if(!p)
        false;  // 如果第 i-1 个位置的结点为空，说明插入位置超过了 表长+1

    DNode *s = new DNode;  // 新建一个结点 s
    s -> data = e;  // 把 e 赋给 s 的 data 域
    s -> next = p -> next;  // 让新结点 s 的 next 指向第 i 个结点
    if(p -> next)
        p -> next ->prior = s;  // 如果 p 不是最后一个结点，那就让第 i 个结点的 prior 指向 s
    s -> prior = p;  // 让 s 的 prior 指向 p
    p -> next = s;  // 让 p 的 next 指向 s

    return true;
}

// 删除第 i 个位置的结点，并用 e 返回
bool ListDelete(DNode *L, int i, int &e) {
    if(i < 1)
        return false;  // 判断输入是否合法，删除位置不能为0
    
    // 找到被删除的结点
    DNode *p = L -> next;  // 新建一个指针 p , 指向链表中第一个结点（不是头结点）
    int j = 1;  // 设置一个计数器，表示当前指向第几个结点
    while(p && j < i) {
        p = p -> next;
        j++;
    }
    if(!p) 
        return false;  // 如果未找到第 i 个节点，说明位置 i 超出了表长

    // 删除结点
    e = p -> data;  // 把被删除结点 p 的值赋给 e
    p -> prior ->next = p ->next;  // 让第 i-1 个结点的 next 指向第 i+1 个结点
    if(p -> next)
        p -> next ->prior = p -> prior;  // 如果 p 不是最后一个结点，就把 p 后面的结点的 prior 指向 p 前面的结点
    delete p;  // 释放结点 p 的空间

    return true;
}


// 遍历打印链表
void PrintList(DNode *L) {
    DNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    while(p) {
        std::cout << p -> data << " ";  // 遍历输出当前结点的值
        p = p -> next;
    }
    std::cout << std::endl;  // 换行
}


int main() {
    DNode *L;  // 新建一个双链表 L
    int e;
    InitList(L);  // 初始化 L

    ListInsert(L, 1, 1);  // 在第一个位置插入 1
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    PrintList(L);  // 遍历打印链表

    ListInsert(L, 2, 4);  // 在第一个位置插入 4
    PrintList(L);

    ListDelete(L, 2, e);  // 删除第 2 个位置的元素并用 e 返回
    PrintList(L);
    std::cout << e << " ";
    return 0;
}
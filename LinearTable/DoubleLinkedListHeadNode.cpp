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


// 判空
bool Empty(DNode *L) {
    return L -> next == nullptr;  // 返回头结点的 next 是否为空
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


// 按值查找
int LocateElem(DNode *L, int e) {
    DNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    int j = 1;  // 设置一个计数器，记录当前指向第几个结点，默认为 1 ，指向第一个结点
    while(p) {
        if(p -> data == e) 
            return j;
        p = p -> next;
        j++;
    }
    return 0;  // 未找到则返回 0
}


// 按位查找
int GetElem(DNode *L, int i) {
    // 判断输入是否合法，不能小于 1
    if(i < 1) 
        return -1;
    
    DNode *p = L -> next;  // 新建一个指针，指向第一个结点
    int j = 1;  // 设置一个计数器，记录当前指向第几个结点
    // 遍历整个链表，找到第 i 个结点
    while(p && j < i) {
        p = p -> next;
        j++;
    }
    if(!p)  // 若没找到则返回 -1
        return -1;
    // 若找到，则返回其值
    return p -> data;
}


// 求表长
int Length(DNode *L) {
    int length = 0;  // 设置一个表长计数器，记录表长
    DNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    //遍历整个链表，每遍历一个结点就记录一个
    while(p) {
        length++;
        p = p -> next;
    }
    // 返回表长
    return length;
}


// 后向遍历输出链表
void PrintList_BackwardTraversal(DNode *L) {
    DNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    while(p) {
        std::cout << p -> data << " ";  // 遍历输出当前结点的值
        p = p -> next;
    }
    std::cout << std::endl;  // 换行
}


// 销毁操作
void DestroyList(DNode *&L) {
    DNode *p = L -> next;  // 新建一个指针 P ，指向第一个结点
    while(p) {
        DNode *temp = p;  // 新建一个指针 temp ，指向 p 指向的结点
        p = p -> next;
        delete temp;  // 删除结点
    }
    delete L;  // 删除头结点
    L = nullptr;  // 头指针指向空
}


int main() {
    DNode *L;  // 新建一个双链表 L
    int e;
    InitList(L);  // 初始化 L
    std::cout << "判空：" << Empty(L) << std::endl;  // 判空操作
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    ListInsert(L, 1, 1);  // 在第一个位置插入 1
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    std::cout << "输出: ";
    PrintList_BackwardTraversal(L);  // 遍历打印链表

    ListInsert(L, 2, 4);  // 在第二个位置插入 4
    std::cout << "输出：";
    PrintList_BackwardTraversal(L);

    ListDelete(L, 2, e);  // 删除第 2 个位置的元素并用 e 返回 
    std::cout << "输出：";
    PrintList_BackwardTraversal(L);
    std::cout << "删除元素为：" << e << std::endl;

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空操作
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    DestroyList(L);  // 销毁操作
    return 0;
}
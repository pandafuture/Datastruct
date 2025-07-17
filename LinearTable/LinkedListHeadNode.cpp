#include <iostream>

// 单链表节点结构
struct LNode {
    int data;  // 数据域
    LNode *next;  // LNode类型的指针域，指向下一个节点
};


// 初始化单链表
void InitList(LNode *&L) {
    L = new LNode;  // 创建一个头结点
    L -> next = nullptr;  // 头结点的next设为空
}


// 判空
bool Empty(LNode *L) {
    return L -> next == nullptr;
}


// 头插法插入元素（在头结点之后插入）
void HeadInsert(LNode *L, int e) {
    LNode *s = new LNode;  // 新建一个结点
    s -> data = e;  // 把 e 赋值给s的数据域
    s -> next = L -> next;  // 把新结点的next指向头结点的next
    L -> next = s;  // 把头结点的next指向s
}


// 尾插法插入元素（在链表尾部插入）
void TailInsert(LNode *L, int e) {
    LNode *s = new LNode;  // 新建一个结点
    s -> data = e;  // 把 e 赋给s的数据域
    s -> next = nullptr;  // 把新结点的next指向空

    LNode *p = L;  // 新建一个指针P，指向头结点
    while(p -> next) {
        p = p -> next;  // 从头结点开始循环整个链表，直到找到当前链表内next指向空的尾结点
    }
    p -> next = s;  // 把s结点放到链表尾部
}


// 按位删除（删除第i个结点，并返回其值）
bool ListDelete(LNode *L, int i, int &e) {
    if(i < 1)
        return false;  // 判断输入是否合法，删除位置不能为0，是否超过表长+1在后面判断

    // 首先要找到被删除结点的前一个结点
    LNode *p = L;  // 新建一个指针P，指向头结点
    int j = 0;  // 设置一个计数器，记录当前是第几个结点
    while(p -> next && j < i - 1) {
        p = p  -> next;  // 循环查找，直到找到第i-1个结点
        j++;  // 计数器加一
    }
    if(!p -> next)
        false;  // 若p的next指向空，则说明i超出表长+1
        
    LNode *q = p -> next;  // 新建一个指针q，指向被删除的结点
    e = q -> data;  // 用e记录被删除结点的值
    p -> next = q -> next;  // 把被删除结点的前一个结点的next指向被删除结点的下一个结点
    delete q;  // 释放被删除结点的空间
    return true;
}


// 按值查找（找到第一个值为 e 的元素的位序，找不到返回 0
int LocateElem(LNode *L, int e) {
    LNode *p = L -> next;  // 新建一个指针 p ，指向头结点后的第一个结点
    int j = 1;  // 新建一个计数器，用来表示当前指向第几个结点，初始为 1 ，指向第一个结点
    while(p) {
        if(p -> data == e)
            return j;  // 若找到则返回位序
        j++;
        p = p -> next;
    }
    return 0;  // 未找到
}


// 按位查找（返回表中第 i 个位置的元素的值）
int GetElem(LNode *L, int i) {
    // 先判断输入是否合法，查询位置不可以小于 0
    if(i < 1)
        return false;

    LNode *p = L -> next;  // 新建一个指针 p ，指向头结点后的第一个结点
    int j = 1;  // 新建一个计数器，用来表示当前指向第几个结点
    // 找到第 i 个结点
    while(p && j < i) {
        j++;
        p = p -> next;
    }
    if(!p)  // 如果没有找到第 i 个结点，说明超过了表长
        return false;
    
    return p -> data;
}


// 交换位置（把第 i 个结点和前驱结点交换）
bool Transform(LNode *L, int i) {
    if(i < 1) 
        return false;  // 判断输入是否合法

    // 首先找到第 i 个结点的前驱结点的前驱结点
    LNode *w = L;  // 新建一个指针，指向头结点
    int j = 0;  // 设置一个计数器，记录当前指向第几个结点，默认为0， 指向头结点
    while(w -> next && j < i - 2) {
        w = w -> next;
        j++;
    }
    if(!w -> next -> next) {
        return false;
    }
    
    LNode *q = w -> next;  // 新建一个指针 q ，指向第 i-1 个结点
    LNode *p = q -> next;  // 新建一个指针 p ，指向第 i 个结点
    LNode *e = p -> next;  // 新建一个指针 e ，指向第 i+1 个结点

    w -> next = p;  // 先把第 i-2 个结点的next 指向第 i 个结点
    p -> next = q;  // 把第 i 个结点的 next 指向第 i 个结点的前驱结点
    q -> next = e; // 最后把第 i-1 个结点的next指向 第i+1个结点

    return true;
}


// 求表长
int Length(LNode *L) {
    LNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点（不是头结点）
    int length = 0;  // 设置一个计数器，表示当前表长

    while(p) {
        length++;
        p = p -> next;;
    }
    return length;
}


// 遍历打印链表
void PrintList(LNode *L) {
    LNode *p = L ->next;  // 新建一个指针p， 指向头结点后的第一个结点
    while(p) {
        std::cout << p -> data << " ";  // 打印出当前结点的数据域
        p = p -> next;  // 打印完p指针指向下一个结点
    }
    std::cout << std::endl;  // 换行
}


// 销毁操作
void DestroyList(LNode *&L) {
    LNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    while(p) {
        LNode *temp = p;  // 新建一个指针 temp ，指向第一个结点
        p = p -> next;
        delete temp;  // 删除结点
    }
    delete L;  // 删除头结点
    L = nullptr;  // 头指针指向空
}


int main() {
    LNode *L;  // 创建一个单链表L
    InitList(L);  // 初始化单链表L
    int e;  // 用走返回值
    std::cout << "判空：" << Empty(L) << std::endl;  // 判空
    std::cout << "求表长：" << Length(L) << std::endl;  // 求表长

    HeadInsert(L, 1);  // 头插法插入1
    HeadInsert(L, 2);  // 头插法插入2
    HeadInsert(L, 3);  // 头插法插入3
    std::cout << "输出：";
    PrintList(L);  // 遍历打印单链表

    Transform(L, 3);  // 交换第三个结点
    std::cout << "输出：";
    PrintList(L);  // 遍历打印单链表

    TailInsert(L, 4);  // 尾插法插入4
    TailInsert(L, 5);  // 尾插法插入5
    TailInsert(L, 6);  // 尾插法插入6
    std::cout << "输出：";
    PrintList(L);  // 遍历打印单链表

    ListDelete(L, 6, e);  // 删除第六个结点，并用e返回
    std::cout << "输出：";
    PrintList(L);  // 遍历打印单链表

    std::cout << "按位查找：" << GetElem(L, 1) << std::endl;  // 按位查找第一个位置
    std::cout << "按值查找：" << LocateElem(L, 4) << std::endl;  // 按值查找 4

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    DestroyList(L);  // 销毁操作

    return 0;
}
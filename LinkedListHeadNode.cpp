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


// 遍历打印链表
void PrintList(LNode *L) {
    LNode *p = L ->next;  // 新建一个指针p， 指向头结点后的第一个结点
    while(p) {
        std::cout << p -> data << " ";  // 打印出当前结点的数据域
        p = p -> next;  // 打印完p指针指向下一个结点
    }
    std::cout << std::endl;  // 换行
}


int main() {
    LNode *L;  // 创建一个单链表L
    InitList(L);  // 初始化单链表L
    int e;  // 用走返回值

    HeadInsert(L, 1);  // 头插法插入1
    HeadInsert(L, 2);  // 头插法插入2
    HeadInsert(L, 3);  // 头插法插入3
    PrintList(L);  // 遍历打印单链表

    TailInsert(L, 4);  // 尾插法插入4
    TailInsert(L, 5);  // 尾插法插入5
    TailInsert(L, 6);  // 尾插法插入6
    PrintList(L);  // 遍历打印单链表

    ListDelete(L, 6, e);  // 删除第一个结点，并用e返回
    PrintList(L);  // 遍历打印单链表
    return 0;
}
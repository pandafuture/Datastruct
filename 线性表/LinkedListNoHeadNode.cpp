#include <iostream>

// 不带头结点的单链表结点结构
struct LNode {
    int data;  // 数据域
    LNode *next;  // 指针域
};


// 初始化单链表
void InitList(LNode *&L) {
    L = nullptr;  // 因为不带头结点，就将头指针指向空
}


// 插入操作，在第i个位置插入e
bool ListInsert(LNode *&L, int i, int e) {
    if(i < 1) {
        false;  // 判断输入是否合法，位置不能小于1
    }
    else if(i == 1) {  // 若在第一个位置插入
        LNode *s = new LNode;  // 创建一个新结点s
        s -> data = e;  // 把e的值赋给s的数据域
        s -> next = L;  // 把新建的s结点的next指向当前第一个结点L
        L = s;  // 把头指针指向s
    }
    else {
        LNode *p = L;  // 新建一个指针p，指向当前第一个结点
        int j = 1;  // 用来记录当前指向第几个结点，默认当前指向一号
        while(p && j < i - 1) {  // 找到插入位置的前一个结点
            p = p -> next;
            j++;
        }
        if(!p)
            return false;  // 插入位置前一个结点为空，说明此位置超过了表长+1

        LNode *s = new LNode;  // 新建一个结点s
        s -> data = e;  // 把e赋给s的数据域
        s -> next = p -> next;  // 让s的next指向被插入位置上的结点
        p -> next = s;  // 把插入位置前一个结点和新结点连接起来
    }
    return true;
}


// 删除操作（删除第i个结点，并返回其值
bool ListDelete(LNode *&L, int i, int &e) {
    if(i < 1) {
        return false;  // 删除位置不能小于1
    }
    // 若删除第一个结点
    else if(i == 1) {
        LNode *p = L;  // 新建一个指针p，指向当前表中第一个结点
        e = p -> data;  // 用e返回被删除结点的值
        L = L -> next;  // 把头指针指向第二个结点
        delete p;  // 删除第一个结点
    }
    else{
        // 找到被删除结点的前一个结点
        LNode *p = L;  // 新建一个指针p，指向当前第一个结点
        int j = 1;  // 记录当前是第几个结点，默认指向第一个
        while(p -> next && j < i - 1) {
            p = p -> next;
            j++;
        }
        if(!p -> next) 
            return false;  // 说明第i个位置没有结点，超出了表长
    
        LNode *q = p -> next;  // 新建一个指针q，指向被删除的结点
        e = q -> data;  // 用e返回被删除结点的值
        p -> next = q -> next;  // 把第i-1个结点的next指向被删除结点的下一个结点
        delete q;  // 释放被删除结点的空间
    }
    return true;
}


// 遍历打印单链表
void PrintList(LNode *L) {
    LNode *p = L;  // 新建一个指针p，指向表中第一个结点
    while(p) {
        std::cout << p -> data << " ";  // 打印当前结点的值
        p = p -> next;
    }
    std::cout << std::endl;    
}


int main() {
    LNode *L;  // 新建一个单链表（不带头结点）
    int e;

    InitList(L);  // 初始化单链表

    ListInsert(L, 1, 1);  // 在第一个位置插入1
    ListInsert(L, 2, 2);  // 在第二个位置插入2
    ListInsert(L, 3, 3);  // 在第三个位置插入3
    PrintList(L);  // 遍历打印单链表

    ListInsert(L, 2, 4);  // 在第二个位置插入4
    PrintList(L);

    ListDelete(L, 2, e);  // 删除第二个结点，并用e返回
    PrintList(L);
    std::cout << e << " ";  // 打印e的值

    return 0;
}
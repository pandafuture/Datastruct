#include <iostream>

// 定义循环双链表的结点结构
struct CDNode {
    int data;  // 数据域
    CDNode *prior;  // 指向前驱的指针
    CDNode *next;  // 指向后继的指针
};


// 初始化
void InitList(CDNode *&L) {
    L = new CDNode;  //  创建一个头结点
    L -> prior = L;  // 让头结点的 prior 指向头结点自己
    L -> next = L;  // 当前表中没有其他结点，让头结点的 next 指向自己
}


// 插入（在第 i 个位置，插入结点 e）
bool ListInsert(CDNode *L, int i, int e) {
    // 判断输入是否合法，插入位置 i 不能为 0
    if(i < 1)
        return false;

    //找到插入位置的前一个位置上的结点
    CDNode *p = L;  // 新建一个指针 p ，指向头结点
    int j = 0;  // 设置一个计数器，记录当前指向第几个结点，默认为 0 （头结点记为 0 ）
    while(p -> next != L && j < i - 1) {  // 遍历整个链表，直到找到第 i-1 个结点
        p = p -> next;
        j++;
    }
    if(j != i - 1) 
        return false;  // 如果遍历完整个链表还未找到第 i-1 个结点，就说明插入位置超过 表长+1
    
    // 插入
    CDNode *s = new CDNode;  // 新建一个结点 s
    s -> data = e;  // 把 e 的值传给 s 的数据域
    s -> prior = p;  // 把 s 的prior 指向被删除结点的前一个结点
    s -> next = p -> next;  // 把 s 的 next 指向被删除的结点
    p -> next -> prior = s;  // 把被删除结点的 prior 指向 s
    p -> next = s;  // 被第 i-1 个结点的 next 指向新结点
    return true;
}


// 删除（删除第 i 个结点，并用 e 返回）
bool ListDelete(CDNode *L, int i, int &e) {
    // 判断输入是否合法，i 不能为 0
    if(i < 1) 
        return false;

    // 找到被删除的结点
    CDNode *p = L; // 新建一个指针 p ，指向头结点
    int j = 0;  // 设置一个计数器，记录当前指向第几个结点，默认为 0 （指向头结点）
    while(p -> next != L && j < i) {  //遍历整个链表，直到找到第 i 个结点
        p = p -> next;
        j++;
    }
    if(j != i) 
        return false;  // 如果没有找到第 i 个结点，就说明删除位置超过表长

    e = p -> data;  // 用 e 返回被删除结点的值
    p -> next ->prior = p -> prior;  // 被删除结点后面的结点和被删除结点前面的结点连起来
    p -> prior -> next = p -> next;  // 把被删除结点前面的结点和被删除结点后面的结点连起来
    delete p;  // 释放被删除结点 p 的空间
    
    return true;
}


// 遍历打印循环双链表
void PrintList(CDNode *L) {
    CDNode *p = L -> next;  // 设置一个指针 p ，指向第一个结点
    int j = 0;  // 设置一个计时器，记录当前指向的结点，默认为 0 （带头结点）
    while(p != L) {
        std::cout << p -> data << " ";  // 遍历整个链表，同时输出结点的值
        p = p -> next;
    }
    std::cout << std::endl;  // 换行
}

// 测试
int main() {
    CDNode *L;  // 新建一个循环双链表
    int e;
    InitList(L);  // 初始化

    ListInsert(L, 1, 1);  // 在 L 的第 1 个位置插入 1
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    PrintList(L);  // 打印 L 

    ListInsert(L, 1, 4);
    PrintList(L);
    ListInsert(L, 2, 5);
    PrintList(L);
    ListInsert(L, 6, 6);
    PrintList(L);
    ListInsert(L, 8, 7);
    PrintList(L);

    ListDelete(L, 1, e);
    PrintList(L);
    ListDelete(L, 2, e);
    PrintList(L);
    ListDelete(L, 4, e);
    PrintList(L);

    ListDelete(L, 4, e);
    PrintList(L);
    
    return 0;
}
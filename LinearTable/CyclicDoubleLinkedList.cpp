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


// 判空
bool Empty(CDNode *L) {
    return L -> next == L;  // 返回头结点的 next 是否指向自己
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


// 按值查找
int LocateElem(CDNode *L, int e) {
    CDNode *p = L -> next;  // 新建一个指针 P ，指向第一个结点
    int j = 1;  // 设置一个计数器，记录当前指向第几个结点，默认为 1 ，指向第一个结点
    while(p != L) {
        if(p -> data == e)
            return j;  // 如果值为 e ，就返回其位序
        p = p -> next;
        j++;
    }
    return 0;  // 若没找到就返回 0
}


// 按位查找
int GetElem(CDNode *L, int i) {
    // 判断输入是否合法
    if(i < 1)
        return -1;
    
    CDNode *p = L -> next;  // 新建一个指针 P ，指向第一个结点
    int j = 1;  // 设置一个计数器，记录当前指向第几个结点
    // 遍历找到第 i 个结点
    while(p != L && j < i) {
        p = p -> next;
        j++;
    }
    if(p == L)
        return -1;  // 查找位置超出表长
    
    return p -> data;  // 返回第 i 个结点的值
}


// 求表长
int Length(CDNode *L) {
    int length = 0;  // 设置一个计数器，记录表长
    CDNode *p = L -> next;  // 新建一个指针，指向第一个结点
    while(p != L) {
        length++;
        p = p -> next;
    }
    return length;  // 返回最终表长
}


// 遍历打印循环双链表
void PrintList(CDNode *L) {
    CDNode *p = L -> next;  // 设置一个指针 p ，指向第一个结点
    while(p != L) {
        std::cout << p -> data << " ";  // 遍历整个链表，同时输出结点的值
        p = p -> next;
    }
    std::cout << std::endl;  // 换行
}


// 销毁操作
void DestroyList(CDNode *&L) {
    CDNode *p = L -> next;  // 新建一个指针 p ，指向第一个结点
    // 遍历整个链表
    while(p != L) {
        CDNode *temp = p;  // 新建一个指针 temp ，指向 p 指向的结点
        p = p -> next;
        delete temp;  // 删除 temp 指向的结点
    }
    delete L;  // 删除头结点
    L = nullptr;  // 头指针置为空
}


// 测试
int main() {
    CDNode *L;  // 新建一个循环双链表
    int e;
    InitList(L);  // 初始化

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    ListInsert(L, 1, 1);  // 在 L 的第 1 个位置插入 1
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    std::cout << "输出：";
    PrintList(L);  // 打印 L 

    ListInsert(L, 1, 4);
    std::cout << "输出：";
    PrintList(L);
    ListInsert(L, 2, 5);
    std::cout << "输出：";
    PrintList(L);
    ListInsert(L, 6, 6);
    std::cout << "输出：";
    PrintList(L);
    ListInsert(L, 8, 7);
    std::cout << "输出：";
    PrintList(L);

    ListDelete(L, 1, e);  // 删除第 1 个位置的元素
    std::cout << "删除第一个结点：";
    PrintList(L);
    ListDelete(L, 2, e);
    std::cout << "删除第二个结点: ";
    PrintList(L);
    ListDelete(L, 4, e);
    std::cout << "删除第四个结点：";
    PrintList(L);

    ListDelete(L, 4, e);
    std::cout << "删除第四个结点：";
    PrintList(L);

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    std::cout << "按值查找：" << LocateElem(L, 3) << std::endl;  // 按值查找 3
    std::cout << "按位查找：" << GetElem(L, 2) << std::endl;  // 按位查找 2

    DestroyList(L);  // 销毁

    return 0;
}
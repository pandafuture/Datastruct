#include <iostream>

// 链栈（带头结点）存储结构
struct LSNode {
    int data;  // 数据域
    LSNode *next;  // LSNode 类型的指针域，指向下一个结点
};


// 初始化链栈
void InitStack(LSNode *&S) {
    S = new LSNode;  // 创建一个头结点
    S -> next = nullptr;  // 头结点的 next 设为空
}
 

// 判空
bool Empty(LSNode *S) {
    return S -> next == nullptr;  // 看头结点的 next 是否为空
}


// 入栈操作
void Push(LSNode *&S, int e) {
    LSNode *w = new LSNode;  // 新建一个结点
    w -> data = e;  // 把 e 的值赋给 w
    w -> next = S -> next;  // 把新结点的 next 指向头结点的 next
    S -> next = w;  // 把头结点的 next 指向新结点 w
}


// 出栈操作
bool Pop(LSNode *&S, int &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    LSNode *p = S -> next;  // 新建一个指针 p ，指向第一个结点
    e = p -> data;  // 用 e 返回栈顶元素的值
    S -> next = p -> next;  // 把头结点的 next 指向栈顶元素的下一个元素
    delete p;  // 删除栈顶元素
    return true;
}


// 读栈顶元素
bool GetTop(LSNode *S, int &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    e = S -> next -> data;  // 用 e 返回栈顶元素的值
    return true;
}


// 输出栈
void PrintStack(LSNode *S) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return;
    }

    LSNode *p = S -> next;  // 新建一个指针 p ，指向栈顶元素
    while(p) {
        std::cout << p -> data << " ";  // 打印当前结点的数据域
        p = p -> next;
    }
    std::cout << std::endl;
}


// 销毁栈
void DestroyStack(LSNode *&S) {
    int e;
    // 循环弹出所有元素
    while(!Empty(S)) {
        Pop(S, e);
    }
}


// 测试
int main() {
    LSNode *S;  // 声明一个链栈（带头结点）
    int e;  // 返回值

    InitStack(S);  // 初始化链栈

    std::cout << "判空：" << Empty(S) << std::endl;  // 判空操作

    Push(S, 1);  // 将 1 入栈
    Push(S, 2);
    Push(S, 3);
    Push(S, 4);
    Push(S, 5);
    std::cout << "输出链栈：";
    PrintStack(S);

    Pop(S, e);  // 出栈
    std::cout << "出栈元素为：" << e << std::endl;
    std::cout << "输出链栈：";
    PrintStack(S);

    GetTop(S, e);  // 读取栈顶元素
    std::cout << "栈顶元素为：" << e << std::endl;

    std::cout << "判空：" << Empty(S) << std::endl;
    
    DestroyStack(S);  // 销毁链栈
}
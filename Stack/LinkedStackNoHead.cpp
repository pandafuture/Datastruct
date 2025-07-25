#include <iostream>

// 不带头结点的链栈存储结构
struct LSNode {
    int data;  // 数据域
    LSNode *next;  // 指针域
};


// 初始化链栈
void InitStack(LSNode *&S) {
    S = nullptr;  // 不带头结点，就把头指针指向空
}


// 判空操作
bool Empty(LSNode *S) {
    return S == nullptr;  // 直接返回头指针是否为空
}


// 入栈操作
bool Push(LSNode *&S, int e) {
    LSNode *w = new LSNode;  // 创建一个新结点 w
    w -> data = e;  // 把 e 的值赋给新结点 w
    w -> next = S;  // 把新结点 w 的 next 指向头指针指向的当前第一个结点
    S = w;  // 把头指针指向 w

    return true;
}


// 出栈操作
bool Pop(LSNode *&S, int &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    LSNode *p = S;  // 新建一个指针 p ，指向栈顶元素
    e = p -> data;  // 用 e 返回出栈元素的值
    S = S -> next;  // 把栈顶指针指向第二个元素
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

    e = S -> data;  // e 记录栈顶元素
    return true;
}


// 输出栈
void PrintStack(LSNode *S) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return;
    }

    LSNode *p = S;  // 新建一个指针 p ，指向栈顶元素
    while(p) {
        std::cout << p -> data << " ";  // 打印当前结点的值
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
    LSNode *S;  // 声明一个链栈（不带头结点）
    int e;  // 返回值

    InitStack(S);  // 初始化链栈
    std::cout << "判空：" << Empty(S) << std::endl;  // 判空操作
    
    Push(S, 1);  // 将 1 入栈
    Push(S, 2);
    Push(S, 3);
    std::cout << "输出链栈：";
    PrintStack(S);

    GetTop(S, e);  // 读取栈顶元素
    std::cout << "栈顶元素为：" << e << std::endl;

    std::cout << "判空：" << Empty(S) << std::endl;  // 判空操作

    Pop(S, e);  // 出栈
    std::cout << "出栈元素为：" << e << std::endl;
    std::cout << "输出链栈：";
    PrintStack(S);

    GetTop(S, e);  // 读取栈顶元素
    std::cout << "栈顶元素：" << e << std::endl;

    DestroyStack(S);  // 销毁链栈
}
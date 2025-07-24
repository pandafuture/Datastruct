#include <iostream>

#define MAX_SIZE 100  // 定义栈的最大容量


// 顺序栈结构体
struct SequenceStack {
    int data[MAX_SIZE];  // 存储栈元素的数组
    int top;  // 栈顶“指针” ，指向栈顶元素的数组下标
};


// 初始化
void InitStack(SequenceStack &S) {
    S.top = -1;  // 栈顶“指针”初始化为 -1 ，表示空栈
}


// 判空
bool Empty(SequenceStack S) {
    return S.top == -1;  // 直接返回栈顶“指针”是否为 -1
}


// 判满
bool Full(SequenceStack S) {
    return S.top == MAX_SIZE - 1;  // 直接返回栈顶“指针”是否为最大表长 - 1
}


// 入栈操作
bool Push(SequenceStack &S, int e) {
    // 先判断栈是否已满
    if(Full(S)) {
        std::cout << "栈已满" << std::endl;
        return false;
    }

    S.data[++S.top] = e;  // 栈顶“指针”先加一，然后入栈
    return true;
}


// 出栈操作
bool Pop(SequenceStack &S, int &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top--];  // 读取出栈顶元素的值，然后指针减一
    return true;
}


// 读栈顶元素
bool GetTop(SequenceStack S, int &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top];  // 获取栈顶元素的值
    return true;
}


// 打印栈
void PrintStack(SequenceStack S) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return;
    }

    // 从栈顶开始遍历整个栈，同时打印每个元素的值
    for (int i = S.top; i >= 0; i--) {
        std::cout << S.data[i] << " ";
    }
    std::cout << std::endl;
}


// 销毁操作
void DestroyStack(SequenceStack &S) {
    S.top = -1;  // 对于静态数组实现的栈，只需要重置栈顶指针
}


int main() {
    SequenceStack S;  // 声明一个顺序栈 S

    int e;  // 作为返回值

    InitStack(S);  // 初始化栈

    std::cout << "判空：" << Empty(S) << std::endl;  // 判空操作

    Push(S, 1);  // 把 1 入栈
    Push(S, 2);
    Push(S, 3);
    std::cout << "输出：";
    PrintStack(S);

    if(GetTop(S, e)) {
        std::cout << "栈顶元素为：" << e << std::endl;  // 读取栈顶元素
    }

    Pop(S, e);  // 出栈操作
    std::cout << "出栈的栈顶元素为：" << e << std::endl;
    std::cout << "输出：";
    PrintStack(S);

    std::cout << "判空: " << Empty(S) << std::endl;  // 判空操作
    
    std::cout << "判满：" << Full(S) << std::endl;  // 判满操作

    DestroyStack(S);  // 销毁操作
}
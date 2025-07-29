// 用顺序栈实现非递归算法求阶乘


#include <iostream>


// 递归算法求阶乘
int factorial(int n) {
    if(n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}


// 非递归算法求阶乘（用顺序栈实现）
#define MAX_SIZE 100  // 定义顺序栈最大容量


// 顺序栈结构体
struct SqStack {
    int data[MAX_SIZE];  // 存储元素的数组
    int top;  // 栈顶指针
};


// 初始化
void InitStack(SqStack &S) {
    S.top = -1;
}


// 判空
bool Empty(SqStack S) {
    return S.top == -1;
}


// 判满
bool Full(SqStack S) {
    return S.top == MAX_SIZE - 1;
}


// 入栈
bool Push(SqStack &S, int e) {
    // 先判断栈是否已满
    if(Full(S)) {
        std::cout << "栈已满" << std::endl;
        return false;
    }

    S.data[++S.top] = e;  // 先把指针加一，再入栈
    return true;
}


// 出栈
bool Pop(SqStack &S, int &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top--];  // 先出栈，再把栈顶指针减一
    return true;
}


// 用栈模拟递归计算阶乘
int factorial_byStack(int n) {
    // 判断输入是否合法
    if(n < 0) {
        std::cerr << "输入不能为负数" << std::endl;
        return -1;
    }

    if(n == 0) {
        return 1;  // 0 的阶乘等于 1
    }

    SqStack S;  // 声明一个顺序栈
    InitStack(S);  // 初始化

    // 把 n, n-1, n-2, ..., 2, 1 依次入栈
    for(int i = n; i >= 1; i--) {
        if(!Push(S, i)) {
            // 如果入栈失败则退出
            std::cerr << "入栈失败" << std::endl;
            return -1;
        }
    }

    int result = 1;  // 存储计算结果
    int e;  // 作为返回值
    // 依次出栈并相乘
    while(!Empty(S)) {
        if(!Pop(S, e)) {
            std::cerr << "出栈失败" << std::endl;
            return -1;
        }
        result *= e;
    }
    return result;  // 返回最终计算结果
}


int main() {
    int n = 5;  // 阶乘数

    // 使用递归算法求阶乘
    int x = factorial(n);
    std::cout << "使用递归算法求阶乘：" << n << "! = " << x << std::endl;
    
    // 使用栈模拟递归计算阶乘
    int result = factorial_byStack(n);
    std::cout << "使用栈模拟递归求阶乘：" << n << "! = " << result << std::endl;
    
    return 0;
}
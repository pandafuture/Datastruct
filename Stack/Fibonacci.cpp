// 用栈实现非递归算法求斐波那契数列


#include <iostream>
#include <vector>


// 递归算法求斐波那契数列
int Fibonacci(int n) {
    if(n == 0)
        return 0;  // 边界条件
    else if(n == 1)
        return 1;  // 边界条件
    else
        return Fibonacci(n - 1) + Fibonacci(n - 2);  // 递归表达式
}


// 非递归算法求斐波那契数列
#define MAX_SIZE 10  // 定义顺序栈的最大容量


// 顺序栈结构体
struct SqStack {
    int data[MAX_SIZE];  // 存储栈元素的数组
    int top;  // 栈顶指针
};


// 初始化栈
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

    S.data[++S.top] = e;  // 先把栈顶指针加一，再入栈
    return true;
}


// 出栈
bool Pop(SqStack &S, int &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈已空" << std::endl;
        return false;
    }

    e = S.data[S.top--];  // 用 e 返回栈顶元素，再把指针减一
    return true;
}


// 读栈顶元素
bool GetTop(SqStack S, int &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top];  // 读栈顶元素
    return false;
}


// 使用顺序栈求斐波那契数列
int Fibonacci_byStack(int n) {
    // 先进行输入合法性判断
    if(n < 0) {
        std::cerr << "输入必须为非负整数" << std::endl;
        return -1;
    }

    // 处理基础情况
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;

    SqStack S;  // 声明一个顺序栈
    InitStack(S);  // 初始化顺序栈

    // 用数组存储斐波那契数列结果
    std::vector<int> fib(n + 1, -1);  // 数组大小未 n+1 ，所有元素初始化为 -1 ，表示未计算
    fib[0] = 0;  // 斐波那契数列的第 0 项是 0
    fib[1] = 1;  // 斐波那契数列的第 1 项是 1

    // 将初始值 n 入栈
    Push(S, n);

    while(!Empty(S)) {
        int e;  // 作为返回值
        Pop(S, e);  // 弹出栈顶元素

        // 如果 e 的值已经计算过，就跳过
        if(fib[e] != -1)
            continue;

        // 检查 e-1 和 e-2 是否已计算
        bool canCompute = true;  // 是否已计算的表示，初始化为 true
        if(e - 1 >= 0 && fib[e - 1] == -1) {
            canCompute = false;
            // 重新入栈，并压入 e-1
            Push(S, e);
            Push(S, e - 1);
        }
        if(e - 2 >= 0 && fib[e - 2] == -1) {
            canCompute = false;
            // 重新入栈，并压入 e-2
            Push(S, e);
            Push(S, e - 2);
        }

        // 如果 e-1 和 e-2 都已计算，则计算 e
        if(canCompute) {
            fib[e] = fib[e - 1] + fib[e - 2];
        }
    }
    return fib[n];
}


// 测试
int main() {
    int n = 4;

    // 递归算法求斐波那契数列
    int x = Fibonacci(n);
    std::cout << "递归算法求斐波那契数列: F(" << n << ") = " << x << std::endl;

    // 非递归算法求斐波那契数列
    int result = Fibonacci_byStack(n);
    if(result != -1) {
        std::cout << "非递归算法求斐波那契数列: F(" << n << ") = " << result << std::endl;
    }

    // 打印斐波那契数列前 n 项
    std::cout << "斐波那契数列前" << n << "项：";
    for(int i = 0; i <= n; i++) {
        std::cout << Fibonacci_byStack(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}
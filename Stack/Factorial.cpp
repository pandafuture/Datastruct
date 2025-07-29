// 用顺序栈实现非递归算法求阶乘


#include <iostream>


// 递归算法求阶乘
int factorial(int n) {
    if(n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}


int main() {
    // 使用递归算法求阶乘
    int x = factorial(5);
    std::cout << "使用递归算法求阶乘：" << x << std::endl;
    return 0;
}
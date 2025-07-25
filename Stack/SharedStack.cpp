#include <iostream>

#define MAX_SIZE 100  // 共享栈的总容量


// 共享栈结构体
struct SharedStack {
    int data[MAX_SIZE];  // 存储栈元素的数组
    int top1;  // 栈1 的栈顶“指针”
    int top2;  // 栈2 的栈顶“指针”
};


// 初始化共享栈
void InitSharedStack(SharedStack &S) {
    S.top1 = -1;  // 栈1 初始化为空（从数组左端开始）
    S.top2 = MAX_SIZE;  // 栈2 初始化为空（从数组右端开始）
}


// 判空
bool Empty1(SharedStack S) {
    return S.top1 == -1;  // 直接返回栈1的栈顶指针是否为 -1
}


bool Empty2(SharedStack S) {
    return S.top2 == MAX_SIZE;  // 直接返回栈2的栈顶指针是否为初始值
}


// 判满
bool Full(SharedStack S) {
    return S.top1 + 1 == S.top2;  // 两个栈顶相邻表示栈满
}


// 入栈
bool Push1(SharedStack &S, int e) {
    // 先判断栈是否已满
    if(Full(S)) {
        std::cout << "栈已满";
        return false;
    }

    S.data[++S.top1] = e;  // 栈1 栈顶“指针”先加一，再入栈
    return true;
}


bool Push2(SharedStack &S, int e) {
    // 先判断栈是否已满
    if(Full(S)) {
        std::cout << "栈已满";
        return false;
    }

    S.data[--S.top2] = e;  // 栈2 栈顶“指针”先减一，在入栈
    return true;
}


// 出栈
bool Pop1(SharedStack &S, int &e) {
    // 先判断栈1是否为空
    if(Empty1(S)) {
        std::cout << "栈1为空";
        return false;
    }

    e = S.data[S.top1--];  // 读取栈顶元素值，再把栈1栈顶“指针”减一
    return true;
}


bool Pop2(SharedStack &S, int &e) {
    // 先判断栈2是否为空
    if(Empty2(S)) {
        std::cout << "栈2为空";
        return false;
    }

    e = S.data[S.top2++];  // 读取栈2栈顶元素值，再把栈2栈顶“指针”加一
    return true;
}


// 读栈顶元素
bool GetTop1(SharedStack S, int &e) {
    // 先判断栈1是否为空
    if(Empty1(S)) {
        std::cout << "栈1为空";
        return false;
    }

    e = S.data[S.top1];  // 读取栈1的栈顶元素
    return true;
}


bool GetTop2(SharedStack S, int &e) {
    // 先判断栈2是否为空
    if(Empty2(S)) {
        std::cout << "栈2为空";
        return false;
    }

    e = S.data[S.top2];  // 读取栈2的栈顶元素
    return true;
}


// 输出栈
void PrintSharedStack(SharedStack S) {
    std::cout << "输出栈1: ";
    // 先判断栈 1 是否为空
    if(Empty1(S)) {
        std::cout << "栈1为空";
    }
    else {
        // 不为空，则从栈1的栈顶开始遍历整个栈1，同时输出元素
        for (int i = S.top1; i >= 0; i--) {
            std::cout << S.data[i] << " ";
        }
    }
    std::cout << std::endl;

    std::cout << "输出栈2: ";
    // 先判断栈2 是否为空
    if(Empty2(S)) {
        std::cout << "栈2为空";
    }
    else {
        // 不为空，则从栈2的栈顶开始遍历整个栈2，同时输出元素
        for (int i = S.top2; i < MAX_SIZE; i++) {
            std::cout << S.data[i] << " ";
        }
    }
    std::cout << std::endl;
}


// 求栈长
int Length1(SharedStack S) {
    return S.top1 + 1;
}


int Length2(SharedStack S) {
    return MAX_SIZE - S.top2;
}


// 销毁栈
void DestroySharedStack(SharedStack &S) {
    S.top1 = -1;  // 重置栈1
    S.top2 = MAX_SIZE;  // 重置栈2
}


// 测试
int main() {
    SharedStack S;  // 声明一个共享栈
    int e;  // 作为返回值

    InitSharedStack(S);  // 初始化共享栈

    std::cout << "栈1 判空：" << Empty1(S) << std::endl;  // 栈1 判空
    std::cout << "栈2 判空：" << Empty2(S) << std::endl;  // 栈2 判空

    std::cout << "栈1 栈长：" << Length1(S) << std::endl;  // 栈1 栈长
    std::cout << "栈2 栈长：" << Length2(S) << std::endl;  // 栈2 栈长


    Push1(S, 1);  // 元素1 入 栈1
    Push1(S, 2);
    Push1(S, 3);
    PrintSharedStack(S);  // 输出栈

    Push2(S, 4);  // 元素1 入 栈2
    Push2(S, 5);
    Push2(S, 6);
    PrintSharedStack(S);  // 输出栈

    // 读 栈1 的栈顶元素
    if(GetTop1(S, e)) {
        std::cout << "栈1 的栈顶元素：" << e << std::endl;
    }

    // 读 栈2 的栈顶元素
    if(GetTop2(S, e)) {
        std::cout << "栈2 的栈顶元素: " << e  << std::endl;
    }


    Pop1(S, e);  // 栈1 的栈顶元素出栈
    std::cout << "栈1 出栈：" << e << std::endl;
    PrintSharedStack(S);  // 输出栈

    Pop2(S, e);  // 栈2 的栈顶元素出栈
    std::cout << "栈2 出栈：" << e << std::endl;
    PrintSharedStack(S);  // 输出栈


    std::cout << "栈1 判空：" << Empty1(S) << std::endl;  // 栈1 判空
    std::cout << "栈2 判空：" << Empty2(S) << std::endl;  // 栈2 判空

    std::cout << "栈1 栈长：" << Length1(S) << std::endl;  // 栈1 栈长
    std::cout << "栈2 栈长：" << Length2(S) << std::endl;  // 栈2 栈长

    
    DestroySharedStack(S);  // 销毁操作
}
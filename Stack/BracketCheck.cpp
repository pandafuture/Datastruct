// 栈在括号匹配中的应用


#include <iostream>


#define MAX_SIZE 100  // 定义顺序栈的最大容量


// 顺序栈结构体
struct SqStack {
    char data[MAX_SIZE];  // 静态数组存放栈中元素
    int top;  // 栈顶“指针”，指向栈顶元素的数组下标
};


// 初始化栈
void InitStack(SqStack &S) {
    S.top = -1;  // 栈顶“指针”初始化为 -1，表示空栈
}


// 判空
bool Empty(SqStack S) {
    return S.top == -1;  // 直接返回栈顶“指针”是否为空
}


// 判满
bool Full(SqStack S) {
    return S.top == MAX_SIZE - 1;  // 直接返回栈顶指针是否为最大表长 - 1
}


// 入栈
bool Push(SqStack &S, char e) {
    // 先判断栈是否已满
    if(Full(S)) {
        std::cout << "栈已满" << std::endl;
        return false;
    }

    S.data[++S.top] = e;  // 栈顶指针加一，然后入栈
    return true;
}


// 出栈
bool Pop(SqStack &S, char &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top--];  // 读出栈顶元素的值，然后指针减一
    return true;
}


// 括号匹配算法
bool bracketCheck(char str[], int length) {
    SqStack S;  // 声明一个栈
    
    InitStack(S);  // 初始化栈

    // 遍历每个字符，把左括号入栈，如果是右括号就查看是否匹配
    for(int i=0; i < length; i++) {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{') {
            if(Full(S)) {
                std::cout << "栈已满" << std::endl;
                return false;
            }
            Push(S, str[i]);
        }
        else {
            // 如果扫描到的是右括号，且当前栈为空，则匹配失败
            if(Empty(S)) {
                std::cout << "匹配失败";
                return false;
            }

            char topChar;  // 栈顶元素
            Pop(S, topChar);  // 弹出栈顶元素
            // 进行括号匹配
            if(str[i] == ')' && topChar != '(') {
                std::cout << "匹配失败";
                return false;
            }
            if(str[i] == ']' && topChar != '[') {
                std::cout << "匹配失败";
                return false;
            }
            if(str[i] == '}' && topChar != '{') {
                std::cout << "匹配失败";
                return false;
            }
        }
    }

    return Empty(S);  // 检查栈是否为空，栈空说明匹配成功
}


// 测试
int main() {
    char bracket1[] = "([{}])";  // 匹配成功，长度：6
    char bracket2[] = "([)]";  // 匹配失败，长度：4

    if(bracketCheck(bracket1, 6)) {  // 进行括号匹配
        std::cout << "匹配成功";
    }
}
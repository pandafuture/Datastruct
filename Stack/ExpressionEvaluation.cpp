// 中缀表达式求值


#include <iostream>


#define MAX_SIZE 100  // 定义顺序栈最大容量


// 定义操作数栈结构体（存储整数）
struct NumStack {
    int data[MAX_SIZE];  // 存储操作数的数组
    int top;  // 栈顶指针
};


// 定义运算符栈结构体（存储字符）
struct OpStack {
    char data[MAX_SIZE];  // 存储运算符的数组
    int top;  // 栈顶指针
};


// 初始化操作数栈
void InitNumStack(NumStack &S) {
    S.top = -1;  // 栈顶指针初始化为 -1 ，表示空栈
}


// 初始化运算符栈
void InitOpStack(OpStack &S) {
    S.top = -1;  // 栈顶指针初始化为 -1 ，表示空栈
}


// 判空操作数栈
bool EmptyNumStack(NumStack S) {
    return S.top == -1;  // 看栈顶指针是否等于 -1
}


// 判空运算符栈
bool EmptyOpStack(OpStack S) {
    return S.top == -1;  // 看栈顶指针是否等于 -1
}


// 判满操作数栈
bool FullNumStack(NumStack S) {
    return S.top == MAX_SIZE - 1;  // 看栈顶指针是否指向最大容量减一
}


// 判满运算符栈
bool FullOpStack(OpStack S) {
    return S.top == MAX_SIZE - 1;  // 看栈顶指针是否指向最大容量减一
}


// 操作数入栈
bool PushNum(NumStack &S, int e) {
    // 先判断栈是否已满
    if(EmptyNumStack(S)) {
        std::cout << "操作数栈已满" << std::endl;
        return false;
    }

    S.data[++S.top] = e;  // 栈顶指针先加一，再入栈
    return true;
}


// 运算符入栈
bool PushOp(OpStack &S, char e) {
    // 先判断栈是否已满
    if(EmptyOpStack(S)) {
        std::cout << "运算符栈已满" << std::endl;
        return false;
    }

    S.data[++S.top];  // 栈顶指针先加一，再入栈
    return true;
}


// 操作数出栈
bool PopNum(NumStack &S, int &e) {
    // 先判断操作数栈是否为空
    if(EmptyNumStack(S)) {
        std::cout << "操作数栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top--];  // 先出栈，再把栈顶指针减一
    return true;
}


// 运算符出栈
bool PopOp(OpStack &S, char &e) {
    // 先判断操作数栈是否为空
    if(EmptyOpStack(S)) {
        std::cout << "操作数栈为空" <<std::endl;
        return false;
    }

    e = S.data[S.top--];  // 先出栈，再把栈顶指针减一
    return true;
}


// 读操作数栈栈顶元素
bool GetTopNum(NumStack S, int &e) {
    // 先判断操作数栈是否为空
    if(EmptyNumStack(S)) {
        std::cout << "操作数栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top];  // 用 e 返回栈顶元素值
    return true;
}


// 读运算符栈栈顶元素
bool GetTopOp(OpStack S, char &e) {
    // 先判断操作符栈是否为空
    if(EmptyOpStack(S)) {
        std::cout << "操作符栈为空" <<std::endl;
        return false;
    }

    e = S.data[S.top];  // 用 e 返回栈顶元素值
    return true;
}


// 获取运算符优先级
int GetPriority(char op) {
    // 加号和减号优先级为 1
    if(op == '+' ||op == '-')
        return 1;

    // 乘号和除号优先级为 2
    if(op == '*' ||op == '/')
        return 2;

    // 其它符号优先级为 0
    return 0;
}


// 执行运算
int calculate(int a, int b, char op) {
    switch(op) {
        // 如果是加号，就执行加法运算
        case '+': return a + b;
        // 如果是减号，就执行减法运算
        case '-': return a - b;
        // 如果是乘号，就执行乘法运算
        case '*': return a * b;
        // 如果是除号，就先判断被除数是否为 0 ，不为 0 就执行除法运算
        case '/':
            if(b == 0) {
                // std::cerr 专用于错误信息
                std::cerr << "错误：被除数不能为 0" << std::endl;
                // 立即终止程序执行
                exit(EXIT_FAILURE);
            }
            return a / b;
        // 如果是其他操作符，就
        default:
            std::cerr << "错误：非法操作符" << std::endl;
            exit(EXIT_FAILURE);
    }
}


// 中缀表达式求值函数
int EvaluateExpression(std::string &expr) {
    NumStack numStack;  // 声明操作数栈
    OpStack opStack;  // 声明运算符栈

    InitNumStack(numStack);  // 初始化操作符栈
    InitOpStack(opStack);  // 初始化操作符栈

    int i = 0;  // 作为计数器
    int length = expr.length();  // 获取字符串长度

    while(i < length) {
        // 跳过空格
        if(expr[i] == ' ') {
            i++;
            continue;
        }

        // 处理操作数
        if(std::isdigit(expr[i])) {
            int num = 0;  // 用来存储转换后的整数
            // 循环处理多位数字的情况
            while(i < length && std::isdigit(expr[i])) {
                /*
                 先将已解析的数字左移一位
                 然后通过 ASCII 码值将后面的数字字符转为对应的整数值
                 最后构建完整的多位数整数
                 */
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            PushNum(numStack, num);  // 将操作数压入栈中
        }
        // 处理左括号
        else if(expr[i] == '(') {
            // 如果遇到左括号，就把左括号压入运算符栈中
            PushOp(opStack, expr[i]);
            i++;
        }
        // 处理右括号
        else if(expr[i] == ')') {
            // 如果遇到右括号，就计算括号内的表达式
            char op;
            while(GetTopOp(opStack, op) && op != '(') {
                PopOp(opStack, op);  // 弹出运算符栈栈顶
            }
        }
    }
}
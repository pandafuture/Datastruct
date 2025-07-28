// 后缀表达式求值


#include <iostream>
#include <sstream>


#define MAX_SIZE 100  // 定义顺序栈最大容量


// 顺序栈结构体，用来存放操作数
struct NumStack {
    double data[MAX_SIZE];  // 存储操作数的数组
    int top;  // 栈顶指针
};


// 初始化
void InitStack(NumStack &S) {
    S.top = -1;  // 栈顶指针初始化为 -1，表示空栈
}


// 判空
bool Empty(NumStack S) {
    return S.top == -1;
}


// 判满
bool Full(NumStack S) {
    return S.top == MAX_SIZE - 1;
}


// 操作数入栈
bool PushNum(NumStack &S, double e) {
    // 先判断栈是否已满
    if(Full(S)) {
        std::cout << "操作数栈已满" << std::endl;
        return false;
    }

    S.data[++S.top] = e;  // 先把指针加一，再入栈
    return true;
}


// 操作数出栈
bool PopNum(NumStack &S, double &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "操作数栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top--];  // 先出栈，再把指针减一
    return true;
}


// 执行运算
double calculate(double a, double b, char op) {
    switch(op) {
        // 如果是加号，就执行加法操作
        case '+': return a + b;

        // 如果是减号，就执行减法操作
        case '-': return a - b;

        // 如果是乘号，就执行乘法操作
        case '*': return a * b;

        // 如果是除号，就执行除法操作。注意被除数不能为 0
        case '/':
            if(b == 0) {
                std::cerr << "错误：被除数不能为 0" << std::endl;
                exit(EXIT_FAILURE);
            }
            return a / b;
        // 如果是其他操作符，则返回错误提示
        default:
            std::cerr << "错误：非法操作符" << std::endl;
            exit(EXIT_FAILURE);
    }
}


// 后缀表达式求值算法
double EvaluationPostfix(const std::string &postfix) {
    NumStack S;  // 声明一个顺序栈
    InitStack(S);  // 初始化栈


    // 创建一个字符串输入流对象 iss ，把 postfix 字符串包装成输入流，允许使用 ">>" 来按空格分割字符串
    // 需要引用 <sstream> 头文件
    std::istringstream iss(postfix);
    // 声明一个字符串变量，用于存储从输入流中提取的每个元素
    std::string token;

    while(iss >> token) {
        // 如果是操作数
        if(isdigit(token[0])) {
            try {
                // 用 std::stod 将字符串转换成双精度浮点数
                double num = std::stod(token);
                PushNum(S, num);
            }
            catch(...) {
                // 捕获任何类型的异常
                // 任何创建一个新的 std::runtime_error 类型的异常，包含错误信息
                // 抛出这个异常
                throw std::runtime_error("错误：无效的操作数 " + token);
            }
        }
        // 如果是运算符
        else {
            double b, a;  // 存储操作数
            // 先弹出操作数 b
            if(!PopNum(S, b)) {
                // 抛出异常
                throw std::runtime_error("错误：缺少操作数");
            }
            // 再弹出操作数 a
            if(!PopNum(S, a)) {
                // 抛出异常
                throw std::runtime_error("错误：缺少操作数");
            }

            try {
                // 进行相应计算
                double result = calculate(a, b, token[0]);
                // 把计算结果压入栈中
                PushNum(S, result);
            }
            catch(const std::runtime_error& e) {
                throw;  // 重新抛出异常
            }
        }
    }

    // 检查最终栈中的元素数量
    if(S.top != 0) {
        throw std::runtime_error("错误：表达式不完整");
    }

    double finalResult;  // 存储最终计算结果
    PopNum(S, finalResult);  // 把最终结果弹出，用 finalResult 返回
    return finalResult;  // 返回最终结果
}


// 测试
int main() {
    std::string expression = "3 4 +";
    std::cout << "后缀表达式为：" << expression << std::endl;
    std::cout << expression << " = " << EvaluationPostfix(expression) << std::endl;

    return 0;
}
// 中缀表达式转后缀表达式


#include <iostream>


#define MAX_SIZE 100  // 顺序栈的最大容量


// 顺序栈结构体（字符类型）
// 用于保存暂时还不能确定运算顺序的运算符
struct CharStack {
    char data[MAX_SIZE];  // 存储字符的数组
    int top;  // 栈顶指针
};


// 初始化栈
void InitStack(CharStack &S) {
    S.top = -1;  // 把栈顶指针初始化为 -1 ，表示空栈
}


// 判空
bool Empty(CharStack S) {
    return S.top == -1;  // 看栈顶指针是否指向 -1
}


// 判满
bool Full(CharStack S) {
    return S.top == MAX_SIZE - 1;
}


// 入栈
bool Push(CharStack &S, char e) {
    // 先判断栈是否已满
    if(Full(S)) {
        std::cout << "栈已满" << std::endl;
        return false;
    }

    S.data[++S.top] = e;  // 先把栈顶指针加一，在入栈
    return true;
}


// 出栈
bool Pop(CharStack &S, char &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top--];  // 先出栈，然后把栈顶指针减一
    return true;
}


// 读栈顶元素
bool GetTop(CharStack S, char &e) {
    // 先判断栈是否为空
    if(Empty(S)) {
        std::cout << "栈为空" << std::endl;
        return false;
    }

    e = S.data[S.top];  // 用 e 返回栈顶元素
    return true;
}


// 获取运算符优先级
int GetPriority(char op) {
    // 加号和减号的优先级为 1
    if(op == '+' || op == '-')
        return 1;
    
    // 乘号和除号优先级为 2
    if(op == '*' || op == '/')
        return 2;

    // 其他运算符优先级为 0
    return 0;
}


// 中缀表达式转后缀表达式
std::string InfixToPostfix(const std::string &infix) {
    CharStack S;  // 声明一个栈
    InitStack(S);  // 初始化栈
    std::string postfix = "";  // 用来存储转换后的后缀表达式

    for(int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // 跳过空格
        if(c == ' ') 
            continue;

        // 处理操作数（包括多位数）
        if(std::isdigit(c)) {
            // 提取整个数字
            while(i < infix.length() && (std::isdigit(infix[i]) || infix[i] == '.')) {
                postfix += infix[i++];  // 将当前字符添加到后缀表达式
            }
            postfix += ' ';  // 数字后面加空格分割
            i--;  // 回退一个字符，否则循环结束时，i 指向的是数字后的第一个非数字字符
            continue;
        }

        // 处理左括号
        if(c == '(') {
            Push(S, c);  // 把左括号入栈
            continue;
        }

        // 处理右括号
        if(c == ')') {
            char topChar;  // 用于返回栈顶元素

            // 遇到 ')' 则一次弹出栈内运算符并加入后缀表达式，直到弹出 '(' 为止
            while(GetTop(S, topChar) && topChar != '(') {
                Pop(S, topChar);
                postfix += topChar;
                postfix += ' ';
            }
            Pop(S, topChar);  // 弹出左括号
            continue;
        }

        // 处理运算符
        char topChar;  // 用于返回栈顶元素

        // 依次弹出栈中优先级高于或等于当前运算符的所有运算符，并加入后缀表达式
        // 若碰到 '(' 或栈空则停止
        while(GetTop(S, topChar) && topChar != '(' && GetPriority(c) <= GetPriority(topChar)) {
            Pop(S, topChar);
            postfix += topChar;
            postfix += ' ';
        }
        Push(S, c);  // 最后把当前运算符入栈
    }

    // 弹出栈中剩余运算符
    char topChar;
    while(Pop(S, topChar)) {
        postfix += topChar;  // 把剩余运算符加入到后缀表达式中
        postfix += ' ';  // 每个运算符后加空格
    }

    // 删除最后一空格（如果有）
    if(!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;  // 返回最终的后缀表达式
}


// 测试
int main() {
    std::string expression = "3 + 4 * 2 / (1 - 5)";  // 中缀表达式
    std::string postfix = InfixToPostfix(expression);  // 中缀转后缀

    std::cout << "中缀表达式：" << expression << std::endl;
    std::cout << "后缀表达式：" << postfix << std::endl;

    return 0;
}
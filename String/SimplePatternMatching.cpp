// 朴素（简单）模式匹配算法


#include <iostream>
#include <cstring>


#define MAX_SIZE 50  // 定义串的最大长度


// 串的定长顺序存储结构
struct SqString {
    char ch[MAX_SIZE];
    int length;
};


// 初始化串
void InitString(SqString &S) {
    S.length = 0;
}


// 赋值操作
bool StrAssign(SqString &S, const char *chars) {
    // 获取字符数组长
    int len = strlen(chars);

    // 判断字符数组长是否超过最大串长
    if(len > MAX_SIZE - 1) {
        std::cerr << "错误：超过最大串长度" << std::endl;
        return false;
    }

    // 开始赋值
    for(int i = 0; i < len; i++) {
        S.ch[i + 1] = chars[i];
    }

    S.length = len;

    return true;
}


// 判空操作
bool StrEmpty(SqString S) {
    return S.length == 0;
}


// 打印操作
void PrintString(SqString S) {
    // 先判断串是否为空
    if(StrEmpty(S)) {
        std::cout << "串为空" << std::endl;
        return;
    }

    // 打印串内容
    for(int i = 1; i <= S.length; i++) {
        std::cout << S.ch[i];
    }
    std::cout << std::endl;
}


// 朴素模式匹配算法
int Index(const SqString &S, const SqString &T) {
    int i = 1;  // 记录当前比较到 串S 的第几个字符
    int j = 1;  // 记录当前匹配到 串T 的第几个字符
    while(i <= S.length && j <= T.length) {
        if(S.ch[i] == T.ch[j]) {
            // 如果当前字符相同，就比较后继字符
            ++i;
            ++j;
        }
        else {
            // 指针后退重新开始匹配
            i = i - j + 2;
            j = 1;
        }
    }
    // 当前 串T 所有字符都匹配成功，就返回在 串S 中的起始位置
    if(j > T.length)
        return i - T.length;
    else
        return 0;
}


// 测试
int main() {
    // 声明串
    SqString S;  // 主串
    SqString T;  // 模式串

    // 初始化串
    InitString(S);
    InitString(T);

    // 赋值操作
    StrAssign(S, "Simple Pattern Matching");
    StrAssign(T, "Matching");

    // 进行朴素模式匹配
    std::cout << "T 在 S 中的朴素模式匹配：" << Index(S, T) << std::endl;
}
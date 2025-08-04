// 串的模式匹配算法 -- KMP 算法


#include <iostream>
#include <cstring>


#define MAX_SIZE 20 // 定义顺序串的最大长度


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


// 求 next 数组
void get_next(const SqString &T, int next[]) {
    int i = 1;  // 主串指针
    int j = 0;  // 模式串指针
    next[1] = 0;  // next[1] 固定为 0

    while(i < T.length) {
        if(j == 0 || T.ch[i] == T.ch[j]) {
            // j 已回溯到起点或匹配成功
            i++;
            j++;
            next[i] = j;  // 设置当前位置的 next 值
        }
        else
            j = next[j];  // 匹配失败，j 回溯
    }
}


// 求 nextval 数组
void get_nextval(const SqString &T, int nextval[]) {
    int i = 1;  // 主串指针
    int j = 0;  // 模式串指针
    nextval[1] = 0;  // nextval[1] 固定为 0

    while(i < T.length) {
        if(j == 0 || T.ch[i] == T.ch[j]) {
            i++;
            j++;
            if(T.ch[i] != T.ch[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}


// KMP 算法
int Index_KMP(const SqString &S, const SqString &T, const int next[]) {
    int i = 1;  // 主串指针
    int j = 1;  // 模式串指针
    while(i <= S.length && j <= T.length) {
        if(j == 0 || S.ch[i] == T.ch[j]) {
            // 匹配成功或 j 已回溯到起点
            i++;
            j++;
        }
        else
            j = next[j];  // 模式串向右移动
    }
    if(j > T.length)
        return i - T.length;  // 匹配成功
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
    StrAssign(S, "ababcabcacbab");
    StrAssign(T, "abcac");

    // 计算 next 数组
    int next[MAX_SIZE];
    get_next(T, next);

    // 打印 next 数组
    std::cout << "next 数组为：";
    for(int i = 1; i <= T.length; i++) {
        std::cout << next[i] << " ";
    }
    std::cout << std::endl;

    // 执行 KMP　模式匹配
    int pos = Index_KMP(S, T, next);
    if(pos > 0) {
        std::cout << "匹配成功：模式串在主串中的起始位置：" << pos <<std::endl;
    }
    else {
        std::cout << "匹配失败" << std::endl;
    }

    // 计算 nextval 数组
    int nextval[MAX_SIZE];
    get_nextval(T, nextval);

    // 打印 nextval 数组
    std::cout << "nextval 数组为：";
    for(int i = 1; i <= T.length; i++) {
        std::cout << nextval[i] << " ";
    }
    std::cout << std::endl;

    // 执行 KMP （优化后）模式匹配
    pos = Index_KMP(S, T, nextval);
    if(pos > 0) {
        std::cout << "匹配成功：模式串在主串中的起始位置：" << pos << std::endl;
    }
    else {
        std::cout << "匹配失败" << std::endl;
    }

    return 0;

}
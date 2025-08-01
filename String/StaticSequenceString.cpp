#include <iostream>
#include <cstring>


#define MAX_SIZE 255  // 预定义最大串长为 255


// 串的顺序存储结构（使用静态数组实现）
struct SqString {
    char ch[MAX_SIZE];  // 存储串字符的数组，每个分量存储一个字符（ch[0] 不使用）
    int length;  // 串的实际长度（从 1 开始存储）
};


// 初始化串（创建空串）
void InitString(SqString &S) {
    S.length = 0;  // 长度设为 0，表示空串
}


// 赋值操作（把串 S 赋值为 chars）
bool StrAssign(SqString &S, const char *chars) {
    int len = strlen(chars);  // 计算输入字符数组的长度
    // 检查输入长度是否超过最大容量（实际可用长度为 MAX_SIZE-1）
    if(len > MAX_SIZE - 1) {
        std::cerr << "错误：超过最大串长度" << std::endl;
        return false;
    }

    // 开始赋值（从 char[1] 开始存放）
    for(int i = 0; i < len; i++) {
        S.ch[i + 1] = chars[i];  // 第几个位序的字符就放在数组中的第几个下标位置
    }
    S.length = len;  // 更新串长度
    return true;
}


// 复制操作（把串 T 复制给串 S）
bool StrCopy(SqString &S, const SqString T) {
    // 检查源串是否为空
    if(T.length == 0) {
        // 如果为空，就只要把目标串初始化为空就行
        InitString(S);
        return true;
    }

    // 开始复制内容（从 char[1] 开始）
    for(int i = 1; i <= T.length; i++) {
        S.ch[i] = T.ch[i];  // 逐字符复制
    }
    S.length = T.length;  // 更新串长度
    return true;
}


// 判空操作
bool StrEmpty(SqString S) {
    return S.length == 0;  // 长度为 0 即为空串
}


// 比较操作（若 S > T，则返回值大于 0；若 S = T，则返回值等于 0；若 S < T，则返回值小于 0）
int StrCompare(SqString S, SqString T) {
    // 逐字符比较（从下标 1 开始）
    for(int i = 1; i <= (S.length < T.length ? S.length : T.length); i++) {
        if(S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];  // 返回第一个不同字符的差值
    }
    return S.length - T.length;  // 所有字符都相同，则比较长度
}


// 求串长
int StrLength(SqString S) {
    return S.length;  // 直接返回长度
}


// 求子串（用 Sub 返回 串S 的第 pos 个字符起长度为 len 的子串）
bool SubString(SqString &Sub, SqString S, int pos, int len) {
    // 检查位置和子串长度是否越界
    if(pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length) {
        std::cerr << "错误：非法位置或长度" << std::endl;
        return false;
    }

    // 截取子串内容
    for(int i = 1; i <= len; i++) {
        Sub.ch[i] = S.ch[pos + i - 1];
    }
    Sub.length = len;
    return true;
}


// 串联接（将 串S1 和 串S2 联接成新串T）
bool Concat(SqString &T, SqString S1, SqString S2) {
    // 检查总长度是否超过最大长度
    if(S1.length + S2.length >  MAX_SIZE - 1) {
        std::cerr << "错误：联接后串超过最大长度" << std::endl;
        return false;
    }

    // 复制第一个串的内容
    for(int i = 1; i <= S1.length; i++) {
        T.ch[i] = S1.ch[i];
    }

    // 复制第二个串的内容（接在第一个串后面）
    for(int i = 1; i <= S2.length; i++) {
        T.ch[S1.length + i] = S2.ch[i];
    }

    T.length = S1.length + S2.length;  // 更新串长度
    return true;
}


// 定位操作（若 主串S 中存在与 串T 值相同的子串，则返回它在主串S中第一次出现的位置；否则返回 0）
int Index(SqString S, SqString T) {
    // 空串是任意串的子串
    if(T.length == 0)
        return 0;

    int n = StrLength(S);  // 获取 串S 的长度
    int m = StrLength(T);  // 获取 串T 的长度
        
    int i = 1;
    SqString sub;  // 用于暂存子串
    // 从 串S 的第一个字符开始获取长度为 m 的子串，并暂存在 串sub 中
    while(i <= n - m + 1) {
        SubString(sub, S, i, m);  // 获取子串
        if(StrCompare(sub, T) != 0)  // 进行比较
            ++i;
        else return i;  // 返回子串在主串中的位置
    }
    return 0;  // 如果没找到就返回 0
}


// 清空操作
void ClearString(SqString &S) {
    S.length = 0;  // 长度重置为 0，即为空串
}


// 销毁串
void DestroyString(SqString &S) {
    // 静态数组无需释放内存，等同于清空
    ClearString(S);
}


// 打印串内容
void PrintString(SqString S) {
    // 先判断串是否为空
    if(StrEmpty(S)) {
        std::cout << "串为空" << std::endl;
        return;
    }

    // 打印串内容（从下标1开始打印）
    for(int i = 1; i <= S.length; i++) {
        std::cout << S.ch[i];
    }
    std::cout << std::endl;
}


// 测试
int main() {
    // 声明静态顺序串
    SqString S1;
    SqString S2;
    SqString S3;
    SqString S4;
    SqString S5;
    SqString S6;

    // 初始化
    InitString(S1);
    InitString(S2);
    InitString(S3);
    InitString(S4);
    InitString(S5);
    InitString(S6);

    // 赋值操作
    StrAssign(S1, "Hello");
    StrAssign(S4, "Hello World!");

    // 复制操作（把 串S1 赋值给 串S2）
    StrCopy(S2, S1);

    // 判空操作
    std::cout << "S1 判空：" << StrEmpty(S1) << std::endl;
    std::cout << "S2 判空：" << StrEmpty(S2) << std::endl;
    std::cout << "S3 判空：" << StrEmpty(S3) << std::endl;

    // 比较操作
    std::cout << "S1 与 S2 比较: " << StrCompare(S1, S4) << std::endl;

    // 求串长
    std::cout << "S1 的串长为：" << StrLength(S1) << std::endl;
    std::cout << "S2 的串长为：" << StrLength(S2) << std::endl;
    std::cout << "S3 的串长为：" << StrLength(S3) << std::endl;
    std::cout << "S4 的串长为：" << StrLength(S4) << std::endl;

    // 求子串
    SubString(S5, S4, 7, 5);

    // 串联接（把 串S1 和 串S4 联接为 串S6）
    Concat(S6, S1, S4);

    // 定位操作
    std::cout << "S1 在 S4 中的定位为：" << Index(S4, S1) << std::endl;

    // 清空操作
    ClearString(S1);
    std::cout << "S1 判空：" << StrEmpty(S1) << std::endl;

    // 销毁串
    DestroyString(S2);
    std::cout << "S2 判空：" << StrEmpty(S2) << std::endl;

    // 打印串
    PrintString(S4);

    return 0;
}
#include <iostream>
#include <cstring>
#include <cstdlib>  // 包含 malloc 和 free 函数


// 串的堆分配存储结构（动态分配实现）
struct HString {
    char *ch;  // 按串长分配存储区，ch 指向串的基地址
    int length;  // 串的长度
    int capacity;  // 当前分配的存储区长度
};


// 初始化串（创建空串）
void InitString(HString &S) {
    S.capacity = 10;  // 初始容量设为 10
    // 分配 capacity + 1（因为 char[0] 不使用）个大小为 char 的内存空间，并用 char 类型的指针返回地址
    S.ch = (char*)malloc((S.capacity + 1) * sizeof(char));

    // 如果内存分配失败，则退出程序
    if(!S.ch) {
        std::cerr << "内存分配失败" << std::endl;
        exit(1);
    }

    // 初始长度设为 0
    S.length = 0;
}


// 赋值操作（把 chars 赋值给 串S）
bool StrAssign(HString &S, const char *chars) {
    // 计算输入字符数组的长度
    int len = strlen(chars);

    // 检查是否需要扩容
    if(len > S.capacity) {
        // 用 realloc 重新分配已申请的内存块大小（传入原指针，总字节数）
        char* new_ch = (char*)realloc(S.ch,(len + 1) * sizeof(char));
        // 如果重新分配失败，则退出
        if(!new_ch) {
            std::cerr << "内存分配失败" << std::endl;
            return false;
        }
        S.ch = new_ch;  // 更新基地址
        S.capacity = len;  // 更新容量
    }

    // 从 ch[1] 开始存储字符
    for(int i = 0; i < len; i++) {
        S.ch[i + 1] = chars[i];
    }
    S.length = len;  // 更新串的长度
    return true;
}


// 复制操作（把串T复制给串S）
bool StrCopy(HString &S, const HString &T) {
    // 检查源串是否为空
    if(T.length == 0) {
        S.length = 0;  // 目标串也设为空串
        return true;
    }

    // 检查是否需要扩容
    if(T.length > S.capacity) {
        char* new_ch = (char*)realloc(S.ch,(T.length + 1) * sizeof(char));
        if(!new_ch) {
            std::cerr << "内存分配失败" << std::endl;
            return false;
        }
        S.ch = new_ch;  // 更新存储区指针
        S.capacity = T.length;  // 更新存储区容量
    }

    // 从 char[1] 开始复制内容
    for(int i = 1; i <= T.length; i++) {
        S.ch[i] = T.ch[i];
    }
    S.length = T.length;  // 更新串长度
    return true;
}


// 判空操作
bool StrEmpty(const HString &S) {
    return S.length == 0;
}


// 比较操作
int StrCompare(const HString &S, const HString &T) {
    // 逐字符比较（从数组下标 1 开始）
    for(int i = 1; i <= (S.length < T.length ? S.length : T.length); i++) {
        if(S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];  // 返回第一个不同字符的差值
    }
    return S.length - T.length;  // 所有字符都相同则比较长度
}


// 求串长
int StrLength(const HString &S) {
    return S.length;
}


// 求子串（用 Sub 返回 串S 的第 pos 个字符起长度为 len 的子串）
bool SubString(HString &Sub, const HString &S, int pos, int len) {
    // 检查位置和长度合法性
    if(pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length) {
        std::cerr << "错误：非法位置或长度" << std::endl;
        return false;
    }

    // 确保 Sub 有足够容量
    if(len > Sub.capacity) {
        char* new_ch = (char*)realloc(Sub.ch, (len + 1) * sizeof(char));
        if(!new_ch) {
            std::cerr << "内存分配失败" << std::endl;
            return false;
        }
        Sub.ch = new_ch;
        Sub.capacity = len;
    }

    // 复制子串内容
    for(int i = 1; i <= len; i++) {
        Sub.ch[i] = S.ch[pos + i - 1];
    }
    Sub.length = len;  // 更新串长
    return true;
}


// 串联接（将 串S1 和 串S2 联接成新串T）
bool Concat(HString &T, const HString &S1, const HString &S2) {
    // 计算总长度
    int totalLen = S1.length + S2.length;

    // 检查是否要扩容
    if(totalLen > T.capacity) {
        char* new_ch = (char*)realloc(T.ch, (totalLen + 1) * sizeof(char));
        if(!new_ch) {
            std::cerr << "内存分配失败" << std::endl;
            return false;
        }
        T.ch = new_ch;
        T.capacity = totalLen;
    }

    // 复制 S1 的内容
    for(int i = 1; i <= S1.length; i++) {
        T.ch[i] = S1.ch[i];
    }

    // 复制 S2 的内容
    for(int i = 1; i <= S2.length; i++) {
        T.ch[S1.length + i] = S2.ch[i];
    }

    T.length = totalLen;  // 更新串长度
    return true;
}


// 定位操作（返回 子串T 在 主串S 中第一次出现的位置）
int Index(const HString &S, const HString &T) {
    // 空串是任意串的子串
    if(T.length == 0)
        return 0;

    int n = StrLength(S);  // 获取主串的长度
    int m = StrLength(T);  // 获取目标子串的长度
    int i = 1;
    HString sub;  // 用于暂存子串
    InitString(sub);  // 初始化
    while(i <= n - m + 1) {
        SubString(sub, S, i, m);  // 获取子串
        if(StrCompare(sub, T) != 0)  // 进行比较
            ++i;
        else
            return i;  // 如果匹配成功就返回子串在主串中的位置
    }
    return 0;
}


// 清空操作
void ClearString(HString &S) {
    S.length = 0;  // 长度重置为 0
}


// 销毁串
void DestroyString(HString &S) {
    free(S.ch);  // 释放动态分配的内存
    S.ch = nullptr;  // 指针置空
    S.length = 0;  // 长度归零
    S.capacity = 0;  // 容量归零
}


// 打印串内容
void PrintString(const HString &S) {
    // 先判断串是否为空
    if(StrEmpty(S)) {
        std::cout << "串为空" << std::endl;
        return;
    }

    // 开始打印
    for(int i = 1; i <= S.length; i++) {
        std::cout << S.ch[i];
    }
    std::cout << std::endl;
}


// 测试
int main() {
    // 声明动态顺序串
    HString S1;
    HString S2;
    HString S3;
    HString S4;
    HString S5;
    HString S6;

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

    // 复制操作
    StrCopy(S2, S1);  // 把 S1 复制给 S2

    // 判空操作
    std::cout << "S1 判空：" << StrEmpty(S1) << std::endl;
    std::cout << "S2 判空：" << StrEmpty(S2) << std::endl;
    std::cout << "S3 判空：" << StrEmpty(S3) << std::endl;

    // 比较操作
    std::cout << "S1 与 S4 比较：" << StrCompare(S1, S4) << std::endl;

    // 求串长
    std::cout << "S1 的串长：" << StrLength(S1) << std::endl;
    std::cout << "S2 的串长：" << StrLength(S2) << std::endl;
    std::cout << "S3 的串长: " << StrLength(S3) << std::endl;
    std::cout << "S4 的串长：" << StrLength(S4) << std::endl;

    // 求子串
    SubString(S5, S4, 7, 6);

    // 串联接
    Concat(S6, S1, S4);

    // 定位操作
    std::cout << "S1 在 S4 中的定位为：" << Index(S4, S1) << std::endl;

    // 清空操作
    ClearString(S2);
    std::cout << "S2 判空：" << StrEmpty(S2) << std::endl;

    // 销毁串
    DestroyString(S2);

    // 打印串内容
    std::cout << "打印 S1 : ";
    PrintString(S1);
    std::cout << "打印 S4 : ";
    PrintString(S4);

    return 0;
}
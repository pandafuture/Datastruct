#include <iostream>
#include <cstring>
#include <cstdlib>  // 包含 malloc 和 free 函数


// 串的堆分配存储结构（动态数组实现）
struct HString {
    char *ch;  // 按串长分配存储区，ch 指向串的基地址
    int length;  // 串的长度
    int capacity;  // 当前分配的存储区长度
};


// 初始化串（创建空串）
void InitString(HString &S) {
    
}
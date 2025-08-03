#include <iostream>
#include <cstring>


#define BLOCK_SIZE 4  // 定义块的大小（每个结点存储的字符数）


// 块链结点结构
struct Block {
    char ch[BLOCK_SIZE];  // 存储字符的数组
    Block *next;  // 指向下一个块的指针
};


// 串的块链存储结构
struct LString {
    Block *head;  // 指向第一个块的指针
    Block *tail;  // 指向最后一个块的指针
    int length;  // 串的实际长度（字符个数）
};


// 初始化串
void InitString(LString &S) {
    S.head = nullptr;  // 头指针置空
    S.tail = nullptr;  // 尾指针置空
    S.length = 0;  // 长度设为 0
}


// 赋值操作（把 chars 赋值给 串S）
bool StrAssign(LString &S, const char* chars) {
    // 先清空块链中所有内容
    Block *p = S.head;  // 新建一个指针，指向第一个块
    while(p) {
        Block *temp = p;  // 再新建一个指针，指向 指针p 指向的块
        p = p -> next;
        delete temp;  // 删除 temp 指向的块
    }

    // 重置链表状态
    S.head = nullptr;  // 重置头指针
    S.tail = nullptr;  // 重置尾指针
    S.length = 0;  // 重置串长

    // 如果是空串，现在就已完成操作，可直接返回
    int len = strlen(chars);  // 计算输入字符数组的长度
    if(len == 0) {
        return true;
    }

    // 计算需要的块数
    int blockCount = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // 处理每个块
    for(int i = 0; i < blockCount; i++) {
        Block* newBlock = new Block();  // 创建新块

        // 计算当前块应存储的字符数
        // 先判断当前块是否是最后一块
        // 如果不是，就说明当前块要存满
        // 如果是，那就再判断，当前块会不会被填满
        // 如果会被填满，就填满
        // 如果不会被填满，就计算需要填多少字符
        int charsInBlock = (i == blockCount - 1) ? (len % BLOCK_SIZE == 0 ? BLOCK_SIZE : len % BLOCK_SIZE) : BLOCK_SIZE;

        // 复制字符到当前块
        for(int j = 0; j < charsInBlock; j++) {
            newBlock -> ch[j] = chars[i * BLOCK_SIZE + j];
        }

        // 最后一个块占不满时，用特殊字符填充
        for(int j = charsInBlock; j < BLOCK_SIZE; j++) {
            newBlock -> ch[j] = '#';  // 填充字符
        }

        newBlock -> next = nullptr;  // 把新块的 next 指向空

        // 链接到链表
        if(!S.head) {
            S.head = newBlock;  // 如果当前链表中没有结点，就把新块作为第一个结点
            S.tail = newBlock;  // 更新尾指针
        }
        else {
            S.tail -> next = newBlock;  // 链接到链表尾部
            S.tail = newBlock;  // 更新尾指针
        }

        S.length += charsInBlock;  // 串的长度增加新增的字符数量
    }
    return true;
}


// 复制操作（把 串T 复制给 串S）
bool StrCopy(LString &S, const LString &T) {
    // 先清空串S原有内容
    Block *p = S.head;  // 新建一个指针 p ，指向第一个结点
    while(p) {
        Block *temp = p;  // 新建一个指针 temp ，指向 p 指向的结点
        p = p -> next;
        delete temp;  // 删除 temp 指向的块
    }

    // 重置链表状态
    S.head = nullptr;  // 重置头指针为空
    S.tail = nullptr;  // 重置尾指针为空
    S.length = 0;  // 重置串长

    // 如果 串T 是空串，就可直接返回了
    if(T.length == 0) {
        return true;
    }

    Block *tCurrent = T.head;  // 用于遍历 串T 的指针

    // 遍历 串T 的所有块
    while(tCurrent) {
        Block *newBlock = new Block();  // 创建新块

        // 计算当前块需要实际存储的字符数
        int charsInBlock = (tCurrent == T.tail) ? (T.length % BLOCK_SIZE == 0 ? BLOCK_SIZE : BLOCK_SIZE) : BLOCK_SIZE;
        
        // 复制字符
        for(int i = 0; i < BLOCK_SIZE; i++) {
            newBlock -> ch[i] = tCurrent -> ch[i];
        }

        newBlock -> next = nullptr;  // 新块的 next 置为空

        // 将新块添加到 串S 的尾部
        if(!S.head) {
            S.head = newBlock;
            S.tail = newBlock;
        }
        else {
            S.tail -> next = newBlock;
            S.tail = newBlock;
        }

        // 移动到 串T 的下一个块
        tCurrent = tCurrent -> next;
    }
    S.length = T.length;  // 更新串长度
    return true;
}


// 判空操作
bool StrEmpty(const LString &S) {
    return S.length == 0;  // 串长为 0 即为空串
}


// 比较操作
int StrCompare(const LString &S, const LString &T) {
    Block *sBlock = S.head;  // 新建一个指针用来标记S的当前块，初始指向第一个块
    Block *tBlock = T.head;  // 新建一个指针用来标记T的当前块，初始指向第一个块
    int sIndex = 0;  // S当前块内的字符索引
    int tIndex = 0;  // T当前块内的字符索引
    int count = 0;  // 已比较的字符计数

    // 比较
    while(count < S.length && count < T.length) {
        // 比较当前字符
        if(sBlock -> ch[sIndex] != tBlock -> ch[tIndex]) {
            return sBlock -> ch[sIndex] - tBlock -> ch[tIndex];
        }

        // 更新索引和计数
        sIndex++;
        tIndex++;
        count++;

        // 处理 串S 的块边界
        if(sIndex == BLOCK_SIZE) {
            sBlock = sBlock -> next;  // 移动到下一个块
            sIndex = 0;  // 重置块内字符索引
        }

        // 处理 串T 的块边界
        if(tIndex == BLOCK_SIZE) {
            tBlock = tBlock -> next;  // 移动到下一个块
            tIndex = 0;  // 重置块内索引
        }
    }
    // 如果字符都相同，就比较长度
    return S.length - T.length;
}


// 求串长
int StrLength(const LString &S) {
    return S.length;  // 直接返回长度
}


// 求子串（用 Sub 返回从 主串S 的第 pos 个字符开始取长度为 len 的子串）
bool SubString(LString &Sub, const LString &S, int pos, int len) {
    // 检查输入是否合法
    if(pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length) {
        std::cerr << "错误：非法位置或长度" << std::endl;
        return false;
    }

    // 清空 Sub 中原有内容
    Block *p = Sub.head;  // 新建一个指针，指向 Sub 的头指针指向位置
    while(p) {
        Block *temp = p;  // 新建一个指针，指向 p 指向的位置
        p = p -> next;
        delete temp;  // 释放当前块
    }

    // 重置链表状态
    Sub.head = nullptr;
    Sub.tail = nullptr;
    Sub.length = 0;

    // 如果 len 是空串，则直接返回
    if(len == 0) {
        return true;
    }

    // 求子串
    // 计算起始块和块内偏移
    int startBlock = (pos - 1) / BLOCK_SIZE;
    int startOffset = (pos - 1) % BLOCK_SIZE;

    // 定位到起始块
    Block *currentBlock = S.head;  // 新建一个指针，初始指向 串S 头指针指向的位置
    for(int i = 0; i < startBlock; i++) {
        // 从 串S 的第一个块开始遍历，直到找到起始块
        currentBlock = currentBlock -> next;
    }

    int count = 0;  // 已复制的字符数

    // 复制子串
    while(count < len) {
        // 创建新块
        Block *newBlock = new Block();  // 创建新块

        // 初始化新块
        for(int i = 0; i < BLOCK_SIZE; i++) {
            newBlock -> ch[i] = '#';  // 默认填充
        }

        newBlock -> next = nullptr;  // 新块的 next 指向空

        // 将新块添加到 串Sub 的尾部
        if(!Sub.head) {
            // 如果是空串，那么头指针和尾指针都指向新块
            Sub.head = newBlock;
            Sub.tail = newBlock;
        }
        else {
            // 先链接到串尾
            Sub.tail -> next = newBlock;
            // 再修改串尾指针
            Sub.tail = newBlock;
        }

        // 复制字符到新块
        int charIndex = 0;  // 新块内的字符索引
        while(charIndex < BLOCK_SIZE && count < len) {
            // 复制字符
            newBlock -> ch[charIndex] = currentBlock -> ch[startOffset];

            // 移动索引
            charIndex++;
            count++;
            startOffset++;

            // 检查是否需要移动到下一个块
            if(startOffset == BLOCK_SIZE && currentBlock -> next) {
                currentBlock = currentBlock -> next;  // 移动到下一个块
                startOffset = 0;  // 重置块内索引
            }
        }
    }

    // 更新子串长度
    Sub.length = len;
    return true;
}


// 串联接（将 串S1 和 串S2 联接成 新串T）
bool Concat(LString &T, const LString &S1, const LString &S2) {
    // 清空 串T 原有内容
    Block *p = T.head;  // 新建一个指针，指向 串T 的头指针指向的结点
    while(p) {
        Block *temp = p;
        p = p -> next;
        delete temp;
    }

    // 重置链表状态
    T.head = nullptr;
    T.tail = nullptr;
    T.length = 0;

    // 处理 S1、S2 是空串的情况
    if(S1.length == 0 && S2.length == 0) {
        return true;
    }

    // 复制 S1 到 T
    if(S1.length > 0) {
        Block *s1Block = S1.head;  // 新建一个指针，指向 串S1 的第一个结点

        while(s1Block) {
            // 创建新块
            Block *newBlock = new Block();

            // 计算当前块实际存储的字符数
            int charsInBlock;
            if(s1Block == S1.tail) {
                // 如果当前块是 S1 的最后一个块
                // 计算最后一块中的字符数
                int remainder = S1.length % BLOCK_SIZE;
                charsInBlock = (remainder == 0) ? BLOCK_SIZE : remainder;
            }
            else {
                // 如果当前不是最后一块，那么块中的字符数是满的
                charsInBlock = BLOCK_SIZE;
            }

            // 只复制有效字符
            for(int i = 0; i < charsInBlock; i++) {
                newBlock -> ch[i] = s1Block -> ch[i];
            }

            // 填充剩余部分
            for(int i = charsInBlock; i < BLOCK_SIZE; i++) {
                newBlock -> ch[i] = '#';
            }

            newBlock -> next = nullptr;  // 新块的 next 置为空

            // 将新块添加到 T 的尾部
            if(!T.head) {
                T.head = newBlock;
                T.tail = newBlock;
            }
            else {
                T.tail -> next = newBlock;
                T.tail = newBlock;
            }

            // 移动到 S1 的下一个块
            s1Block = s1Block -> next;
        }
        T.length = S1.length;
    }

    // 复制 S2 到 T 的尾部
    if(S2.length > 0) {
        Block *s2Block = S2.head;  // 新建一个指针，指向 S2 的头指针指向的结点
        while(s2Block) {
            // 创建新块
            Block *newBlock = new Block();  // 创建新块

            // 计算当前块实际存储的字符数
            int charsInBlock;
            if(s2Block == S2.tail) {
                // 如果当前块是最后一块
                // 计算最后一块中有多少字符
                int remainder = S2.length % BLOCK_SIZE;
                charsInBlock = (remainder == 0) ? BLOCK_SIZE : remainder;
            }
            else {
                // 如果当前块不是最后一块，就存满
                charsInBlock = BLOCK_SIZE;
            }

            // 只复制有效字符
            for(int i = 0; i < charsInBlock; i++) {
                newBlock -> ch[i] = s2Block -> ch[i];
            }

            // 填充剩余部分
            for(int i = charsInBlock; i < BLOCK_SIZE; i++) {
                newBlock -> ch[i] = '#';
            }

            // 把新块的 next 指向空
            newBlock -> next = nullptr;

            // 将新块添加到 T 的尾部
            if(!T.head) {
                // 修改头指针和尾指针
                T.head = newBlock;
                T.tail = newBlock;
            }
            else {
                // 添加到 T 的尾部
                T.tail -> next = newBlock;
                // 修改尾指针
                T.tail = newBlock;
            }

            // 移动到S2的下一块
            s2Block = s2Block -> next;
        }
        // 更新串长
        T.length += S2.length;
    }
    return true;
}


// 定位操作（返回 子串T 在 主串S 中第一次出现的位置）
int Index(const LString &S, const LString &T) {
    // 先判断 子串T 是否是空串
    if(T.length == 0) {
        return 1;  // 空串是任意串的子串
    }

    // 主串不能比子串短
    if(S.length < T.length) {
        return 0;
    }

    // 遍历主串所有可能的起始位置
    for(int pos = 1; pos <= S.length - T.length + 1; pos++) {
        LString sub;  // 暂存子串
        InitString(sub);  // 初始化临时子串

        // 获取当前子串
        if(SubString(sub, S, pos, T.length)) {
            if(StrCompare(sub, T) == 0) {  // 比较是否相等
                return pos;  // 返回位置
            }
        }
    }
    return 0;  // 未找到，则返回 0
}


// 清空操作
void ClearString(LString &S) {
    Block *p = S.head;  // 新建一个指针，指向 串S 的头指针指向的结点
    while(p) {
        Block *temp = p;
        p = p -> next;
        delete temp;
    }

    // 重置链表状态
    S.head = nullptr;
    S.tail = nullptr;
    S.length = 0;
}


// 销毁串
void DestroyString(LString &S) {
    ClearString(S);  // 清空即销毁
}


// 打印串内容
void PrintString(const LString &S) {
    // 先判断串是否为空
    if(StrEmpty(S)) {
        std::cout << "串为空" << std::endl;
        return;
    }

    Block *current = S.head;  // 当前块指针
    int count = 0;  // 已打印字符数

    // 遍历所有块
    while(current && count < S.length) {
        // 计算当前块的实际字符数
        int charsInBlock;
        if(current == S.tail) {
            // 如果当前块是最后一块
            // 计算最后一块中有多少字符
            int remainder = S.length % BLOCK_SIZE;
            charsInBlock = (remainder == 0) ? BLOCK_SIZE : remainder;
        }
        else {
            // 如果当前块不是最后一块，就存满
            charsInBlock = BLOCK_SIZE;
        }

        // 打印当前块的有效字符
        for(int i = 0; i < charsInBlock && count < S.length; i++) {
            std::cout << current -> ch[i];
            count++;
        }

        // 移动到下一个块
        current = current -> next;
    }
    std::cout << std::endl;
}


// 测试
int main() {
    // 声明
    LString S1;
    LString S2;
    LString S3;
    LString S4;
    LString S5;
    LString S6;

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
    StrCopy(S2, S1);  // 把 串S1 复制给 串S2

    // 判空操作
    std::cout << "S1 是否为空: " << StrEmpty(S1) << std::endl;
    std::cout << "S2 是否为空：" << StrEmpty(S2) << std::endl;
    std::cout << "S3 是否为空：" << StrEmpty(S3) << std::endl;

    // 比较操作
    std::cout << "S1 和 S2 比较: " << StrCompare(S1, S4) << std::endl;

    // 求串长
    std::cout << "S1 的串长为：" << StrLength(S1) << std::endl;
    std::cout << "S2 的串长为：" << StrLength(S2) << std::endl;
    std::cout << "S3 的串长为：" << StrLength(S3) << std::endl;
    std::cout << "S4 的串长为：" << StrLength(S4) << std::endl;

    // 求子串
    SubString(S5, S4, 7, 5);

    // 串联接
    Concat(S6, S1, S4);

    // 定位操作
    std::cout << "S1 在 S4 中的定位：" << Index(S4, S1) << std::endl;

    // 清空操作
    ClearString(S1);

    // 销毁操作
    ClearString(S2);

    // 打印串内容
    std::cout << "打印 S1: ";
    PrintString(S1);
    std::cout << "打印 S2: ";
    PrintString(S2);
    std::cout << "打印 S3: ";
    PrintString(S3);
    std::cout << "打印 S4: ";
    PrintString(S4);
    std::cout << "打印 S5: ";
    PrintString(S5);
    std::cout << "打印 S6: ";
    PrintString(S6);

    return 0;
}
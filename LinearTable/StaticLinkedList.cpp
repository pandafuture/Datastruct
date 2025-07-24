#include <iostream>

#define  MAX_SIZE 100  // 静态链表的最大长度


// 静态链表结点结构
struct StaticNode {
    int data;  // 数据域
    int next;  // 下一个元素的数组下标
};


// 静态链表结构
struct StaticLinkedList {
    StaticNode nodes[MAX_SIZE];  // 结点数组
    int head;  // 头结点下标
    int tail;  // 尾结点下标
    int size;  // 当前元素个数
    int freeList;  // 空闲链表头指针
};


// 初始化静态链表
void InitList(StaticLinkedList &L) {
    // 初始化所有结点
    for (int i = 0; i < MAX_SIZE - 1; i++) {
        L.nodes[i].next = i + 1;  // 每个结点的 next 指向下一个结点
    }

    L.nodes[MAX_SIZE - 1].next = -1;  // 把最后一个结点的 next 置为 -1

    L.head = -1;  // 头指针初始化为空
    L.tail = -1;  // 尾指针初始化为空
    L.size = 0;  // 元素个数为 0
    L.freeList = 0;  // 空闲链表头指针指向第一个结点
}


// 从空闲链表中分配结点
int AllocateNode(StaticLinkedList &L) {
    // 判断是否还有空闲结点
    if(L.freeList ==  -1) {
        return -1;  // 空间不足
    }

    int index = L.freeList;  // 获取空闲结点
    L.freeList = L.nodes[index].next;  // 更新空闲链表表头

    return index;
}


// 释放结点到空闲链表
void FreeNode(StaticLinkedList &L, int index) {
    L.nodes[index].next = L.freeList;  // 当前结点指向空闲链表表头
    L.freeList = index;  // 空闲链表表头指向当前结点
}


// 判空
bool Empty(StaticLinkedList &L) {
    return L.size == 0;  // 返回表长是否为 0
}


// 插入操作
bool ListInsert(StaticLinkedList &L, int i, int e) {
    // 先判断插入位置是否合法
    if(i < 1 || i > L.size + 1) {
        return false;  // 插入位置无效
    }

    int newNode = AllocateNode(L);  // 分配空间结点
    if(newNode == -1) {
        return false;  // 空间不足则退出
    }

    L.nodes[newNode].data = e;  // 给新结点赋值 e

    // 插入到链表头部
    if(i == 1) {
        L.nodes[newNode].next = L.head;  // 把新结点的 next 指向原来的头节点
        L.head = newNode;  // 把新结点设为新的头结点
        if(L.size == 0) {
            L.tail = newNode;  // 如果新结点是第一个元素就更新尾指针
        }
    }
    // 插入到链表尾部
    else if (i == L.size + 1) {
        L.nodes[newNode].next = -1;  // 把新结点标记为尾结点
        // 判断当前链表是否为空，若不为空则把原尾结点的 next 指向新结点
        if(L.tail != -1) {
            L.nodes[L.tail].next = newNode;
        }
        L.tail = newNode;  // 把新结点设为标为结点
        if(L.size == 0) {
            L.head = newNode;  // 如果是第一个元素，就更新头指针
        }
    }
    // 插入到链表中间
    else {
        int prev = L.head;  // 新建一个“指针” prev ，指向头结点
        // 遍历整个静态链表，找到插入位置的前一个结点
        for(int j = 1; j < i - 1; j++) {
            prev = L.nodes[prev].next;
        }
        L.nodes[newNode].next = L.nodes[prev].next;  // 把新结点的 next 指向原来的第 i 个结点
        L.nodes[prev].next = newNode;  // 把第 i-1 个结点的 next 指向新结点
    }

    L.size++;  // 表长加一
    return true;
}


// 删除操作
bool ListDelete(StaticLinkedList &L, int i, int &e) {
    // 先判断删除位置是否合法，不能小于 1 ；不能超过表长；当前表为空时也无法操作
    if(i < 1 || i > L.size || L.size == 0) {
        return false;
    }

    int toDelete;  // 要删除的结点

    // 删除头结点
    if(i == 1) {
        toDelete = L.head;  // 获取要删除的结点
        e = L.nodes[toDelete].data;  // 获取被删除结点的值
        L.head = L.nodes[toDelete].next;  // 更改头结点
        
        if(L.size == 1) {
            L.tail = -1;  // 如果删除后表为空，则更新尾指针
        }
    }
    // 删除尾结点
    else if(i == L.size) {
        int prev = L.head;  // 新建一个“指针”，指向头结点
        // 遍历整个静态链表，找到表尾结点的前一个结点
        while(L.nodes[prev].next != L.tail) {
            prev = L.nodes[prev].next;
        }

        toDelete = L.tail;  // 获取要删除的结点
        e = L.nodes[toDelete].data;  // 获取被删除结点的值
        L.nodes[prev].next = -1;  // 把原尾结点的前驱结点的 next 指向 -1
        L.tail = prev;  // 更新尾结点为原尾结点的前驱结点
    }
    // 删除中间结点
    else {
        int prev = L.head;  // 新建一个“指针” prev ，指向头结点
        // 遍历整个静态链表，找到被删除结点的前驱结点
        for(int j = 1; j < i - 1; j++) {
            prev = L.nodes[prev].next;
        }

        toDelete = L.nodes[prev].next;  // 获取要删除的结点
        e = L.nodes[toDelete].data;  // 获取被删除结点的值
        L.nodes[prev].next = L.nodes[toDelete].next;  // 把被删除结点的前驱结点的 next 指向被删除结点的后继结点
    }

    FreeNode(L, toDelete);  // 释放被删除结点到空闲链表
    L.size--;  // 表长减一
    return true;
}


// 按值查找
int LocateElem(StaticLinkedList &L, int e) {
    int current = L.head;  // 新建一个指针 current ，指向头结点
    int pos = 1;  // 设置一个计数器，记录当前指向第几个结点，默认为 1 ，指向第一个结点
    
    // 遍历整个链表，找到值为 e 的结点，并返回其位序
    while(current != -1) {
        if(L.nodes[current].data == e) {
            return pos;
        }
        current = L.nodes[current].next;
        pos++;
    }

    return 0;  // 如果未找到就返回 0
}


// 按位查找
int GetElem(StaticLinkedList &L, int i) {
    // 先判断输入是否合法，不能小于 1 ；也不能超过表长
    if(i < 1 || i > L.size) {
        return -1;
    }

    int current = L.head;  // 新建一个“指针” current ，指向第一个结点
    // 遍历整个静态链表，找到第 i-1 个结点
    for(int j = 1; j < i; j++) {
        current = L.nodes[current].next;
    }

    return L.nodes[current].data;  // 返回其值
}


// 求表长
int Length(StaticLinkedList &L) {
    return L.size;  // 直接返回表长
}


// 输出操作
void PrintList(StaticLinkedList &L) {
    // 如果静态链表为空则输出空提示
    if(L.size == 0) {
        std::cout << "Empty List" << std::endl;
        return;
    }

    int current = L.head;  // 新建一个“指针” current ，指向头结点
    // 遍历整个静态链表，同时输出每个结点的值
    while(current != -1) {
        std::cout << L.nodes[current].data << " ";
        current = L.nodes[current].next;
    }
    std::cout << std::endl;
}


// 销毁操作
void DestroyList(StaticLinkedList &L) {
    // 重置所有结点
    for (int i = 0; i < MAX_SIZE - 1; i++) {
        L.nodes[i].next = i + 1;  // 把每个结点的 next 重置为下一个位置
    }
    L.nodes[MAX_SIZE - 1].next = -1;  // 把最后一个结点的 next 重置为 -1

    L.head = -1;  // 头指针设为 -1，表示链表为空
    L.tail = -1;  // 重置尾指针
    L.size = 0;  // 重置表长
    L.freeList = 0;  // 重置空闲链表表头指针
}


// 打印空闲链表
void PrintFreeList(StaticLinkedList &L) {
    std::cout << "Free List: ";
    int current = L.freeList;  // 新建一个“指针” current ，指向空闲链表的表头
    // 遍历整个链表，同时输出每个空闲结点的数组下标
    while(current != -1) {
        std::cout << current << " ";
        current = L.nodes[current].next;
    }
    std::cout << std::endl;
}


// 测试
int main(){
    StaticLinkedList L;  // 声明一个静态链表 L
    int e;  // 用来作为返回值

    InitList(L);  // 初始化静态链表

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空操作
    std::cout << "表长：" << Length(L) << std::endl;  // 求表长

    ListInsert(L, 1, 1);  // 再第一个位置插入 1
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    ListInsert(L, 4, 4);
    ListInsert(L, 5, 5);
    std::cout << "输出：";
    PrintList(L);  // 输出操作

    ListDelete(L, 2, e);  // 删除第 2 个位置的元素
    std::cout << "删除第二个位置的元素：";
    PrintList(L);
    std::cout << "删除的值为：" << e << std::endl;  // 输出被删除的值
    PrintFreeList(L);  // 输出空闲链表

    std::cout << "按值查找：" << LocateElem(L, 3) << std::endl;  // 按查找值为三的元素
    std::cout << "按位查找：" << GetElem(L, 2) << std::endl;  // 按位查找第 2 个位置的元素

    std::cout << "判空：" << Empty(L) << std::endl;  // 判空操作
    std::cout << "表长：" << Length(L) <<std::endl;  // 求表长

    DestroyList(L);  // 销毁操作
    std::cout << "输出：";
    PrintList(L);

    std::cout << "输出空闲链表：";
    PrintFreeList(L);
}
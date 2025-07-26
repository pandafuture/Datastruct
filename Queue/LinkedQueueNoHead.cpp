#include <iostream>


// 链式队列（不带头结点）结点结构
struct QueueNode {
    int data;  // 数据域
    QueueNode *next;  // 指针域
};


// 链式队列（不带头结点）结构
struct LinkQueue {
    QueueNode *front;  // 队头指针，指向第一个元素
    QueueNode *rear;  // 队尾指针，指向最后一个元素
    int size;  // 队列中元素个数
};


// 初始化
void InitQueue(LinkQueue &Q) {
    Q.front = nullptr;  // 队头指针置为空
    Q.rear = nullptr;  // 队尾指针置为空
    Q.size = 0;  // 元素个数初始化为 0
}


// 判队空
bool IsEmpty(LinkQueue Q) {
    return Q.front == nullptr;  // 队头为空表示队列空
}


// 入队
void EnQueue(LinkQueue &Q, int e) {
    // 创建新结点
    QueueNode *s = new QueueNode;
    s -> data = e;  // 把 e 的值赋给新结点 s
    s -> next  = nullptr;  // 新结点 s 在队尾插入，就把 next 值为空

    // 先判断队列是否为空
    if(IsEmpty(Q)) {
        // 队列为空时，新结点既是队头也是队尾
        Q.front = s;  // 把队头指针指向新结点
        Q.rear = s;  // 把队尾指针指向新结点
    }
    else {
        // 队列非空时，把新结点链接到队尾
        Q.rear -> next = s;
        Q.rear = s;  // 更新队尾指针
    }

    Q.size++;  // 更新队列大小
}


// 出队
bool DeQueue(LinkQueue &Q, int &e) {
    // 先判断队列是否为空
    if(IsEmpty(Q)) {
        std::cout << "队列为空" << std::endl;
        return false;
    }

    QueueNode *p = Q.front;  // 新建一个指针 p ，指向队首
    e = p -> data;  // 用 e 返回队首元素的值
    Q.front = Q.front -> next;  // 更新队首指针
    // 如果队列只有一个元素，出队后队列为空，就更新队尾指针
    if(Q.front == nullptr) {
        Q.rear = nullptr;
    }

    // 删除 p 结点
    delete p;

    // 更新队列大小
    Q.size--;

    return true;
}


// 读队首元素
bool GetFront(LinkQueue Q, int &e) {
    // 先判断队列是否为空
    if(IsEmpty(Q)) {
        std::cout << "队列为空" << std::endl;
        return false;
    }

    e = Q.front -> data;  // 用 e 返回队首元素的值
    return true;
}


// 获取队列长度
int QueueLength(LinkQueue Q) {
    return Q.size;  // 直接返回队列长度
}


// 打印队列内容
void PrintQueue(LinkQueue Q) {
    // 先判断队列是否为空
    if(IsEmpty(Q)) {
        std::cout << "队列为空" << std::endl;
        return;
    }

    QueueNode *p = Q.front;  // 新建一个指针 p ，指向队首
    // 遍历整个队列，同时输出每个元素
    while(p != nullptr) {
        std::cout << p -> data << " ";
        p = p -> next;
    }
    std::cout << std::endl;
}


// 销毁队列
void DestroyQueue(LinkQueue &Q) {
    int e;  // 作为返回值
    // 循环出队所有元素
    while(!IsEmpty(Q)) {
        DeQueue(Q, e);
    }
}


// 测试
int main() {
    LinkQueue Q;  // 声明一个队列
    int e;  // 返回值

    InitQueue(Q);  // 初始化队列
    std::cout << "判空：" << IsEmpty(Q) << std::endl;  // 判空操作
    std::cout << "队列长为：" << QueueLength(Q) << std::endl;  // 求队列长

    EnQueue(Q, 1);  // 将 1 入队
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    EnQueue(Q, 5);
    std::cout << "输出队列：";
    PrintQueue(Q);

    GetFront(Q, e);  // 读队首元素
    std::cout << "队首元素为：" << e << std::endl;

    DeQueue(Q, e);  // 出队
    std::cout << "出队的队首为：" << e << std::endl;
    std::cout << "输出队列：";
    PrintQueue(Q);

    GetFront(Q, e);  // 读队首元素
    std::cout << "队首元素为：" << e << std::endl;

    std::cout << "判空：" << IsEmpty(Q) << std::endl;  // 判空操作
    std::cout << "队列长为：" << QueueLength(Q) << std::endl;  // 求队列长

    DestroyQueue(Q);  // 销毁队列
}
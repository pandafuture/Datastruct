#include <iostream>

// 链式队列（带头结点）结点结构
struct QueueNode {
    int data;  // 数据域
    QueueNode *next;  // 指针域
};


// 链式队列（带头结点）队列结构
struct LinkedQueue {
    QueueNode *front;  // 队头指针，指向头结点
    QueueNode *rear;  // 队尾结点，指向尾结点
    int size;  // 队列中元素的个数
};


// 初始化
void InitQueue(LinkedQueue &Q) {
    Q.front = new QueueNode;  // 新建一个头结点
    Q.front -> next = nullptr;  // 头结点的 next 指向空，当前队列为空
    Q.rear = Q.front;  // 队尾指针指向头结点
    Q.size = 0;  // 队列长度初始化为 0
}


// 判队空
bool IsEmpty(LinkedQueue Q) {
    return Q.front == Q.rear;  // 队头等于队尾时队列为空
}


// 入队操作（插入到队尾）
void EnQueue(LinkedQueue &Q, int e) {
    // 创建一个新结点
    QueueNode *s = new QueueNode;
    s -> data = e;  // 把 e 的值赋给新结点
    s -> next = nullptr;  // 新结点要插入到队尾，所以 next 指向空

    // 把新结点链接到队尾
    Q.rear -> next = s;
    Q.rear = s;  // 更新队尾结点

    Q.size++;  // 更新队列大小
}


// 出队操作（队首元素出队）
bool DeQueue(LinkedQueue &Q, int &e) {
    // 先判断队列是否为空
    if(IsEmpty(Q)) {
        std::cout << "队列为空" << std::endl;
        return false;
    }

    QueueNode *p = Q.front -> next;  // 新建一个指针 p ，指向队首结点
    e = p -> data;  // 用 e 返回队首元素的值
    Q.front -> next = p -> next;  // 更新队首结点

    // 如果删除的是最后一个结点，还要更新队尾指针
    if(Q.rear == p) {
        Q.rear = Q.front;
    }

    delete p;  // 删除队首结点
    Q.size--;  // 更新队列大小
    return true;
}


// 读取队首元素
bool GetFront(LinkedQueue Q, int &e) {
    // 先判断队列是否为空
    if(IsEmpty(Q)) {
        std::cout << "队列为空" << std::endl;
        return false;
    }

    e = Q.front -> next -> data;  // 读取队首元素的值
    return true;
}


// 获取队列长度
int Length(LinkedQueue Q, int &e) {
    return Q.size;
}


// 输出队列
void PrintQueue(LinkedQueue Q) {
    // 先判断队列是否为空
    if(IsEmpty(Q)) {
        std::cout << "队列为空" << std::endl;
        return;
    }

    QueueNode *p = Q.front -> next;  // 新建一个指针 p ，指向队首元素
    while(p) {
        std::cout << p -> data << " ";
        p = p -> next;
    }
    std::cout << std::endl;
}


// 销毁队列
void DestroyQueue(LinkedQueue &Q) {
    // 循环出队所有元素
    int e;
    while(!IsEmpty(Q)) {
        DeQueue(Q, e);
    }

    // 销毁头结点
    delete Q.front;
    Q.front = nullptr;  // 队首指针值为空
    Q.rear = nullptr;  // 队尾指针置为空
}


// 测试
int main() {
    LinkedQueue Q;  // 声明一个链式队列（带头结点）
    int e;  // 返回值

    InitQueue(Q);  // 初始化链式队列

    std::cout << "判空：" << IsEmpty(Q) << std::endl;  // 判空操作
    std::cout << "队列长：" << Length(Q, e) << std::endl;  // 求队列长

    EnQueue(Q, 1);  // 将 1 入队
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    EnQueue(Q, 5);
    std::cout << "输出队列：";
    PrintQueue(Q);  // 输出队列
    
    GetFront(Q, e);  // 读队首元素
    std::cout << "队首元素为：" << e << std::endl;

    DeQueue(Q, e);  // 出队
    std::cout << "输出队列：";
    PrintQueue(Q);  // 输出队列
    std::cout << "出队的队首元素为：" << e << std::endl;

    GetFront(Q, e);  // 读队首元素
    std::cout << "队首元素为：" << e << std::endl;

    std::cout << "判空：" << IsEmpty(Q) << std::endl;  // 判空操作
    std::cout << "队列长：" << Length(Q, e) << std::endl;  // 求队列长

    DestroyQueue(Q);  // 销毁队列
}
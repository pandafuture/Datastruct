#include <iostream>

#define MAX_SIZE 50  // 定义队列的最大容量


// 顺序队列（循环队列）存储结构
struct SeqQueue {
    int data[MAX_SIZE];  // 存储队列元素的数组
    int front;  // 队首指针，指向队首元素
    int rear;  // 队尾指针，指向队尾元素的下一个位置
};


// 初始化队列
void InitQueue(SeqQueue &Q) {
    Q.front = 0;  // 初始化队首指针为 0
    Q.rear = 0;  // 初始化队尾指针为 0
}


// 判空操作
bool Empty(SeqQueue Q) {
    return Q.front == Q.rear;
}


// 判满操作
bool Full(SeqQueue Q) {
    return (Q.rear + 1) % MAX_SIZE == Q.front;  // 队尾下一个位置是队头时队列满
}


// 入队操作
bool EnQueue(SeqQueue &Q, int e) {
    // 先判断队列是否已满
    if(Full(Q)) {
        std::cout << "队列已满" << std::endl;
        return false;
    }

    Q.data[Q.rear] = e;  // 把 e 入队到队尾指针指向的位置
    Q.rear = (Q.rear + 1) % MAX_SIZE;  // 队尾指针加一取模
    return true;
}


// 出队操作
bool DeQueue(SeqQueue &Q, int &e) {
    // 先判断队列是否为空
    if(Empty(Q)) {
        std::cout << "队列为空" << std::endl;
        return false;
    }

    e = Q.data[Q.front];  // 获取队首元素
    Q.front = (Q.front + 1) % MAX_SIZE;  // 队首指针后移一位
    return true;
}


// 读队首元素
bool GetHead(SeqQueue Q, int &e) {
    // 先判断队列是否为空
    if(Empty(Q)) {
        std::cout << "队列为空" << std::endl;
        return false;
    }

    e = Q.data[Q.front];  // 获取队首元素
    return true;
}


// 获取队列长度
int Length(SeqQueue Q) {
    return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
}


// 输出队列
void PrintQueue(SeqQueue Q) {
    // 先判断队列是否为空
    if(Empty(Q)) {
        std::cout << "队列为空" << std::endl;
        return;
    }

    // 遍历整个循环队列，同时打印每个元素
    int i = Q.front;  // 从队首开始
    while(i != Q.rear) {
        std::cout << Q.data[i] << " ";
        i = (i + 1) % MAX_SIZE;
    }
    std::cout << std::endl;
}


// 销毁队列
void DestroyQueue(SeqQueue &Q) {
    // 对于静态数组，不需要释放内存
    Q.front = 0;  // 重置队首指针
    Q.rear = 0;  // 重置队尾指针
}


// 测试
int main() {
    SeqQueue Q;  // 声明一个循环队列
    int e;  // 返回值

    InitQueue(Q);  // 初始化循环队列

    std::cout << "判空：" << Empty(Q) << std::endl;  // 判空操作
    std::cout << "判满：" << Full(Q) << std::endl;  // 判满操作

    EnQueue(Q, 1);  // 将 1 入队
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    EnQueue(Q, 5);
    std::cout << "输出队列：";
    PrintQueue(Q);  // 输出队列

    GetHead(Q, e);  // 读队首元素
    std::cout << "队首元素为：" << e << std::endl;

    std::cout << "队长为：" << Length(Q) << std::endl;  // 求队长

    std::cout << "判空：" << Empty(Q) << std::endl;  // 判空操作

    DeQueue(Q, e);  // 出队
    std::cout << "出队元素为：" << e << std::endl;
    std::cout << "输出队列：";
    PrintQueue(Q);  // 输出队列

    std::cout << "队长为: " << Length(Q) << std::endl;  // 求队长

    GetHead(Q, e);  // 读队首元素
    std::cout << "队首元素为：" << e << std::endl;
    std::cout << "输出队列：";
    PrintQueue(Q);

    std::cout << "队长为：" << Length(Q) << std::endl;  // 求队长

    DestroyQueue(Q);  // 销毁循环队列
}
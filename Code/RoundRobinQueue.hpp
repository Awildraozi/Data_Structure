#pragma once
/*
本程序采用少用一个元素空间来判断队列是否为满
队空的条件 front = rear
队满的条件 (rear + 1)%(MAXQSIZE + 1)= front
*/

#include <iostream>
#include <limits>
#include <stdexcept>

typedef struct RoundRobinQueue{
    int *data;
    int rear;
    int front;
    int MAXQSIZE;

    RoundRobinQueue(int size){
        // size 表示最多存放的元素数量，必须为正；额外预留一个空位。
        // 在计算 size + 1 前排除 int 最大值，避免有符号整数溢出。
        if(size <= 0 || size == std::numeric_limits<int>::max()){
            throw std::invalid_argument("Queue capacity must be between 1 and INT_MAX - 1.");
        }
        MAXQSIZE = size;
        data = new int[MAXQSIZE + 1];
        rear = 0;
        front = 0;
    }
    //注意在C的实现中，struct不具有构造函数，需要设置Init函数并手动调用

    // 默认拷贝只复制 data 的地址，两个对象会共享数组并在析构时重复释放。
    // 暂时禁止拷贝构造和拷贝赋值；以后需要复制队列时再实现深拷贝。
    RoundRobinQueue(const RoundRobinQueue&) = delete;
    RoundRobinQueue& operator=(const RoundRobinQueue&) = delete;

    ~RoundRobinQueue(){
        delete[] data;
    }

    int QueueLen();
    //获取当前队列逻辑长度
    void EnQueue(int e);
    //添加新元素
    int DeQueue();
    //弹出元素
    void clearQueue();
    //清除当前队列所有值，但不执行删除

}RRQueue;

inline void RRQueue::EnQueue(int e){
    if((rear + 1) % (MAXQSIZE + 1) == front){
        std::cout << "Queue is full!" << std::endl;
        return;
    }
    data[rear] = e;
    rear = (rear + 1) % (MAXQSIZE + 1);
}

inline int RRQueue::DeQueue(){
    if(rear == front){
        std::cout << "Queue is empty!" << std::endl;
        return -1;
    }
    int temp = data[front];
    front = (front + 1) % (MAXQSIZE + 1);
    return temp;
}

inline int RRQueue::QueueLen(){
    // 分情况计算环形距离，避免大容量下 rear + MAXQSIZE + 1 溢出。
    if(rear >= front){
        return rear - front;
    }
    return (MAXQSIZE + 1) - (front - rear);
}

inline void RRQueue::clearQueue(){
    while(rear != front){
        data[front] = 0;
        front = (front + 1) % (MAXQSIZE + 1);
    }
    //如果只是想逻辑清除，直接rear = front也没问题
}

#pragma once
/*
本程序采用不带头结点的单链表实现队列。
front 指向队首元素，rear 指向队尾元素。
队空时 front 和 rear 均为 nullptr；入队接在队尾，出队删除队首。
*/

#include <iostream>

typedef struct QueueNode{
    int data;
    QueueNode* next;
}QueueNode;

typedef struct LinkedQueue{
    QueueNode* front = nullptr;
    QueueNode* rear = nullptr;
    int queuelen = 0;

    // 链式队列按需申请节点，无需在构造时指定容量。
    LinkedQueue() = default;

    // 禁止默认浅拷贝，避免多个队列共享节点而重复释放内存。
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    ~LinkedQueue(){
        clearQueue();
    }

    int QueueLen();
    // 返回当前队列的元素个数。
    void EnQueue(int e);
    // 在队尾添加新元素。
    int DeQueue();
    // 删除并返回队首元素；空队列沿用循环队列的约定，返回 -1。
    void clearQueue();
    // 释放全部节点，使队列恢复为空，但保留队列对象供后续使用。
}LQueue;

inline int LinkedQueue::QueueLen(){
    return queuelen;
}

inline void LinkedQueue::EnQueue(int e){
    // 分配成功后才修改队列，若 new 抛出异常，原队列仍保持不变。
    QueueNode* newNode = new QueueNode{e, nullptr};
    if(rear == nullptr){
        // 原队列为空，新节点同时是队首和队尾。
        front = newNode;
    }else{
        rear->next = newNode;
    }
    rear = newNode;
    queuelen++;
}

inline int LinkedQueue::DeQueue(){
    if(front == nullptr){
        std::cout << "Queue is empty!" << std::endl;
        return -1;
    }

    QueueNode* temp = front;
    int value = temp->data;
    front = front->next;
    if(front == nullptr){
        // 删除最后一个节点后，rear 也必须置空，避免成为悬空指针。
        rear = nullptr;
    }
    delete temp;
    queuelen--;
    return value;
}

inline void LinkedQueue::clearQueue(){
    while(front != nullptr){
        QueueNode* temp = front;
        // 先保存下一节点的位置，再释放当前节点。
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    queuelen = 0;
}

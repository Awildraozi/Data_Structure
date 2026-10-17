#pragma once
#include <iostream>

typedef struct StackNode{
    int data;
    StackNode* previous;
}StackNode;

typedef struct Stack{
    // [内存修复 1] 默认构造即为空栈，保证首次操作和析构时指针有效。
    StackNode* top = nullptr;
    StackNode* base = nullptr;
    int stacklen = 0;

    Stack() = default;

    // [内存修复 2] 对象销毁时自动释放全部节点，避免忘记手动清空导致泄漏。
    ~Stack() { ClearStack(); }

    // [内存修复 3] 禁止浅拷贝，避免多个栈共享节点后悬空访问或重复释放。
    // 复制赋值还可能覆盖目标栈原有节点的地址，造成内存泄漏。
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void Initzstack();
    // 初始化为空栈
    int StackLen();
    //返回当前栈的元素个数
    void ClearStack();
    //清除当前栈
    void Push(int e);
    //插入新元素
    int Pop();
    //弹出新元素
}Stack;

inline void Stack::Initzstack(){
    // [内存修复 4] 重新初始化前释放旧节点，不能直接置空指针丢失整条链。
    ClearStack();
}

inline int Stack::StackLen(){
    return stacklen;
}

inline void Stack::ClearStack(){
    auto curNode = top;
    while(curNode){
        auto temp = curNode;
        // 删除前先保存下一节点，避免释放后继续访问该节点。
        curNode = curNode->previous;
        delete(temp);
    }
    // 无论原来是否为空，清理后都恢复一致的空栈状态，可安全重复调用。
    top = nullptr;
    base = nullptr;
    stacklen = 0;
}
        

inline void Stack::Push(int e){
    // [内存修复 5] 使用 new 与 Pop/ClearStack 中的 delete 配对。
    // 分配成功后才修改栈；若 new 抛出异常，原栈的指针和长度保持不变。
    StackNode* newNode = new StackNode{e, top};
    if(!top){
        base = newNode;
    }
    top = newNode;
    stacklen++;
}

inline int Stack::Pop(){
    if(!top)
        return;
    StackNode* temp = top;
    top = top->previous;
    if(top == nullptr)
        base = nullptr;
    int temp_v = temp->data;
    delete(temp);
    stacklen--;
    return temp_v;
}

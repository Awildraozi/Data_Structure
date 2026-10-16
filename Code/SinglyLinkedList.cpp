#include <iostream>
using namespace std;

struct Node { int data; Node *next; };

// 操作名：初始化单链表
// 实现：创建头结点，使插入和删除操作更统一。
void initList(Node *&head) { head = new Node{0, nullptr}; }

// 操作名：判空
bool isEmpty(const Node *head) { return head == nullptr || head->next == nullptr; }

// 操作名：获取长度
int getLength(const Node *head) {
    int length = 0;
    const Node *current = head == nullptr ? nullptr : head->next;
    while (current != nullptr) { ++length; current = current->next; }
    return length;
}

// 操作名：头插法插入
void insertAtHead(Node *head, int value) {
    if (head != nullptr) head->next = new Node{value, head->next};
}

// 操作名：尾插法插入
// 实现：找到最后一个结点并连接新结点。
void insertAtTail(Node *head, int value) {
    if (head == nullptr) return;
    Node *current = head;
    while (current->next != nullptr) current = current->next;
    current->next = new Node{value, nullptr};
}

// 操作名：按位置插入
// 实现：找到前驱结点后修改指针。位置从 1 开始。
bool insertElement(Node *head, int position, int value) {
    if (head == nullptr || position < 1) return false;
    Node *previous = head;
    for (int i = 1; i < position && previous != nullptr; ++i) previous = previous->next;
    if (previous == nullptr) return false;
    previous->next = new Node{value, previous->next};
    return true;
}

// 操作名：按位置删除
// 实现：绕过目标结点，再释放其动态内存。
bool deleteElement(Node *head, int position, int &deletedValue) {
    if (head == nullptr || position < 1) return false;
    Node *previous = head;
    for (int i = 1; i < position && previous->next != nullptr; ++i) previous = previous->next;
    Node *target = previous->next;
    if (target == nullptr) return false;
    deletedValue = target->data;
    previous->next = target->next;
    delete target;
    return true;
}

// 操作名：按位置获取元素
bool getElement(const Node *head, int position, int &value) {
    if (head == nullptr || position < 1) return false;
    const Node *current = head->next;
    for (int i = 1; i < position && current != nullptr; ++i) current = current->next;
    if (current == nullptr) return false;
    value = current->data;
    return true;
}

// 操作名：按值查找
// 实现：逐结点比较，返回从 1 开始的位置；未找到返回 -1。
int findElement(const Node *head, int value) {
    int position = 1;
    const Node *current = head == nullptr ? nullptr : head->next;
    while (current != nullptr) {
        if (current->data == value) return position;
        current = current->next;
        ++position;
    }
    return -1;
}

// 操作名：修改元素
bool updateElement(Node *head, int position, int newValue) {
    if (head == nullptr || position < 1) return false;
    Node *current = head->next;
    for (int i = 1; i < position && current != nullptr; ++i) current = current->next;
    if (current == nullptr) return false;
    current->data = newValue;
    return true;
}

// 操作名：遍历单链表
void printList(const Node *head) {
    const Node *current = head == nullptr ? nullptr : head->next;
    while (current != nullptr) {
        cout << current->data << (current->next == nullptr ? "" : " -> ");
        current = current->next;
    }
    cout << endl;
}

// 操作名：清空单链表
// 实现：逐个释放数据结点，但保留头结点。
void clearList(Node *head) {
    if (head == nullptr) return;
    Node *current = head->next;
    while (current != nullptr) {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head->next = nullptr;
}

// 操作名：销毁单链表
// 实现：释放数据结点和头结点，并将头指针置空。
void destroyList(Node *&head) {
    clearList(head);
    delete head;
    head = nullptr;
}

int main() {
    Node *head = nullptr;
    initList(head);
    insertAtTail(head, 10);
    insertAtTail(head, 20);
    insertAtHead(head, 5);
    insertElement(head, 3, 15);
    printList(head);

    int value;
    if (getElement(head, 3, value)) cout << "第 3 个元素：" << value << endl;
    cout << "元素 20 的位置：" << findElement(head, 20) << endl;

    updateElement(head, 2, 8);
    int deletedValue;
    if (deleteElement(head, 3, deletedValue)) cout << "删除：" << deletedValue << endl;
    printList(head);

    destroyList(head);
    return 0;
}

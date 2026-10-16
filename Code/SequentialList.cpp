#include <iostream>
using namespace std;

const int MAX_SIZE = 100;
struct SequentialList { int data[MAX_SIZE]; int length; };

// 操作名：初始化顺序表
void initList(SequentialList &list) { list.length = 0; }

// 操作名：判空
bool isEmpty(const SequentialList &list) { return list.length == 0; }

// 操作名：获取长度
int getLength(const SequentialList &list) { return list.length; }

// 操作名：按位置插入
// 实现：将插入位置及其后的元素后移，再写入新元素。位置从 1 开始。
bool insertElement(SequentialList &list, int position, int value) {
    if (list.length >= MAX_SIZE || position < 1 || position > list.length + 1) return false;
    for (int i = list.length; i >= position; --i) list.data[i] = list.data[i - 1];
    list.data[position - 1] = value;
    ++list.length;
    return true;
}

// 操作名：按位置删除
// 实现：保存删除值，将后续元素前移。位置从 1 开始。
bool deleteElement(SequentialList &list, int position, int &deletedValue) {
    if (position < 1 || position > list.length) return false;
    deletedValue = list.data[position - 1];
    for (int i = position; i < list.length; ++i) list.data[i - 1] = list.data[i];
    --list.length;
    return true;
}

// 操作名：按位置获取元素
bool getElement(const SequentialList &list, int position, int &value) {
    if (position < 1 || position > list.length) return false;
    value = list.data[position - 1];
    return true;
}

// 操作名：按值查找
// 实现：顺序比较，返回从 1 开始的位置；未找到返回 -1。
int findElement(const SequentialList &list, int value) {
    for (int i = 0; i < list.length; ++i) if (list.data[i] == value) return i + 1;
    return -1;
}

// 操作名：修改元素
bool updateElement(SequentialList &list, int position, int newValue) {
    if (position < 1 || position > list.length) return false;
    list.data[position - 1] = newValue;
    return true;
}

// 操作名：遍历顺序表
void printList(const SequentialList &list) {
    cout << "顺序表：";
    for (int i = 0; i < list.length; ++i) cout << list.data[i] << ' ';
    cout << endl;
}

// 操作名：清空顺序表
// 静态数组无需手动释放，将长度置零即可。
void clearList(SequentialList &list) { list.length = 0; }

int main() {
    SequentialList list;
    initList(list);
    insertElement(list, 1, 10);
    insertElement(list, 2, 20);
    insertElement(list, 2, 15);
    printList(list);

    int value;
    if (getElement(list, 2, value)) cout << "第 2 个元素：" << value << endl;
    cout << "元素 20 的位置：" << findElement(list, 20) << endl;

    updateElement(list, 2, 18);
    int deletedValue;
    if (deleteElement(list, 1, deletedValue)) cout << "删除：" << deletedValue << endl;
    printList(list);

    clearList(list);
    return 0;
}

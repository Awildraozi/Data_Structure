#include <iostream>
#include <map>
//跳舞者个人信息
typedef struct
{
	std::string name; 
	std::string sex;
    dancer* next;
}dancer;

typedef struct Night_Dancer
{
    dancer* front = nullptr;
    dancer* rear = nullptr;
    int queuelen = 0;

    // 链式队列按需申请节点，无需在构造时指定容量。
    Night_Dancer() = default;

    // 禁止默认浅拷贝，避免多个队列共享节点而重复释放内存。
    Night_Dancer(const Night_Dancer&) = delete;
    Night_Dancer& operator=(const Night_Dancer&) = delete;

    ~Night_Dancer(){
        clearQueue();
    }

    int QueueLen();
    // 返回当前队列的元素个数。
    void EnQueue(std::string a, std::string b);
    // 在队尾添加新元素。
    std::map<std::string, std::string> DeQueue();
    // 删除并返回队首元素；空队列沿用循环队列的约定，返回空映射。
    void clearQueue();
    // 释放全部节点，使队列恢复为空，但保留队列对象供后续使用。
    bool isEmpty() { return queuelen == 0; }
    // 判断队列是否为空。
}Nt_Dancer;
Nt_Dancer Mdancer,Fdancer;

inline int Night_Dancer::QueueLen(){
    return queuelen;
}

inline void Night_Dancer::EnQueue(std::string a, std::string b){
    // 分配成功后才修改队列，若 new 抛出异常，原队列仍保持不变。
    dancer* newNode = new dancer{a, b, nullptr};
    if(rear == nullptr){
        // 原队列为空，新节点同时是队首和队尾。
        front = newNode;
    }else{
        rear->next = newNode;
    }
    rear = newNode;
    queuelen++;
}

inline std::map<std::string, std::string> Night_Dancer::DeQueue(){
    if(front == nullptr){
        std::cout << "Queue is empty!" << std::endl;
        return {};
    }
    dancer* temp = front;
    std::map<std::string, std::string> data = {temp->name, temp->sex};
    front = front->next;
    if(front == nullptr){
        rear = nullptr;
    }
    delete temp;
    queuelen--;
    return data; 
}

inline void Night_Dancer::clearQueue(){
    while(front != nullptr){
        dancer* temp = front;
        // 先保存下一节点的位置，再释放当前节点。
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    queuelen = 0;
}

void DancerPartner(dancer list[],int num)
{
    for(int i=0;i<num;i++)
    {
        if(list[i].sex=="M")
        {
            Mdancer.EnQueue(list[i].name,list[i].sex);
        }
        else
        {
            Fdancer.EnQueue(list[i].name,list[i].sex);
        }
    }
    std::cout<<"The dancing partners are:\n"<<std::endl;
    while(!Mdancer.isEmpty() && !Fdancer.isEmpty())
    {
        std::map<std::string, std::string> male = Mdancer.DeQueue();
        std::map<std::string, std::string> female = Fdancer.DeQueue();
        std::cout<<male.begin()->first<<" and "<<female.begin()->first<<std::endl;
    }
    if(!Mdancer.isEmpty())
    {
        std::cout<<"The first woman to get a partner is: "<<std::endl;
        while(!Mdancer.isEmpty())
        {
            std::map<std::string, std::string> male = Mdancer.DeQueue();
            std::cout<<male.begin()->first<<std::endl;
        }
    }
    else if(!Fdancer.isEmpty())
    {
        std::cout<<"The first man to get a partner is: "<<std::endl;
        while(!Fdancer.isEmpty())
        {
            std::map<std::string, std::string> female = Fdancer.DeQueue();
            std::cout<<female.begin()->first<<std::endl;
        }
    }
}



int main()
{
    int num;
    std::cout<<"Please enter the number of dancers: ";
    std::cin>>num;
    dancer list[num];
    for(int i=0;i<num;i++)
    {
        std::cout<<"Please enter the name and sex of dancer "<<i+1<<": ";
        std::cin>>list[i].name>>list[i].sex;
    }
    DancerPartner(list,num);
}
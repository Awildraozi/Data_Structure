#include "LinkedStack.hpp"

int main(){
    //构造栈并初始化
    Stack ns;
    ns.Initzstack();

    //输入数字
    int n;
    if(!(std::cin >> n)){
        return 1;
    }

    //转化过程，这里以十进制转八进制为例；0也需要入栈一次
    do{
        ns.Push(n % 8);
        n /= 8;
    }while(n);
    while(ns.StackLen() > 0){
        std::cout << ns.Pop();
    }
    std::cout << std::endl;
    return 0;
    
}

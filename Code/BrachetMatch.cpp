#include "LinkedStack.hpp"

int main(){
    bool flag = true;
    char ch;
    Stack S;
    while(std::cin >> ch){
        if(ch == '('){
            S.Push(1);
        }
        else if(ch == '['){
            S.Push(2);
        }
        else if(ch == ')'){
            if(S.Pop() != 1){
                flag = false;
                break;
            }
        }
        else if(ch == ']'){
            if(S.Pop() != 2){
                flag = false;
                break;
            }
        }
        else{}
    }

    if(flag)
        std::cout << "Matched" << std::endl;
    else
        std::cout << "Dismatched" << std::endl;
    return 0;
}
#include <stdio.h>
#include "Stack/stack.h"

int main() {
    
    puts("Yes:");
    fflush(stdin);
    Stack stk;
    StackCtor_(stk, int);

    int value = 5;
    StackPush(&stk, &value);
    value = 6;
    StackPush(&stk, &value);

    value = 0;
    StackPop(&stk, &value);
    printf("First element of Stack is:  %d\n", value);
    StackPop(&stk, &value);
    printf("Second element of Stack is: %d\n", value);

    StackDtor(&stk);
    return 0;
}

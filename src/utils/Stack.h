#ifndef RPG_STACK_H
#define RPG_STACK_H

class Stack
{
    int m_stackEnd;
    const int m_range;
    int* m_stack;
public:
    Stack(const int range, int stack_end = 0);
    ~Stack();

    void push(int element);
    int pop();
    int getElement();
    int popSearch(int key);
};

#endif //RPG_STACK_H

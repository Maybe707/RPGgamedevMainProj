class Stack_Engine
{
	int m_stack_end;
	const int m_range;
	int* m_stack;
public:
    Stack_Engine(const int range, int stack_end = 0);
	~Stack_Engine();

	void Push(int element);
	int Pop();
	int getElement();
	int Pop_Search(int key);
};

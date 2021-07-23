#include "Stack_Engine.h"

Stack_Engine::Stack_Engine(const int range, int stack_end) : m_range(range)
{
	m_stack = new int[m_range];
}

Stack_Engine::~Stack_Engine()
{
	delete [] m_stack;
}

void Stack_Engine::Push(int element)
{
	m_stack[m_stackEnd] = element;
	++m_stackEnd;
}

int Stack_Engine::Pop()
{
	int temp;
	temp = m_stack[m_stackEnd-1];
	m_stack[m_stackEnd-1] = 0;
	--m_stackEnd;
	return temp;
}

int Stack_Engine::getElement()
{
	return m_stack[m_stackEnd-1];
}

int Stack_Engine::PopSearch(int key)
{
	int temp = 0;
	int temp_array[m_stackEnd];
	for(int n = 0; n < m_stackEnd; ++n)
	{
		temp_array[n] = m_stack[n];
	}
	for(int i = 0; i < m_stackEnd; ++i)
	{
		if(m_stack[i] == key)
		{
			continue;
		}
		m_stack[temp] = temp_array[i];
		++temp;
	}
	m_stack[m_stackEnd - 1] = 0;
	--m_stackEnd;
	return temp_array[temp-1];
}

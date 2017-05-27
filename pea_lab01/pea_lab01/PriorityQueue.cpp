#include "PriorityQueue.h"
#include <iostream>
#include <sstream>

using namespace std;

PriorityQueue::PriorityQueue()
{
	length = 0;
	first = NULL;
}

PriorityQueue::~PriorityQueue()
{
	ElemQueue * pointer;
	pointer = first;
	while (first)
	{
		pointer = first->next;
		delete first;
		first = pointer;
	}
	first = NULL;
}

void PriorityQueue::Add(int item, float P)
{
	ElemQueue *temp = new ElemQueue();
	temp->item = item;
	temp->P = P;
	temp->next = NULL;
	ElemQueue * pointer, *pointerPrev;
	pointerPrev = first;
	pointer = first;
	// no elements
	if (pointer == NULL)
	{
		first = temp;
		length++;
		return;
	}
	// 1 element
	if (pointer->next == NULL)
	{
		if (pointer->P < temp->P)
		{
			first = temp;
			temp->next = pointer;
			length++;
			return;
		}
		else
		{
			pointer->next = temp;
			length++;
			return;
		}
	}
	if (first->next != NULL && first->P < temp->P)
	{
		pointer = first;
		first = temp;
		temp->next = pointer;
		length++;
		return;
	}
	// 2 or more elements
	while (pointer != NULL)
	{
		if (pointer->P < temp->P)
		{
			pointerPrev->next = temp;
			temp->next = pointer;
			length++;
			return;
		}
		pointerPrev = pointer;
		pointer = pointer->next;
	}
	pointerPrev->next = temp;
	length++;
}

void PriorityQueue::Remove()
{
	ElemQueue * pointer;
	if (first != NULL)
	{
		pointer = first->next;
		delete first;
		first = pointer;
		length--;
	}
	if (length == 0)
		first = NULL;
}
ElemQueue *PriorityQueue::GetFirst()
{
	return first;
}

string PriorityQueue::Display()
{
	ElemQueue *pointer;
	string result = "";
	stringstream stream;
	pointer = first;
	while (pointer != NULL)
	{
		stream << pointer->item << " ";
		pointer = pointer->next;
	}
	result = stream.str();
	stream.str(string());
	stream.clear();
	return result;
}

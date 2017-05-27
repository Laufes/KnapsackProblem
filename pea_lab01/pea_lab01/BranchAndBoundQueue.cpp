#include "BranchAndBoundQueue.h"
#include <iostream>
#include <sstream>

using namespace std;

BranchAndBoundQueue::BranchAndBoundQueue()
{
	length = 0;
	first = NULL;
}

BranchAndBoundQueue::~BranchAndBoundQueue()
{
	BBElemQueue * pointer;
	pointer = first;
	while (first)
	{
		pointer = first->next;
		delete[] first->items;
		delete first;
		first = pointer;
	}
	first = NULL;
}

void BranchAndBoundQueue::Add(int treeLevel, float upperBound, int value, int weight, bool* items, int itemsCount)
{
	BBElemQueue *temp = new BBElemQueue();
	temp->treeLevel = treeLevel;
	temp->upperBound = upperBound;
	temp->value = value;
	temp->weight = weight;
	temp->items = new bool[itemsCount];
	for (int i = 0; i < itemsCount; i++)
		temp->items[i] = items[i];
	temp->next = NULL;
	BBElemQueue * pointer, *pointerPrev;
	pointerPrev = first;
	pointer = first;
	//  no elements
	if (pointer == NULL)
	{
		first = temp;
		length++;
		return;
	}
	// 1 element
	if (pointer->next == NULL)
	{
		if (pointer->upperBound < temp->upperBound)
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
	if (first->next != NULL && first->upperBound < temp->upperBound)
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
		if (pointer->upperBound < temp->upperBound)
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

void BranchAndBoundQueue::Remove()
{
	BBElemQueue * pointer;
	if (first != NULL)
	{
		pointer = first->next;
		delete[] first->items;
		delete first;
		first = pointer;
		length--;
	}
	if (length == 0)
		first = NULL;
}
BBElemQueue *BranchAndBoundQueue::GetFirst()
{
	return first;
}

string BranchAndBoundQueue::Display()
{
	BBElemQueue *pointer;
	string res = "";
	stringstream ss;
	pointer = first;
	while (pointer != NULL)
	{
		ss << pointer->treeLevel << " ";
		pointer = pointer->next;
	}
	res = ss.str();
	ss.str(string());
	ss.clear();
	return res;
}

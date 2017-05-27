#pragma once
#include <string>
using namespace std;

struct ElemQueue
{
	ElemQueue * next;
	float P;
	int item;
};
class PriorityQueue
{
private:
	int length;
	ElemQueue * first;
public:
	PriorityQueue();
	~PriorityQueue();
	// Add new element to queue and set order depending on P
	void Add(int item, float P);
	// Remove first element
	void Remove();
	ElemQueue * GetFirst();
	string Display();
};

